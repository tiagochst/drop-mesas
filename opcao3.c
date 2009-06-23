#include "definicoes.h"


typedef struct{
  double sim;
  int id;
  int pos;
}TMedia;


/*
 * Leitura das matrizes de distancia 
 */
double **le_matriz(char *file,int *n){
  int i,j;
  FILE *fp;
  double **vet;
  fp = Fopen(file,"r");
  
  fscanf(fp,"%d",&(*n));
  vet = (double **)malloc((*n)*sizeof(double *));
  for(i=0;i<(*n);i++){
    vet[i] = (double *)malloc((*n)*sizeof(double));
    for(j=0;j<(*n);j++)  fscanf(fp,"%lf",&vet[i][j]);
  }
  fclose(fp);
  return vet;
}


double **calcula_media(double **v1,double **v2,double **v3,int n){
  int i,j;
  double **vet;
 
  vet = (double **)malloc(n*sizeof(double *));
  for(i=0;i<n;i++){
    vet[i] = (double *)malloc(n*sizeof(double));
    for(j=0;j<n;j++){
      vet[i][j] = (v1[i][j]+v2[i][j]+v3[i][j])/3;      
    }
  	
  }
  
  return vet;

}

/*
 * Compara a matriz das medias 
 * na linha n (arquivo n) teremos a distancia do
 * n ao m,quanto menor a distancia mais proximo ele eh 
 */
void compara(double **vet,int n){
  int j;
  int id;
  TMedia *mat_media;

  do{
    printf("Digite o identificador do arquivo (Max = %d Min = 0):\n",n-1);
    scanf("%d",&id);
  }while(id>=n || id<0);
  
  mat_media = (TMedia *)malloc(n*sizeof(TMedia));
  for(j=0;j<n;j++){    
    mat_media[j].sim = vet[id][j];
    mat_media[j].id = j;
  }
  printf("\n");
  qsort(mat_media,n,sizeof(TMedia),comp1);/*ordenacao por distancia*/
  for(j=0;j<n;j++) mat_media[j].pos = j;
  qsort(mat_media,n,sizeof(TMedia),comp2);/*ordenacao por indice do arquivo*/
  
  for(j=0;j<n;j++)
    printf("%d - %s\n",mat_media[j].pos,FileNames[j]);
 
  Pause();
  free(mat_media);
  
}

void opcao3(){
  double **v1,**v2,**v3;
  double **vet;
  int n;
  v1 = le_matriz("bagOfWords.matrix",&n);
  v2 = le_matriz("cosseno.matrix",&n);
  v3 = le_matriz("okapi.matrix",&n);
 
  vet = calcula_media(v1,v2,v3,n);
  
  compara(vet,n);

  limpa_matrix(v1,n);
  limpa_matrix(v2,n);
  limpa_matrix(v3,n);
  limpa_matrix(vet,n);
 
  return;
}
  
int comp1(const void *a,const void *b){
  TMedia *A = (TMedia *)a;
  TMedia *B = (TMedia *)b;

  if(B->sim > A->sim) return 1;
  else if(B->sim == A->sim) return 0;
  return -1;

}

int comp2(const void *a,const void *b){
  TMedia *A = (TMedia *)a;
  TMedia *B = (TMedia *)b;

  return A->id - B->id;

}
  
void limpa_matrix(double **v,int n){
  int i;

  for(i=0;i<n;i++){
    free(v[i]);
  }
  free(v);

  return;
}
