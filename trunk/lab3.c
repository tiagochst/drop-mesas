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

}

void compara_tempo(){
  int i,j;
  char c;
  int k,n1,n2;
  double t1[4],t2[4];
  struct timeb ini, fim;
  

  printf("Digite a quantidade de consultas a realizar:\n");
  scanf("%d",&k);
    
  n1 = k/N_IPIndiv;
  n2 = k/N_IPEspec;
  
  /* EXECUTA A CONSULTA A */
  ftime(&ini);

  for(i=0;i<N_IPIndiv;i++)
    for(j=0;j<n1;j++)
      historico_monitoramento_lab1(IPIndiv[i].id);

  ftime(&fim);
  t1[0] = ((double) fim.time + ((double) fim.millitm * 0.001)) -((double) ini.time + ((double) ini.millitm * 0.001));

  ftime(&ini);
  for(i=0;i<N_IPIndiv;i++)
    for(j=0;j<n1;j++)
      historico_monitoramento_lab2(IPIndiv[i].id);
  ftime(&fim);
  t2[0] = ((double) fim.time + ((double) fim.millitm * 0.001)) -((double) ini.time + ((double) ini.millitm * 0.001));
  
      
  /*EXECUTA A CONSULTA B*/
  ftime(&ini);

  for(i=0;i<N_IPIndiv;i++)
    for(j=0;j<n1;j++)
      ultima_captura_lab1(IPIndiv[i].id);

  ftime(&fim);
  t1[1] = ((double) fim.time + ((double) fim.millitm * 0.001)) -((double) ini.time + ((double) ini.millitm * 0.001));

  ftime(&ini);
  for(i=0;i<N_IPIndiv;i++)
    for(j=0;j<n1;j++)
      ultima_captura_lab2(IPIndiv[i].id);
  ftime(&fim);
  t2[1] = ((double) fim.time + ((double) fim.millitm * 0.001)) -((double) ini.time + ((double) ini.millitm * 0.001));
  
  
  
  /*EXECUTA A CONSULTA C*/
  ftime(&ini);

  for(i=0;i<N_IPEspec;i++)
    for(j=0;j<n2;j++)
      ultima_captura_peso_lab1(IPEspec[i].id);

  ftime(&fim);
  t1[2] = ((double) fim.time + ((double) fim.millitm * 0.001)) -((double) ini.time + ((double) ini.millitm * 0.001));

  ftime(&ini);
  for(i=0;i<N_IPEspec;i++)
    for(j=0;j<n2;j++)
      ultima_captura_peso_lab2(IPEspec[i].id);
  ftime(&fim);
  t2[2] = ((double) fim.time + ((double) fim.millitm * 0.001)) -((double) ini.time + ((double) ini.millitm * 0.001));
  
  
 
  /*EXECUTA A CONSULTA D*/
  ftime(&ini);

  for(i=0;i<N_IPIndiv;i++)
    for(j=0;j<n1;j++)
      caminho_especie_lab1(IPIndiv[i].id);

  ftime(&fim);
  t1[3] = ((double) fim.time + ((double) fim.millitm * 0.001)) -((double) ini.time + ((double) ini.millitm * 0.001));

  ftime(&ini);
  for(i=0;i<N_IPIndiv;i++)
    for(j=0;j<n1;j++)
      caminho_especie_lab2(IPIndiv[i].id);
  ftime(&fim);
  t2[3] = ((double) fim.time + ((double) fim.millitm * 0.001)) -((double) ini.time + ((double) ini.millitm * 0.001));
  
  
  system("clear");
  printf("Consulta Tempo 1(ms) Tempo 2(ms) Reducao\n");
  for(i=0,c='a';i<4;i++,c++){    
    printf("4.%c %10.2lf %12.2lf %11.2lf%%\n",c,1000*t1[i],1000*t2[i],100*((t1[i]-t2[i])/t1[i]));
  }

  
  Pause();
  return;
}

