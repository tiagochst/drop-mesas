#include "definicoes.h"

/* Efetua uma busca no arquivo de Capturas (registro de
   tamanho fixo) por registros de captura do individuo
   do ID fornecido pelo usuario */
void historico_monitoramento(){
  int n, id;
  Captura aux;
  system("clear");

  puts("** HISTÓRICO DE MONITORAMENTO **");
  printf("\n");

  printf("Digite o ID do indivíduo: ");
  scanf(" %d", &id);

  fseek(FCaptu, 0, SEEK_SET);
  fread(&n, sizeof(int), 1, FCaptu);
  while(n--){
    aux = captura_read(FCaptu);
    if(aux.id == -1) n++;
    else if(aux.id == id) captura_write(stdout, aux, 1);
  }

  Pause();
}

/* Efetua a mesma busca do Historico de Monitoramento,
   mas para determinar a ultima captura, armazena-se a
   data da captura mais recente e o registro dessa captura */
void ultima_captura(){
  int n, id,pos,data;
  Captura aux;
  system("clear");

  printf("Digite o ID do individuo: ");
  scanf(" %d", &id);

  fseek(FCaptu, 0, SEEK_SET);
  fread(&n, sizeof(int), 1, FCaptu);

  data = 0;
  while(n--){
    aux = captura_read(FCaptu);
    if(aux.id == -1) n++;
    else if(aux.id == id && aux.data >  data){
      pos = ftell(FCaptu) - sizeof(Captura);
      data = aux.data;
    }
  }

  if(!data) printf("Nao ha registros de captura desse individuo\n");
  else{
    printf("O ultimo registro desse individuo data de %d:\n", data);
    fseek(FCaptu, pos, SEEK_SET);
    aux = captura_read(FCaptu);
    captura_write(stdout, aux, 1);
  }
  Pause();
}

/* Obtido o ID da especie e o peso minimo, encontra
   os individuos dessa especie, e então o registro
   da ultima captura desse individuo, e enfim verifica-se
   se o peso esta dentro do pedido */
void ultima_captura_peso() {
  int idE, idI,n1,n2,data, peso;
  Captura C,Cc;
  Individuo X;

  system("clear");
  printf("Digite o ID da especie: ");
  scanf("%d",&idE);
  printf("Digite o peso minimo: ");
  scanf("%d",&peso);

  /* acha os idI */
  idI = -1;

  fseek(FIndiv, 0, SEEK_SET);
  fscanf(FIndiv, " %d", &n1);
  while(n1--) {
    X = individuo_read(FIndiv, NULL, NULL);

    if(X.idI == -1) {
      n1++; continue;
    }
    if(X.idE == idE) {
      idI = X.idI;

      /* achou um idI */
      printf("O individuo %d pertence aa especie %d\n", idI, idE);

      fseek(FCaptu, 0, SEEK_SET);
      fread(&n2, sizeof(int), 1, FCaptu);
      data = -1;
      while(n2--){
	C = captura_read(FCaptu);

	if(C.id == -1) n2++;
	else if(C.id == idI && C.data >  data){
	  Cc = C;
	  data = C.data;
	}
      }

      if(data == -1) printf("Nao ha registros de captura desse individuo\n");
      else{
	if(Cc.peso < peso)
	  printf("O peso na ultima captura deste individuo foi abaixo do minimo\n");
	else {
	  printf("ID do Individuo: ");
	  printf("%d\n", Cc.id);
	  printf("Data de Captura: ");
	  printf("%d\n", Cc.data);
	  printf("Local de Captura: ");
	  printf("%s\n", Cc.local);

	  printf("\n");
	}
      }
      Pause();  
    }
  }

  if(idI == -1) {
    printf("Nao foi encontrado individuos da especie com o ID fornecido.\n\n");
    Pause();
  }
}

/* Dado o individuo, buscamos a especie que ele pertence
   e enfim procuramos pelo registro dessa especie, onde
   esta salvo o caminho da foto */
void caminho_especie() {
  int idI, idE;
  Individuo X;
  Especie Y;

  system("clear");
  printf("Digite o ID do individuo: ");
  scanf(" %d", &idI);

  if(individuo_busca(idI, &X) == -1) {
    printf("Nao foi encontrado individuo com o ID fornecido.\n\n");
    Pause();
    return;
  }
  idE = X.idE;

  printf("Individuo %d pertence aa especie de ID %d\n", idI, idE);

  if(especie_busca(idE, &Y) == -1) {
    printf("Inconcistencia nos dados: nao ha especie de ID %d\n\n", idE);
    Pause();
    return;
  }

  printf("Caminho do arquivo de imagem: %s\n\n", Y.camin);
  Pause();
  return;
}
