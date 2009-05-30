#include "definicoes.h"

/* Efetua uma busca no arquivo de Capturas (registro de
 * tamanho fixo) por registros de captura do individuo
 * do ID fornecido pelo usuario */
void historico_monitoramento_lab1(int lab3) {
  int n, id;
  Captura aux;
    
  if(lab3 == -1){
    system("clear");
    
    puts("** HISTORICO DE MONITORAMENTO **");
    printf("\n");
    
    printf("Digite o ID do indivíduo: ");
    scanf(" %d", &id);
  }
  else id = lab3;  
  
  fseek(FCaptu, 0, SEEK_SET);
  fread(&n, sizeof(int), 1, FCaptu);
  while(n--){
    aux = captura_read(FCaptu);
    if(aux.idC == -1) n++;
    else if(aux.idI == id) captura_write_(stdout, aux, 1);
  }
  if(lab3 == -1) Pause();

}

void historico_monitoramento_lab2(int lab3) {
  int i, pos;
  int id;
  Captura aux;


  if(lab3 == -1){
    system("clear");

    puts("** HISTORICO DE MONITORAMENTO **");
    printf("\n");

    printf("Digite o ID do individuo: ");
    scanf(" %d", &id);
    putchar('\n');
  }
  else id = lab3;

  pos = indice_sec_busca("captura", id);
  if (pos == -1) {
    printf("Nao ha capturas desse individuo!\n");
  } else {
    for (i = pos; i < N_ISCaptu && ISCaptu[i].idS == id; i++) {
      fseek(FCaptu, ISCaptu[i].idP, SEEK_SET);
      aux = captura_read(FCaptu);
      captura_write_(stdout, aux, 1);
    }
  }

  if(lab3 == -1) Pause();
}

/* Efetua a mesma busca do Historico de Monitoramento,
 * mas para determinar a ultima captura, armazena-se a
 * data da captura mais recente e o registro dessa captura */
void ultima_captura_lab1(int lab3) {
  int n, id,pos;
  Data data;
  Captura aux;
    
  if(lab3 == -1){
    system("clear");
    puts("** ULTIMA CAPTURA **");
    printf("\n");

    
    printf("Digite o ID do individuo: ");
    scanf(" %d", &id);
  }
  else id = lab3;
  
  fseek(FCaptu, 0, SEEK_SET);
  fread(&n, sizeof(int), 1, FCaptu);
  
  data.ano = FAIL;
  while(n--){
    aux = captura_read(FCaptu);
    if(aux.idC == -1) n++;
    else if(aux.idI == id && data_cmp(aux.data,data) > 0){
      pos = ftell(FCaptu) - sizeof(Captura);
      data = aux.data;
    }
  }
  
  if(data.ano == FAIL) printf("Nao ha registros de captura desse individuo\n");
  else{
    printf("O ultimo registro desse individuo data de :");
    data_escreve(stdout,data);
    fseek(FCaptu, pos, SEEK_SET);
    aux = captura_read(FCaptu);
    captura_write_(stdout, aux, 1);
  }
  if(lab3 == -1) Pause();  
}

void ultima_captura_lab2(int lab3) {
  int i, id, pos, offset;
  Data data;
  Captura aux;
  

  if(lab3 == -1){
    system("clear");
    
    puts("** ULTIMA CAPTURA **");
    printf("\n");

    printf("Digite o ID do individuo: ");
    scanf(" %d", &id);
    putchar('\n');
  }
  else id = lab3;
  
  data.ano = FAIL;

  pos = indice_sec_busca("captura", id);
  if (pos != -1) {
    for (i = pos; i < N_ISCaptu && ISCaptu[i].idS == id; i++) {
      fseek(FCaptu, ISCaptu[i].idP, SEEK_SET);
      aux = captura_read(FCaptu);

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
    putchar('\n');
    fseek(FCaptu, offset, SEEK_SET);
    aux = captura_read(FCaptu);
    captura_write_(stdout, aux, 1);
  }

  if(lab3 == -1) Pause();
}

/* Obtido o ID da especie e o peso minimo, encontra
 * os individuos dessa especie, e então o registro
 * da ultima captura desse individuo, e enfim verifica-se
 * se o peso esta dentro do pedido */
void ultima_captura_peso_lab1(int lab3) {
  int idE, idI,n1,n2, peso;
  Data data;
  Captura C,Cc;
  Individuo X;
  
  if(lab3 == -1){
    system("clear");
        
    puts("** PESO MINIMO **");
    printf("\n");
    
    printf("Digite o ID da especie: ");
    scanf("%d",&idE);
    printf("Digite o peso minimo: ");
    scanf("%d",&peso);
  }
  else{
    idE = lab3;
    srand(time(NULL));
    peso = (rand()%100) + 100;
  }
  
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
      data.ano = FAIL;
      while(n2--){
        C = captura_read(FCaptu);
	
        if(C.idC == -1) n2++;
        else if(C.idI == idI && data_cmp(C.data,data) > 0){
          Cc = C;
          data = C.data;
        }
      }
      
      if(data.ano == FAIL) printf("Nao ha registros de captura desse individuo\n");
      else{
        if(Cc.peso < peso)
          printf("O peso na ultima captura deste individuo foi abaixo do minimo\n");
        else {
          printf("ID do Individuo: ");
          printf("%d\n", Cc.idI);
          printf("Data de Captura: ");
          data_escreve(stdout,Cc.data);
          printf("Local de Captura: ");
          printf("%s\n", Cc.local);
	  
          printf("\n");
        }
      }
      if(lab3 == -1) Pause();  
    }
  }
  
  if(idI == -1 && lab3 == -1) {
    printf("Nao foi encontrado individuos da especie com o ID fornecido.\n\n");
    Pause();
  }  
}

