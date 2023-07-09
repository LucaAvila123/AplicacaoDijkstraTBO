#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "PQ.h"
#include "item.h"
#include "lista.h"

#define TAM 300
#define FATOR_CONVERTE 3.6

int main(int argc, char *argv[]) {

  FILE *fileIn;
  fileIn = fopen(argv[1], "r");
  
  int N = 0, M = 0, S = 0, T = 0;
  double VM = 0;

  char* aux;
  char linha[TAM];
    
  // três primeiras linhas do arquivo sendo lidas
  // leitura do número de vértices e distancias
  if (fgets(linha, TAM, fileIn) != NULL) {
    aux = strtok(linha,";");
    N = atoi(aux);
    aux = strtok(NULL,";");
    M = atoi(aux);
    
  }

  // leitura de começo e fim do grafo
  if (fgets(linha, TAM, fileIn) != NULL) {

    aux = strtok(linha,";");
    S = atoi(aux);
    aux = strtok(NULL,";");
    T = atoi(aux);
    
  }
  // leitura da velocidade média inicial
  if (fgets(linha, TAM, fileIn) != NULL) {

    aux = strtok(linha,";");
    VM = atof(aux) / FATOR_CONVERTE; // converte de km/h para m/s
       
  }    
  
  // vetor de listas de distancias e tempos 
  Lista** distancias_tempos = (Lista**) malloc ((N+1)*sizeof(Lista*));
  for(int i=0; i<N+1; i++) distancias_tempos[i] = InicializaListaVazia();
  
  double distancia, tempo;
  // leitura das M linhas quem contem informações sobre as arestas  
  for(int i=0; i<M;i++){
    if (fgets(linha, TAM, fileIn) != NULL) {
      aux = strtok(linha,";");
      int id1 = atoi(aux);
            
      aux = strtok(NULL, ";");
      int id2 = atoi(aux);
            
      aux = strtok(NULL, ";");
      distancia = atof(aux);
      tempo = distancia / VM;
      Item item = make_item(id2, tempo);
      InsereNaLista(distancias_tempos[id1], item, distancia);
    
    }
  }
  // criação da heap usando o algoritmo
  PQ* heap = dijkstra(N, S, distancias_tempos);
  Item p = PQ_get(heap, T);
  double tempoDecorrido = 0;
  double instant=0, updatedSpeed=0; // foi colocado o valor do tempo do nó T para o caso de não haver atualizações
  
  // tentando fazer o caminho (ainda do inverso); S é o ponto inicial
  for(int i=N; prevId(p) != S; i--){
    p = PQ_get(heap, prevId(p));
  }
  p = PQ_get(heap, prevId(p));

  Celula* noTempo;
  Celula* noAtual;
  int uO=0, uD =0;
  int pontoParada = 0;

  FILE *fileOut = fopen(argv[2], "w");
  double distanciaTotal = 0;
  int linhaAtualizouDepois = 0;

  // leitura das linhas de atualização e trajetória do objeto no grafo
  while(id(p) != T){
     
    fprintf(fileOut, "%d;", id(p));
    tempoDecorrido += value(p);

    while((id(p) == S || tempoDecorrido - instant >= 0.001) && fgets(linha, TAM, fileIn) != NULL){
      aux = strtok(linha,";");
      instant = atof(aux);
      aux = strtok(NULL,";");
      uO = atoi(aux);
      aux = strtok(NULL,";");
      uD = atoi(aux);
      aux = strtok(NULL,";");
      updatedSpeed = atof(aux) / FATOR_CONVERTE;

      if(instant - tempoDecorrido >= 0.001){
        linhaAtualizouDepois = 1;
        break;
      }

      noTempo = FirstNode(distancias_tempos[uO]);
      while(noTempo && getId(noTempo) != uD)
        noTempo = getProx(noTempo);
      
      noTempo = changeTime(noTempo, returnDistancia(noTempo) / updatedSpeed);
    }

    noAtual = FirstNode(distancias_tempos[prevId(p)]);
    while(noAtual && getId(noAtual) != id(p))
      noAtual = getProx(noAtual);
    distanciaTotal += returnDistancia(noAtual);
  
    PQ_finish(heap);
    heap = dijkstra(N, id(p), distancias_tempos);
    pontoParada = id(p);

    p = PQ_get(heap, T);
    for(int i=N; prevId(p) != pontoParada; i--){
      p = PQ_get(heap, prevId(p));
    }

    if(linhaAtualizouDepois == 1){
      noTempo = FirstNode(distancias_tempos[uO]);
      while(noTempo && getId(noTempo) != uD)
        noTempo = getProx(noTempo);
      
      noTempo = changeTime(noTempo, returnDistancia(noTempo) / updatedSpeed);
      if(instant < tempoDecorrido){
        linhaAtualizouDepois = 0;
      } 
    }

  }
  fclose(fileIn);
  fprintf(fileOut, "%d\n", id(p));

  tempoDecorrido += value(p);
  
  noAtual = FirstNode(distancias_tempos[prevId(p)]);
  while(noAtual && getId(noAtual) != id(p))
    noAtual = getProx(noAtual);
  distanciaTotal += returnDistancia(noAtual);
  
  // print da distancia
  fprintf(fileOut, "%lf\n", distanciaTotal/1000); // dividindo por mil para conseguir valor em km
    
  // as próximas linhas são meramente formatação de tempo
  int horasDecorridas=0, minutosDecorridos=0;
  double segundosDecorridos=0;

  horasDecorridas = tempoDecorrido / 3600;
  minutosDecorridos = tempoDecorrido / 60 - horasDecorridas*60;
  segundosDecorridos = tempoDecorrido - horasDecorridas*3600 - minutosDecorridos*60;

  // print do tempo
  if(horasDecorridas < 10){
    fprintf(fileOut, "0");
  } 
  
  fprintf(fileOut, "%d:", horasDecorridas);

  if(minutosDecorridos < 10){
    fprintf(fileOut, "0");
  }
  
  fprintf(fileOut, "%d:", minutosDecorridos);

  if(segundosDecorridos < 10){
    fprintf(fileOut, "0");
  }
  fprintf(fileOut, "%lf\n", segundosDecorridos);

  // liberando a memoria
  fclose(fileOut);
  PQ_finish(heap);
  for(int i=0; i<N+1; i++){
    LiberaLista(distancias_tempos[i]);
  }
  free(distancias_tempos);

  return 0;
}
