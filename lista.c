#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct cel{
    Item item;
    double distancia;
    Celula* prox;
};

struct lista{
    Celula* prim;
    Celula* ult;    
};

//cria lista 
Lista* InicializaListaVazia(){
    Lista* lista = (Lista*) calloc (1, sizeof(Lista));
    return lista; 
}

//insere elementos na lista 
void InsereNaLista(Lista* lista, Item item, double distancia){
    if(lista){
        Celula* nova = (Celula*) calloc (1, sizeof(Celula));

        nova -> item = item;
        nova -> distancia = distancia;
        if(!lista -> prim && !lista -> ult)
            lista -> prim = lista -> ult = nova;
        else{
            lista -> ult -> prox = nova;
            lista -> ult = nova;
            lista -> ult -> prox = NULL;
        }
    }
}

//imprime todos os itens da lista
void ImprimeLista(Lista* lista){
    if(lista){
        Celula* p = FirstNode(lista);
        while(p){
            printf("%d (%lf) -", id(p->item), value(p->item));
            p = p -> prox;
        }
    }
}

//libera a memória alocada da lista
void LiberaLista(Lista* lista){
    if(lista){
        Celula* p = lista -> prim;
        Celula* temp = NULL;
        while(p){
            temp = p -> prox;
            free(p);
            p = temp;
        }
        free(lista);
    }
}

Celula* FirstNode(Lista* lista){
    if(lista != NULL) return lista->prim;
    return NULL;
}

Celula* getProx(Celula* node){
    if(node != NULL) return node->prox;
    return NULL;
}

int getId(Celula* node){
    if(node != NULL) return id(node -> item);
    return 0;
}

double returnDistancia(Celula* node){
    if(node) return node -> distancia;
    return 0;
}

double returnTempo(Celula* node){
    if(node != NULL) return value(node -> item);
    return 0;
}

Celula* changeTime(Celula* node, double tempo){
    if(node != NULL) value(node -> item) = tempo;
    return node;
}