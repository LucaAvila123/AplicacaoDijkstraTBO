#include "PQ.h"
#include "item.h"
#include "lista.h"

#ifndef ALGORITMO_H
#define ALGOTIRMO_H

Item make_item(int id, double value); // função para criar um item

PQ* dijkstra(int N, int startingPoint, Lista** distanciasTempos); // algoritmo de dijkstra

#endif