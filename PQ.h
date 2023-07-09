#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "item.h"

typedef struct{
    Item *pq;
    int *map;
    int N;
} PQ;

PQ* PQ_init(int maxN); // cria uma min PQ com capacidade maxN
void PQ_insert(PQ*, Item);   // Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
Item PQ_delmin(PQ*);       // Remove Item com menor campo 'value' da PQ
void PQ_decrease_key(PQ* heap, int id, double value); // Muda a prioridade do nó com identificador 'id' para 'value'
Item PQ_min(PQ*);          // Retorna Item com menor campo 'value' da PQ
bool PQ_empty(PQ*);        // Retorna True se a PQ não tem elementos
int  PQ_size(PQ*);         // Número de elementos na PQ
void PQ_finish(PQ*);       // Libera memória
Item PQ_get(PQ* heap, int id);    // para encontrar o valor de um item específico
void PQ_change_prev_id(PQ* heap, int id, int prevId); // para mudar vértice imediatamente anterior

#endif
