#include "definicoes.h"

/* CAPTURA INSERE
   Le os valores da entrada padrao e insere no arquivo
   de tamanho fixo  */
void captura_insere(){
  Captura X; 
  system("clear");

  puts("** INSERE CAPTURA **");
  X = captura_read(stdin,1); 

  captura_insere_fix(X); 
  
  captura_insere_var(X); 
}

void captura_insere_fix(Captura X){
  int i,n;
  Captura aux;
  
  fseek(FCaptu_fix, 0, SEEK_SET);

  fread(&n,sizeof(int),1,FCaptu_fix);
  for(i=0;i<n;i++){
    fread(&aux,sizeof(Captura),1,FCaptu_fix);
    if(aux.id == -1){
      fseek(FCaptu_fix,-sizeof(Captura),SEEK_CUR);
      break;
    }
  }  
  fwrite(&X,sizeof(Captura),1,FCaptu_fix);
  fseek(FCaptu_fix,0,SEEK_SET);
  n++;
  
  fwrite(&n,sizeof(int),1,FCaptu_fix);
}

void captura_insere_var(Captura X){
  int n;

  fseek(FCaptu_var, 0, SEEK_SET);
  fread(&n,sizeof(int),1,FCaptu_var);
  fseek(FCaptu_var,0,SEEK_SET);
  n++;
  fwrite(&n,sizeof(int),1,FCaptu_var);

  fseek(FCaptu_var,0,SEEK_END);
  captura_write_var(FCaptu_var, X);
}

void captura_atualiza(){
  int id;

  system("clear");

  puts("** ATUALIZACAO CAPTURAS **");
  printf("Digite o ID: ");
  scanf(" %d", &id);

  captura_atualiza_fix(id);
}

void captura_atualiza_fix(int id){
  int i,j,n, pos_var;
  Captura aux,aux2, auxsave;
  
  fseek(FCaptu_fix, 0, SEEK_SET);
  fread(&n,sizeof(int),1,FCaptu_fix);
  
  for(i=0;i<n;i++){
    fread(&aux,sizeof(Captura),1,FCaptu_fix);

    if(aux.id == -1) i--;
    else if(aux.id == id){
      auxsave = aux;

      printf("ID: ");
      printf("%d\n", aux.id);
      muda_int(&aux.id);
      printf("Comprimento: ");
      printf("%d\n", aux.comprimento);
      muda_int(&aux.comprimento);
      printf("Largura: ");
      printf("%d\n", aux.largura);
      muda_int(&aux.largura);
      printf("Peso: ");
      printf("%d\n", aux.peso);
      muda_int(&aux.peso);
      printf("Data de Captura: ");
      printf("%d\n", aux.data);
      muda_int(&aux.data);
      printf("Local de Captura: ");
      printf("%s\n", aux.local);
      muda_string(aux.local);

      fseek(FCaptu_fix,-sizeof(Captura),SEEK_CUR);
      fwrite(&aux,sizeof(Captura),1,FCaptu_fix);

      /* remove e insere no arquivo de tamanho variavel */
      fseek(FCaptu_var, sizeof(int), SEEK_SET);
      for(j=0 ; j<n ; j++){
	pos_var = (int)ftell(FCaptu_var);
	aux2 = captura_read_var(FCaptu_var);
	if((aux2.id == auxsave.id) &&
	   (aux2.comprimento == auxsave.comprimento) &&
	   (aux2.largura == auxsave.largura) &&
	   (aux2.peso == auxsave.peso) &&
	   (aux2.data == auxsave.data) &&
	   (strcmp(aux2.local, auxsave.local)==0)) {
	  fseek(FCaptu_var, pos_var, SEEK_SET);
	  aux2.id = -1;

	  captura_write_var(FCaptu_var, aux2);
	  break;
	}
      }

      fseek(FCaptu_var,0,SEEK_END);
      captura_write_var(FCaptu_var, aux);

      return;
    }
  }
  printf("Nao encontradas capturas do individuo de ID %d\n", id);
}

void captura_le(){
  char c;
  system("clear");
  
  puts("** LEITURA CAPTURAS **");
  printf("\n");
  
  printf("Voce deseja ler do arquivo de tamanho (F)ixo ou do arquivo de tamanho (V)ariavel: ");
  while(scanf(" %c",&c) == 1 && tolower(c)!='f' && tolower(c)!='v');

  if(tolower(c) == 'f') captura_le_fix();
  if(tolower(c) == 'v') captura_le_var();
}

void captura_le_fix(){
  int n;
  Captura aux;
  
  system("clear");
 
  puts("** LEITURA CAPTURAS FIXO **");
  printf("\n");

  fseek(FCaptu_fix, 0, SEEK_SET);
  fread(&n,sizeof(int),1,FCaptu_fix);
  while(n--){
    fread(&aux,sizeof(Captura),1,FCaptu_fix);
    if(aux.id == -1) n++;
    else captura_write(stdout,aux,1);
    
  }
  Pause();
}  

void captura_le_var(){
  int n;
  Captura aux;
  
  system("clear");
 
  puts("** LEITURA CAPTURAS VARIAVEL **");
  printf("\n");

  fseek(FCaptu_var, 0, SEEK_SET);
  fread(&n,sizeof(int),1,FCaptu_var);
  while(n--){
    aux = captura_read_var(FCaptu_var);
    if(aux.id == -1) n++;
    else captura_write(stdout,aux,1);
  }
  Pause();
}

