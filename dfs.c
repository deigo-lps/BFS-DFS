//Diego Lopes da Silva, Atividade DFS, ED2.
#include<stdio.h>
#include<stdlib.h>

typedef struct node{
  int vertice;
  struct node *prox;
}Node;

Node* criaNo(int v){
  Node *newNode=malloc(sizeof(Node));
  newNode->vertice=v;
  newNode->prox=NULL;
  return newNode;
}

typedef struct grafo{
  int numVertices;
  Node **adjList;
  int *visitado;
}Grafo;

Grafo* criaGrafo(int vertices){
  Grafo *grafo=malloc(sizeof(Grafo));
  grafo->numVertices=vertices;

  grafo->adjList=malloc(vertices * sizeof(Node));
  grafo->visitado=malloc(vertices * sizeof(int));

  int i;
  for(i=0;i<vertices;i++){
    grafo->adjList[i]=NULL;
    grafo->visitado[i]=0;
  }
  return grafo;
}

void addAresta(Grafo *grafo,int origem,int destino){
  // adiciona aresta de origem para destino
  Node *novoNo=criaNo(destino);
  //proximo do destino é o primeiro da lista de adjacencias de origem
  novoNo->prox=grafo->adjList[origem];
  //destino se torna o primeiro da lista de adjacencias de origem
  grafo->adjList[origem]=novoNo;

  // adiciona aresta de destino para origem
  novoNo=criaNo(origem);
  // proximo da origem é o primeiro da lista de adjacencias de destino
  novoNo->prox=grafo->adjList[destino];
  //primeiro da lista de adjacencias de destino é origem.
  grafo->adjList[destino]=novoNo;
}


//Algoritmo DFS
void dfs(Grafo *grafo, int vertice) {
  //recebe a lista de adjacencias de vertice
  Node *adjList = grafo->adjList[vertice];
  Node *aux = adjList;

  //marca vertice como visitado
  grafo->visitado[vertice] = 1;
  printf("Visitado %d \n", vertice);

  // passa pela lista de adjacencias
  while (aux != NULL) {
    int verticeConectado = aux->vertice;

    //se o vertice não tiver sido visitado, chama a função recursivamente
    if (grafo->visitado[verticeConectado] == 0) {
      dfs(grafo, verticeConectado);
    }
    aux = aux->prox;
  }
}

int main(){
  Grafo *grafo=criaGrafo(6);
  addAresta(grafo, 0, 1);
  addAresta(grafo, 0, 2);
  addAresta(grafo, 1, 2);
  addAresta(grafo, 1, 4);
  addAresta(grafo, 1, 3);
  addAresta(grafo, 2, 4);
  addAresta(grafo, 3, 4);

  dfs(grafo, 0);

  return 0;
}

