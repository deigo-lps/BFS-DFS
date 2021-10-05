//Diego Lopes da Silva, Atividade BFS, ED2.
#include<stdio.h>
#include<stdlib.h>

typedef struct fila{
  int itens[40];
  int head;
  int tail;
} Fila;

Fila* criaFila(){
  Fila *fila=malloc(sizeof(Fila));
  fila->head=-1;
  fila->tail=-1;
  return fila;
}

int vazia(Fila *fila){
  if(fila->tail == -1)
    return 1;
  else
    return 0;
}

void addFila(Fila *fila, int valor){
  if (fila->tail == 40-1)
    printf("Fila cheia.\n");
  else{
    if(fila->head==-1)
      fila->head=0;
    fila->tail++;
    fila->itens[fila->tail]=valor;
  }
}

int removeFila(Fila *fila){
  int item;
  if(vazia(fila)){
    printf("fila vazia\n");
    item=-1;
  }
  else{
    item=fila->itens[fila->head];
    fila->head++;
    if(fila->head > fila->tail){
      printf("\nresetando fila");
      fila->head=fila->tail=-1;
    }
  }
  return item;
}

void printar(Fila *fila){
  int i=fila->head;
  if(vazia(fila))
    printf("Fila vazia.\n");
  else{
    printf("Fila contem \n");
    for(i=fila->head;i<=fila->tail;i++)
      printf("%d ",fila->itens[i]);
  }
}

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


//Algoritmo BFS
void bfs(Grafo *grafo, int verticeInicial){
  //cria fila
  Fila *fila=criaFila();
  //marca vertice inicial como visitado e adiciona na fila
  grafo->visitado[verticeInicial]=1;
  addFila(fila,verticeInicial);

  while(!vazia(fila)){
    printar(fila);
    //recebe primeiro elemento da fila ao passo de que remove da fila.
    int verticeAtual=removeFila(fila);
    printf("\nVisitado: %d\n",verticeAtual);

    //recebe lista de adjacencias do vertice atual
    Node *aux=grafo->adjList[verticeAtual];

    while(aux){
      //recebe valor do vertice adjacente
      int verticeAdjacente=aux->vertice;
      //se não tiver sido visitado
      if(grafo->visitado[verticeAdjacente] == 0){
        //marca como visitado e adiciona à fila.
        grafo->visitado[verticeAdjacente] = 1;
        addFila(fila,verticeAdjacente);
      }
      //passa para proximo vertice da lista de adjacencias.
      aux=aux->prox;
    }
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

  bfs(grafo, 0);

  return 0;
}