void captura_deleta(){
  int id;
  
  system("clear");

  puts("** DELECAO CAPTURA **");
  printf("Digite o ID do individuo a ser deletado: ");
  scanf(" %d", &id);

  captura_deleta_fix(id);
}

int captura_deleta_fix(int id){
  int i,n,pos_var;
  char c;
  Captura aux, aux2;

  fseek(FCaptu_var, 0, SEEK_SET);
  fread(&n,sizeof(int),1,FCaptu_var);

  for(i=0 ; i<n ; i++){
    pos_var = (int)ftell(FCaptu_var);

    aux = captura_read_var(FCaptu_var);

    if(aux.id == -1) i--;
    if(aux.id == id){
      captura_write(stdout,aux,1);

      printf("Voce deseja apagar esse registro (y/n)?");
      while(scanf("%c", &c)==1 && tolower(c)!='y' && tolower(c)!='n');
      if(tolower(c)=='n') continue;

      /* reduz o numero de registros nos 2 arquivos */
      fseek(FCaptu_fix, 0, SEEK_SET);
      fread(&n,sizeof(int), 1, FCaptu_fix);
      n--;

      fseek(FCaptu_fix, 0, SEEK_SET);
      fwrite(&n, sizeof(int), 1, FCaptu_fix);
      fseek(FCaptu_var, 0, SEEK_SET);
      fwrite(&n, sizeof(int), 1, FCaptu_var);

      /* para o registro variavel */
      fseek(FCaptu_var, pos_var, SEEK_SET);
      aux2 = aux;
      aux2.id = -1;

      captura_write_var(FCaptu_var, aux2);


      /* para o registro fixo */
      /* precisa achar o registro, e entao apagar */
      fseek(FCaptu_fix, sizeof(int), SEEK_SET);
      while(1) {
	fread(&aux2, sizeof(Captura), 1, FCaptu_fix);
	if((aux2.id == aux.id) &&
	   (aux2.comprimento == aux.comprimento) &&
	   (aux2.largura == aux.largura) &&
	   (aux2.peso == aux.peso) &&
	   (aux2.data == aux.data) &&
	   (strcmp(aux2.local, aux.local)==0)) break;
      }
      fseek(FCaptu_fix, -sizeof(Captura), SEEK_CUR);

      aux.id = -1;
      fwrite(&aux, sizeof(Captura), 1, FCaptu_fix);
    }

    fseek(FCaptu_var, pos_var+captura_conta_bytes(aux), SEEK_SET);
  }
    
  return 0;
}


Captura captura_read(FILE *fin, int print) {
  Captura X;

  if(print) printf("ID: ");
  fscanf(fin, " %d", &X.id);
  if(print) printf("Comprimento: ");
  fscanf(fin, " %d", &X.comprimento);
  if(print) printf("Largura: ");
  fscanf(fin, " %d", &X.largura);
  if(print) printf("Peso: ");
  fscanf(fin, " %d", &X.peso);
  if(print) printf("Data de Captura: ");
  fscanf(fin, " %d", &X.data);
  if(print) printf("Local de Captura: ");
  fscanf(fin, " %s", X.local);

  return X;
}

void captura_write(FILE *fout, Captura X, int print) {
  if(print) printf("ID do Individuo: ");
  fprintf(fout, "%d\n", X.id);
  if(print) printf("Comprimento: ");
  fprintf(fout, "%d\n", X.comprimento);
  if(print) printf("Largura: ");
  fprintf(fout, "%d\n", X.largura);
  if(print) printf("Peso: ");
  fprintf(fout, "%d\n", X.peso);
  if(print) printf("Data de Captura: ");
  fprintf(fout, "%d\n", X.data);
  if(print) printf("Local de Captura: ");
  fprintf(fout, "%s\n", X.local);

  if(print) printf("\n");
}

Captura captura_read_var(FILE *fin) {
  Captura X;
  int tam;

  fread(&X.id, sizeof(int), 1, fin);
  fread(&X.comprimento, sizeof(int), 1, fin);
  fread(&X.largura, sizeof(int), 1, fin);
  fread(&X.peso, sizeof(int), 1, fin);
  fread(&X.data, sizeof(int), 1, fin);

  fread(&tam, sizeof(int), 1, fin);
  fread(X.local, sizeof(char), tam, fin);
  X.local[tam]='\0';

  return X;
}

void captura_write_var(FILE *fout, Captura X) {
  int tam = strlen(X.local);

  fwrite(&X.id, sizeof(int), 1, fout);
  fwrite(&X.comprimento, sizeof(int), 1, fout);
  fwrite(&X.largura, sizeof(int), 1, fout);
  fwrite(&X.peso, sizeof(int), 1, fout);
  fwrite(&X.data, sizeof(int), 1, fout);

  fwrite(&tam, sizeof(int), 1, fout);
  fwrite(X.local, sizeof(char), tam, fout);
}

int captura_conta_bytes(Captura X) {
  return (5*sizeof(int)
	  + sizeof(int)
	  + strlen(X.local)*sizeof(char));
}