void ultima_captura_peso_lab2(int lab3) {
  int i, j;
  int pos, aux;
  int offset;
  int idE, idI, peso;
  Data data;
  Captura C, Cc;
  
  if(lab3 == -1){
    system("clear");
        
    puts("** PESO MINIMO **");
    printf("\n");
    
    printf("Digite o ID da especie: ");
    scanf("%d", &idE);
    printf("Digite o peso minimo: ");
    scanf("%d", &peso);
    putchar('\n');
  }
  else{
    idE = lab3;
    srand(time(NULL));
    peso = (rand()%100) + 100;
  }
  
  idI = -1;
  pos = indice_sec_busca("individuo", idE);/*Pega todos os individuos dessa especie*/
  if (pos == -1) {
    printf("Nao ha registros dessa espécie!\n");
  } else {
    for (i = pos; i < N_ISIndiv && ISIndiv[i].idS == idE; i++) {
      data.ano = FAIL;
      aux = indice_sec_busca("captura", ISIndiv[i].idP); /*Dado o individuo, pegamos todas as capturas*/
      if (aux != -1) {
	for (j = aux; j < N_ISCaptu && ISCaptu[j].idS == ISIndiv[i].idP; j++) {

	  fseek(FCaptu, ISCaptu[j].idP, SEEK_SET);
	  C = captura_read(FCaptu);

	  if (C.idI == ISIndiv[i].idP && data_cmp(C.data, data) > 0) {
	    offset = ISCaptu[j].idP;
	    data = C.data;
	  }
	}
	fseek(FCaptu, offset, SEEK_SET);
	Cc = captura_read(FCaptu);

	if (Cc.peso < peso)
	  printf("O peso na ultima captura deste individuo foi abaixo do minimo\n");
	else
	  captura_write_(stdout, Cc, 1);
      }
    }
  }

  if(lab3 == -1) Pause();
}

/* Dado o individuo, buscamos a especie que ele pertence
 * e enfim procuramos pelo registro dessa especie, onde
 * esta salvo o caminho da foto */
void caminho_especie_lab1(int lab3) {

  int idI, idE;
  Individuo X;
  Especie Y;


  if(lab3 == -1){
    system("clear");
       
    puts("** CAMINHO DA ESPECIE **");
    printf("\n");
    
    printf("Digite o ID do individuo: ");
    scanf(" %d", &idI);
  }
  else idI = lab3;

  if(individuo_busca_lab1(idI, &X) == -1) {
    printf("Nao foi encontrado individuo com o ID fornecido.\n\n");
    if(lab3 == -1) Pause();
    return;
  }
  idE = X.idE;

  printf("Individuo %d pertence aa especie de ID %d\n", idI, idE);

  if(especie_busca_lab2(idE, &Y) == -1) {
    printf("Inconcistencia nos dados: nao ha especie de ID %d\n\n", idE);
    if(lab3 == -1) Pause();
    return;
  }

  printf("Caminho do arquivo de imagem: %s\n\n", Y.camin);
  if(lab3 == -1) Pause();
  return;

}

void caminho_especie_lab2(int lab3) {
  int idI, idE;
  Individuo X;
  Especie Y;

  if(lab3 == -1){
    system("clear");
        
    puts("** CAMINHO DA ESPECIE **");
    printf("\n");
    
    printf("Digite o ID do individuo: ");
    scanf(" %d", &idI);
    putchar('\n');
  }
  else idI = lab3;

  if (individuo_busca_lab2(idI, &X) == -1) {
    printf("Nao foi encontrado individuo com o ID fornecido.\n\n");
    if(lab3 == -1) Pause();
    return;
  }
  idE = X.idE;

  printf("Individuo %d pertence aa especie de ID %d\n", idI, idE);

  if (especie_busca_lab2(idE, &Y) == -1) {
    printf("Inconcistencia nos dados: nao ha especie de ID %d\n\n", idE);
    if(lab3 == -1) Pause();
    return;
  }

  printf("Caminho do arquivo de imagem: %s\n\n", Y.camin);
  if(lab3 == -1 ) Pause();
  return;
}

/* Le o texto da busca, e chama função da lista invertida
 * para busca textual pelo campo descrição da espécie */
void busca_especie_descricao() {
  char s[200];
  system("clear");

  printf("Digite as palavras a pesquisar: ");
  scanf(" %[^\n]", s);

  lista_inv_busca(s);
}
