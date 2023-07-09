#ifndef LISTA_H
#define LISTA_H

#include "item.h"
typedef struct lista Lista;
typedef struct cel Celula;

Lista* InicializaListaVazia();

void InsereNaLista(Lista* lista, Item item, double distancia);

Celula* FirstNode(Lista* lista);
Celula* getProx(Celula* node);

int getId(Celula* node);
double returnDistancia(Celula* node);
double returnTempo(Celula* node);
Celula* changeTime(Celula* node, double tempo);

void ImprimeLista(Lista* lista);

void LiberaLista(Lista* lista);

#endif