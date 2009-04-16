#include "definicoes.h"

/* ESCREVE EM UM ARQUIVO UM REGISTRO DE LISTA */
void lista_escreve(FILE *fp, int sz, int prev, int next) {
  fprintf(fp, "%c", VAZIO);
  fprintf(fp, "%04d %03d %03d\n", sz, prev, next);
}

/* LE DE UM ARQUIVO UM REGISTRO DE LISTA */
int lista_le(FILE *fp, Lista *x) {
  if(fscanf(fp, " %d %d %d", &(x->sz), &(x->prev), &(x->next))==3)
    return 1;
  return 0;
}

/* BUSCA UM BURACO DE NO MINIMO sz BYTES */
/* devolve -1 em caso de falha na busca e SZ, o
   tamanho do buraco, em caso de sucesso na busca */
int lista_busca_vazio(FILE *fp, int sz) {
  Lista x;
  char c;
  int aux, no_cabeca = 1;

  fseek(fp, SZ_1, SEEK_SET);
  while(1) {
    fscanf(fp, " %c", &c);
    if(c == USADO) {
      fscanf(fp, " %d", &aux);
      fseek(fp, aux, SEEK_CUR);
      continue;
    }

    if(lista_le(fp, &x)!=1) break;
    if(x.sz >= sz && !no_cabeca) {
      fseek(fp, -SZ_LISTA, SEEK_CUR);
      return x.sz;
    }

    if(x.next == -1) return -1;
    fseek(fp, x.next, SEEK_SET);

    no_cabeca = 0;
  }

  return -1;
}

/* INSERCAO DE BURACOS NA LISTA LIGADA */
void lista_insere(FILE *fp, int sz, int pos) {
  Lista x,y;
  int save, next;

  /* BUSCA NO ANTERIOR AO NOVO */
  next = SZ_1;
  while(next < pos && next != -1) {
    fseek(fp, next+1, SEEK_SET);
    lista_le(fp, &x);

    next = x.next;
  }

  fseek(fp, -SZ_LISTA, SEEK_CUR);
  save = (int)ftell(fp);

  /* PEGA INFORMACOES DO NO SEGUINTE AO NOVO */
  if(x.next != -1) {
    fseek(fp, x.next+1, SEEK_SET);
    lista_le(fp, &y);
  }

  /* volta aa posicao do no anterior ao novo */
  fseek(fp, save, SEEK_SET);


  /* UNIAO DE BURACOS */
  /* x.prev != -1 pois nao pode ser o no-cabeca */
  if((save + SZ_REG + x.sz == pos) && (x.prev != -1)) {
    /* este e o proximo podem se juntar */
    if(pos + SZ_REG + sz == x.next) {
      lista_escreve(fp, x.sz+sz+y.sz+2*SZ_REG, x.prev, y.next);
      return;
    }
    else {
      lista_escreve(fp, x.sz+sz+SZ_REG, x.prev, x.next);
      /* modifica o no seguinte ao novo */
      if(x.next == -1) return;
      fseek(fp, x.next, SEEK_SET);
      lista_escreve(fp, y.sz, pos, y.next);
    }
  }
  else if(pos + SZ_REG + sz == x.next) {
    lista_escreve(fp, x.sz, x.prev, pos);

    /* cria o no novo */
    fseek(fp, pos, SEEK_SET);
    lista_escreve(fp, sz+y.sz+SZ_REG, save, y.next);
  }
  else {
    lista_escreve(fp, x.sz, x.prev, pos);

    /* cria o no novo */
    fseek(fp, pos, SEEK_SET);
    lista_escreve(fp, sz, save, x.next);

    /* modifica o no seguinte ao novo */
    if(x.next == -1) return;
    fseek(fp, x.next, SEEK_SET);
    lista_escreve(fp, y.sz, pos, y.next);
  }
}

/* REMOVE UM BURACO DA LISTA LIGADA */
/* a posicao do ponteiro do arquivo sera, garatidamente,
   a mesma antes e depois do uso da funcao lista_remove() */
void lista_remove(FILE *fp) {
  int save;
  Lista x, prev,next;

  save = (int)ftell(fp);

  fscanf(fp, "%*c");
  lista_le(fp, &x);

  /* modifica os apontadores do no anterior ao removido */
  fseek(fp, x.prev, SEEK_SET);
  fscanf(fp, "%*c");
  lista_le(fp, &prev);
  fseek(fp, -SZ_LISTA, SEEK_CUR);
  lista_escreve(fp, prev.sz, prev.prev, x.next);

  if(x.next != -1) {
    /* modifica os apontadores do no posterior ao removido */
    fseek(fp, x.next, SEEK_SET);
    fscanf(fp, "%*c");
    lista_le(fp, &next);
    fseek(fp, -SZ_LISTA, SEEK_CUR);
    lista_escreve(fp, next.sz, x.prev, next.next);
  }

  fseek(fp, save, SEEK_SET);
}
