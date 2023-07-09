#include <float.h>
#include "algoritmo.h"
#include "lista.h"
#include <stdio.h>

Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    value(t) = value;
    return t;
}

PQ* dijkstra(int N, int startingPoint, Lista** distanciasTempos){
    
    PQ* heap = PQ_init(N+1);
    // inserindo alguns elementos na PQ
    for(int i=1; i<=N; i++){
        PQ_insert(heap, make_item(i, DBL_MAX)); // colocando valor alto para simular infinito
    }
    // setando a prioridade do primeiro vértice (a posição no heap vai mudar)
    PQ_decrease_key(heap, startingPoint, 0);
    PQ_change_prev_id(heap, startingPoint, 0);
    
    // aplicando o algoritmo de Dijkstra
    while (!PQ_empty(heap)) {
        Item p = PQ_delmin(heap);
        Celula* celula = FirstNode(distanciasTempos[id(p)]);
        while(celula != NULL){
            if(value(PQ_get(heap, getId(celula))) > value(p) + returnTempo(celula)){
                PQ_decrease_key(heap, getId(celula), value(p) + returnTempo(celula));
                PQ_change_prev_id(heap, getId(celula), id(p));
            }
            celula = getProx(celula);
        }
    }
    return heap;
}