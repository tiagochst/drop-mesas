#include "definicoes.h"

/* Efetua uma busca no arquivo de Capturas (registro de
   tamanho fixo) por registros de captura do individuo
   do ID fornecido pelo usuario */
void historico_monitoramento() {
  int i,pos;
  int id;
  Captura aux;
  system("clear");
  
  puts("** HISTORICO DE MONITORAMENTO **");
  printf("\n");
  
  printf("Digite o ID do individuo: ");
  scanf(" %d", &id);
  pos = indice_sec_busca("captura",id);
  if(pos == -1){
    printf("Nao ha capturas desse individuo!\n");
  }
  else{
    for(i=pos;i<N_ISCaptu && ISCaptu[i].idS==id;i++){
      fseek(FCaptu,ISCaptu[i].idP,SEEK_SET);
      aux = captura_read(FCaptu);
      captura_write_(stdout,aux,1);
    }
  }
  
  Pause();
}

/* Efetua a mesma busca do Historico de Monitoramento,
   mas para determinar a ultima captura, armazena-se a
   data da captura mais recente e o registro dessa captura */
void ultima_captura() {
  int i, id, pos,offset;
  Data data;
  Captura aux;
  system("clear");

  printf("Digite o ID do individuo: ");
  scanf(" %d", &id);
  data.ano = FAIL;
  
  
  pos = indice_sec_busca("captura",id);
  if(pos == -1){
    printf("Nao ha capturas desse individuo!\n");
  }
  else{
    for(i=pos;i<N_ISCaptu && ISCaptu[i].idS==id;i++){
      fseek(FCaptu,ISCaptu[i].idP,SEEK_SET);
      aux = captura_read(FCaptu);
      captura_write_(stdout,aux,1);
      if (data_cmp(aux.data, data) > 0) {
	offset = ISCaptu[i].idP;
	data = aux.data;
      }
    }
  }
  if (data.ano == FAIL)
    printf("Nao ha registros de captura desse individuo\n");
  else {
    printf("O ultimo registro desse individuo data de ");
    data_escreve(stdout, data);
    fseek(FCaptu, offset, SEEK_SET);
    aux = captura_read(FCaptu);
    captura_write_(stdout, aux, 1);
  }

  Pause();
}

/* Obtido o ID da especie e o peso minimo, encontra
   os individuos dessa especie, e então o registro
   da ultima captura desse individuo, e enfim verifica-se
   se o peso esta dentro do pedido */
void ultima_captura_peso() {
  int i,j;
  int pos,aux;
  int offset;
  int idE, idI, peso;
  Data data;
  Captura C, Cc;
  
  system("clear");
  printf("Digite o ID da especie: ");
  scanf("%d", &idE);
  printf("Digite o peso minimo: ");
  scanf("%d", &peso);
  
  idI = -1;
  pos = indice_sec_busca("individuo",idE);/*Pega todos os individuos dessa especie*/ 
  if(pos == -1){
    printf("Nao ha registros dessa espécie!\n");
  }
  else{
    for(i=pos;i<N_ISIndiv && ISIndiv[i].idS == idE;i++){
      data.ano = FAIL;
      aux = indice_sec_busca("captura",ISIndiv[i].idP); /*Dado o individuo, pegamos todas as capturas*/ 
      if(aux!= -1){
	for(j=aux;j<N_ISCaptu && ISCaptu[j].idS==ISIndiv[i].idP;j++){

	  fseek(FCaptu,ISCaptu[j].idP,SEEK_SET);
	  C = captura_read(FCaptu);	  
	  
	  if (C.idI == ISIndiv[i].idP && data_cmp(C.data, data) > 0) {
	    offset = ISCaptu[j].idP;
	    data = C.data;
	  }
	}
	fseek(FCaptu, offset, SEEK_SET);
	Cc = captura_read(FCaptu);
	captura_write_(stdout,Cc,1);
	if (Cc.peso < peso)
	  printf("O peso na ultima captura deste individuo foi abaixo do minimo\n");
	else {
	  printf("ID do Individuo: ");
	  printf("%d\n", Cc.idI);
	  printf("Data de Captura: ");
	  data_escreve(stdout, Cc.data);
	  printf("Local de Captura: ");
	  printf("%s\n", Cc.local);
	  
	  printf("\n");
	}
	
      }
    }
  }
 
  Pause();
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

  if (individuo_busca(idI, &X) == -1) {
    printf("Nao foi encontrado individuo com o ID fornecido.\n\n");
    Pause();
    return;
  }
  idE = X.idE;

  printf("Individuo %d pertence aa especie de ID %d\n", idI, idE);

  if (especie_busca(idE, &Y) == -1) {
    printf("Inconcistencia nos dados: nao ha especie de ID %d\n\n", idE);
    Pause();
    return;
  }

  printf("Caminho do arquivo de imagem: %s\n\n", Y.camin);
  Pause();
  return;
}

void busca_especie_descricao() {
  char s[200];
  system("clear");

  printf("Digite as palavras a pesquisar: ");
  scanf(" %[^\n]", s);

  lista_inv_busca(s);
}
