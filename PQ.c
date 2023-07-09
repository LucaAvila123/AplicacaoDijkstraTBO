#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

static void swap(PQ* heap, int i, int j) {
    exch(heap->pq[i], heap->pq[j]);
    heap->map[id(heap->pq[i])] = i;
    heap->map[id(heap->pq[j])] = j;
}

void fix_up(PQ* heap, Item *a, int k) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(heap, k, k/2);
        k = k/2;
    }
}

void fix_down(PQ* heap, Item *a, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(heap, k, j);
    k = j;
  }
}

PQ* PQ_init(int maxN) {
    PQ* heap = (PQ*) malloc (sizeof(PQ));
    heap->pq = (Item *) malloc((maxN+1) * sizeof (Item));
    heap->map = (int *) malloc((maxN+1) * sizeof (int));
    heap->N = 0;

    return heap;
}

void PQ_insert(PQ* heap, Item v) {
    if(heap == NULL) return;
    heap->N++;
    heap->pq[heap->N] = v;
    heap->map[id(v)] = heap->N;
    fix_up(heap, heap->pq, heap->N);
}

Item PQ_delmin(PQ* heap) {
    Item min = heap->pq[1];
    swap(heap, 1, heap->N);
    heap->N--;
    fix_down(heap, heap->pq, heap->N, 1);
    return min;
}

Item PQ_min(PQ* heap) {
    return heap->pq[1];
}

void PQ_decrease_key(PQ* heap, int id, double value) {
    int i = heap->map[id];
    value(heap->pq[i]) = value;
    fix_up(heap, heap->pq, i);
}

Item PQ_get(PQ* heap, int id){
    int i = heap->map[id];
    return heap->pq[i];
}

bool PQ_empty(PQ* heap) {
    return heap->N == 0;
}

int  PQ_size(PQ* heap) {
    return heap->N;
}

void PQ_finish(PQ* heap) {
    if(heap == NULL) return;
    free(heap->pq);
    free(heap->map);
    free(heap);
}

void PQ_change_prev_id(PQ* heap, int id, int prevId){
    int i = heap->map[id];
    prevId(heap->pq[i]) = prevId;
}
