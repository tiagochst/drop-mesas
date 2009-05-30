#include "definicoes.h"
#include <sys/time.h>
#include <time.h>
#include <sys/timeb.h>

void le_dados(char **arg){
  int i;
  FILE *file_input[3];
  
  for(i=0 ; i<3 ; i++) {
    
    file_input[i] = fopen(arg[i+1], "r");
    
    if(file_input[i] == NULL) {
      fprintf(stderr, "ERRO [main]: Nao foi possivel abrir um dos arquivos de input.");
	    return ;
    }
  }
  especie_insere_lab3(file_input[0]);
  individuo_insere_lab3(file_input[1]);
  captura_insere_lab3(file_input[2]);
  
  for(i=0 ; i<3 ; i++)
    fclose(file_input[i]);
  
  printf("Leitura efetuada com sucesso!\n");
  Pause();
}

void compara_tempo(){
  int i,j;
  int k,n1,n2;
  double t1,t2;
  struct timeb ini, fim;
  

  printf("Digite a quantidade de consultas a realizar:\n");
  scanf("%d",&k);
  n1 = k/N_IPIndiv;
  n2 = k/N_IPEspec;
  
  /* EXECUTA A CONSULTA A */
  t1 = 0;
  t2 = 0;

  ftime(&ini);

  for(i=0;i<N_IPIndiv;i++)
    for(j=0;j<n1;j++)
      historico_monitoramento_lab1(IPIndiv[i].id);

  ftime(&fim);
  t1 = ((double) fim.time + ((double) fim.millitm * 0.001)) -((double) ini.time + ((double) ini.millitm * 0.001));

  ftime(&ini);
  for(i=0;i<N_IPIndiv;i++)
    for(j=0;j<n1;j++)
      historico_monitoramento_lab2(IPIndiv[i].id);
  ftime(&fim);
  t2 = ((double) fim.time + ((double) fim.millitm * 0.001)) -((double) ini.time + ((double) ini.millitm * 0.001));
 
  printf("%lf %lf\n",t1,t2);
  Pause();
  return;
}

