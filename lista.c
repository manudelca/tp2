#include "lista.h"
#include <stdlib.h>

typedef struct nodo{
  void* dato;
  struct nodo* prox;
} nodo_t;

typedef struct lista{
  nodo_t* prim;
  nodo_t* ult;
  size_t largo;
} lista_t;

lista_t* lista_crear(){
  lista_t* lista=malloc(sizeof(lista_t));
  lista->prim=NULL;
  lista->ult=NULL;
  lista->largo=0;
  return lista;
}

bool lista_esta_vacia(const lista_t* lista){
  return lista->largo==0;
}

/*Crea y devuelve un nodo que almacena el dato pasado por parametro y apunta
al nodo pasado por parametro. En caso de error, devuelve NULL.*/
nodo_t* nodo_crear(void* dato, void* prox){
  nodo_t* nodo=malloc(sizeof(nodo_t));
  if(!nodo)
    return NULL;
  nodo->dato=dato;
  nodo->prox=prox;
  return nodo;
}

bool lista_insertar_primero(lista_t* lista, void* dato){
  nodo_t* nodo=nodo_crear(dato,lista->prim);
  if(!nodo)
    return false;
  lista->prim=nodo;
  if (lista->largo==0)
    lista->ult=nodo;
  lista->largo +=1;
  return true;
}

bool lista_insertar_ultimo(lista_t* lista,void* dato){
  nodo_t* nodo=nodo_crear(dato, NULL);
  if(!nodo)
    return false;
  if(lista->ult)
    lista->ult->prox=nodo;
  lista->ult=nodo;
  if(lista->largo==0)
    lista->prim=nodo;
  lista->largo +=1;
  return true;
}

void* lista_borrar_primero(lista_t* lista){
  if (lista->largo==0)
    return NULL;
  void* dato=lista->prim->dato;
  nodo_t* prox=lista->prim->prox;
  free(lista->prim);
  lista->prim=prox;
  if(!lista->prim)
    lista->ult=NULL;
  lista->largo -=1;
  return dato;
}

void* lista_ver_primero(const lista_t* lista){
  return lista->prim?lista->prim->dato:NULL;
}

void* lista_ver_ultimo(const lista_t* lista){
  return lista->ult?lista->ult->dato:NULL;
}

size_t lista_largo(const lista_t* lista){
  return lista->largo;
}

void lista_destruir(lista_t* lista, void destruir_dato(void*)){
  nodo_t* actual=lista->prim;
  while(actual){
    if(destruir_dato)
      destruir_dato(actual->dato);
    nodo_t* prox=actual->prox;
    free(actual);
    actual=prox;
  }
  free(lista);
  return;
}

void lista_iterar(lista_t* lista, bool (*visitar)(void* dato, void* extra),void* extra){
  if(!visitar)
    return;
  nodo_t* actual=lista->prim;
  while(actual){
    if(!visitar(actual->dato, extra))
      return;
    actual=actual->prox;
  }

}

typedef struct lista_iter{
  lista_t* lista;
  nodo_t* actual;
  nodo_t* anterior;
} lista_iter_t;

lista_iter_t* lista_iter_crear(lista_t* lista){
  lista_iter_t* iter=malloc(sizeof(lista_iter_t));
  iter->lista=lista;
  iter->actual=lista->prim;
  iter->anterior=NULL;
  return iter;
}

bool lista_iter_avanzar(lista_iter_t* iter){
  if(lista_iter_al_final(iter))
    return false;
  iter->anterior=iter->actual;
  iter->actual=iter->actual->prox;
  return true;
}

void* lista_iter_ver_actual(const lista_iter_t* iter){
  return iter->actual?iter->actual->dato:NULL;
}

bool lista_iter_al_final(const lista_iter_t* iter){
  return !iter->actual;
}

void lista_iter_destruir(lista_iter_t* iter){
  free(iter);
  return;
}

bool lista_iter_insertar(lista_iter_t* iter, void* dato){
  nodo_t* nodo=nodo_crear(dato,iter->actual);
  if(!nodo)
    return false;
  iter->actual=nodo;
  if(!iter->anterior){
    iter->lista->prim=nodo;
  }
  else{
    iter->anterior->prox=nodo;
  }
  if(!nodo->prox)
    iter->lista->ult=nodo;
  iter->lista->largo +=1;
  return true;
}

void* lista_iter_borrar(lista_iter_t* iter){
  if(!iter->actual)
    return NULL;
  void* dato=iter->actual->dato;
  nodo_t* proximo=iter->actual->prox;
  if(!iter->anterior){
    iter->lista->prim=proximo;
  }
  else{
    iter->anterior->prox=proximo;
  }
  if(!proximo)
    iter->lista->ult=iter->anterior;
  free(iter->actual);
  iter->actual=proximo;
  iter->lista->largo -= 1;
  return dato;
}
