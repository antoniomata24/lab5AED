#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"LinkedList.h"



int main(int argc, char *argv[]){

  FILE *fIn=NULL, *fOut = NULL;
  Edge *E = NULL;
  Graph *G = NULL;
  int nV = 0, i=0, weight=0, len=0, nE=0;
  char *nomef = NULL;
  link *aux=NULL;

  if(argc!=2){
    printf("Erro nos argumentos\n");
    return 1;
  }

  fIn=fopen(argv[1], "r");
  if(fIn==NULL){
    printf("Erro na abertura do ficheiro\n");
    return 1;
  }

  E = (Edge *)malloc(sizeof(Edge));
  E->v=0;
  E->w=0;

  fscanf(fIn, "%d", &nV);
  G=GRAPHinit(nV);

  fscanf(fIn, "%d", &nE);

  for(i=0;i<nE;i++){
    fscanf(fIn, "%d %d %d", &E->v, &E->w, &weight);
    GRAPHinsertE(G, E, weight);
  }

  nomef = (char*)calloc(1, (strlen(argv[1]) - strlen(".ram") +
                                          strlen(".ladj") + 1)*sizeof(char));
  if (nomef == NULL)
    exit(0);

  len = strlen(argv[1])-strlen(".ram");
  strncpy(nomef, argv[1], len);
  strcat(nomef, ".ladj");

  fOut=fopen(nomef, "w");
  if(fOut==NULL)
    exit(0);

  fprintf(fOut, "%d\n", G->V);
  for(i=0; i<nV;i++){
    aux=G->adj[i];
    while(aux!=NULL){
      fprintf(fOut, "%d:%d ", aux->v, aux->weight);
      aux=aux->next;
    }
    fprintf(fOut, "-1\n");
  }

  fclose(fIn);
  fclose(fOut);
  free(E);
  for(i=0;i<nV;i++){
    aux=G->adj[i];
    freeLAdj(aux);
  }
  free(G->adj);
  free(G);
  free(nomef);
  return 0;
}

void freeLAdj(link *Data){
    if(Data==NULL)
      return;
    freeLAdj(Data->next);
    free(Data);
}

link *NEW(int v, link *next, int weight)
{
  link *aux = next;
  link *first = next;
  link *x = (link *) malloc(sizeof(struct node));
  x->weight=weight;
  x->v = v;
  if(next==NULL){
    x ->next = next;
    return x;
  }else{
    while(aux->next!=NULL)
      aux=aux->next;
    aux->next=x;
    x->next=NULL;
    return first;
  }
}

Graph *GRAPHinit(int V)
{
  int v;
  Graph *G = (Graph*) malloc(sizeof(Graph));

  G->V = V;
  G->E = 0;
  G->adj = (link **) malloc(V * sizeof(link*));

  for (v = 0; v < V; v++)
    G->adj[v] = NULL;
  return G;
}

void GRAPHinsertE(Graph *G, Edge *e, int weight)
{
  int v = e->v, w = e->w;
  G->adj[v] = NEW(w, G->adj[v], weight);
  G->adj[w] = NEW(v, G->adj[w], weight);
  G->E++;
}
