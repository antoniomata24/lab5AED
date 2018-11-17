#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _graph Graph;
typedef struct _edge Edge;
struct _graph{int V; int E; int **adj;};
struct _edge{int v; int w;};

Graph *GRAPHinit(int V);
void GRAPHinsertE(Graph *, Edge *, int);
int **MATRIXint(int , int , int );
void DestroyGRAPH(Graph *, int );

int main(int argc, char *argv[]){

  FILE *fIn, *fOut = NULL;
  Graph *G = NULL;
  Edge *E = NULL;
  int nV = 0, i=0, j=0, value=0, maxGrau=0, len=0;
  char *nomef=NULL;

  E = (Edge *)malloc(sizeof(Edge));
  E->v=0;
  E->w=0;

  if(argc!=2){
    printf("Erro nos argumentos\n");
    return 1;
  }

  fIn = fopen(argv[1], "r");
  if(fIn==NULL){
    printf("Erro na abertura do ficheiro");
    return 1;
  }

  /*QUESTÃO 1*/
  fscanf(fIn, "%d", &nV);

  G=GRAPHinit(nV);

  for(i=0; i<nV; i++){
    for(j=0; j<nV; j++){
      fscanf(fIn, "%d", &value);
      if(value!=0){
        E->v=i;
        E->w=j;
        GRAPHinsertE(G, E, value);
      }
    }
  }

  /*QUESTÃO 2*/
  printf("Densidade do grafo = %.3f\n", ((float)(2*(G->E))/nV));

  /*QUESTÃO 3*/
  for(i=0; i<nV; i++){
    value=0;
    for(j=0; j<nV; j++){
      if(G->adj[i][j]!=0)
      value++;
    }
    if(maxGrau==0)
      maxGrau=value;
    if(value>maxGrau)
      maxGrau=value;
  }
  printf("Grau máximo = %d\n", maxGrau);

  /*QUESTÃO 4*/
  nomef = (char*)calloc(1, (strlen(argv[1]) - strlen(".adj") +
                                          strlen(".ram") + 1)*sizeof(char));
  if (nomef == NULL)
    exit(0);

  len = strlen(argv[1])-strlen(".adj");
  strncpy(nomef, argv[1], len);
  strcat(nomef, ".ram");

  fOut=fopen(nomef, "w");
  if(fOut==NULL)
    exit(0);

  fprintf(fOut, "%d\n%d\n", nV, G->E);
  for(i=0; i<nV;i++){
    for(j=i; j<nV; j++){
      if(G->adj[i][j]!=0){
        fprintf(fOut, "%d %d %d\n", i, j, G->adj[i][j]);
      }
    }
  }

  /*LIBERTAÇÃO DE MEMÓRIA*/
  free(nomef);
  free(E);
  DestroyGRAPH(G, nV);
  fclose(fIn);
  fclose(fOut);

  return 0;
}

/**DestroyGRAPH - destrói o grafo e liberta a memória alocada para o mesmo
  G - grafo a ser destruído
  nV - número de vértices do grafo
*/
void DestroyGRAPH(Graph *G, int nV){
  int i=0;
  for(i=0; i<nV; i++)
    free(G->adj[i]);
  free(G->adj);
  free(G);
}

/** MATRIXint - cria matriz para uso como grafo (matriz de adjacencias)
  lines - número de linhas da matriz a criar
  cols - número de colunas da matriz a criar
  n - valor com que se incializa a matriz

  retorna a matriz criada
*/
int **MATRIXint(int lines, int cols, int n){
  int **matrix = NULL;
  int i = 0, j=0;

  matrix=(int **)malloc(lines*sizeof(int*));

  for(i=0; i<lines; i++){
    matrix[i]=(int *)malloc(cols*sizeof(int));
  }

  for(i=0; i<lines; i++){
    for(j=0; j<cols; j++){
      matrix[i][j]=n;
    }
  }

  return matrix;
}

/** GRAPHinit - cria um grafo, em forma de matriz de adjacencias
  V - número de vértices
  Retorna o grafo criado
*/
Graph *GRAPHinit(int V)
{
  Graph *G = (Graph*) malloc(sizeof(Graph));
  G->V = V; G->E = 0;
  G->adj = MATRIXint(V, V, 0);
  return G;
}

/**GRAPHinsertE - insere uma aresta entre 2 vértices
  G - grafo a ser alterado
  V - vértices a serem ligados
*/
void GRAPHinsertE(Graph *G, Edge *e, int value){
  int v = e->v, w = e->w;
  if (G->adj[v][w] == 0) G->E++;
  G->adj[v][w] = value;
  G->adj[w][v] = value;
}
