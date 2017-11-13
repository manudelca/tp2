#include <stdlib.h>
#include <stdio.h>
#include "visitas.h"
#include "heap.h"

struct sitio{
  char* direccion;
  int cantidad;
};

/*Recibe una ip y la imprime por pantalla. (Funcion para abb inorder)*/
bool imprimir_ip(const char* ip,void* valor ,void* extra){
  fprintf(stdout,"\t%s\n",ip);
  return true;
}

void ver_visitantes(abb_t* visitantes,const char* ini,const char* fin){
  fprintf(stdout, "Visitantes:\n");
  abb_in_order_mod(visitantes,ini,fin,imprimir_ip,NULL);
  return;
}

/*Recibe dos punteros tipo sitio_t y los compara. Devuelve 1 si a<b;
-1 si a>b y 0 si son iguales. (Estan invertidos para que sea un heap de minimos)*/
int comparar_sitios(const void *a, const void *b){
  sitio_t* a_sitio=a;
  sitio_t* b_sitio=b;
  if( a->cantidad < b->cantidad)
    return 1;
  if(a->cantidad > b->cantidad)
    return -1;
  return 0;
}

void ver_mas_visitados(hash_t* sitios, char* cantidad){
  int n=atoi(cantidad);
  heap_t* heap_min=heap_crear(comparar_sitios);
  hash_iter_t* iter_hash=hash_iter_crear(sitios);
  for(int i=0;i<n && !hash_iter_al_final(iter_hash);i++){
    char* sitio=hash_iter_ver_actual(iter_hash)
    int* cantidad=hash_obtener(sitios, sitio);
    sitio_t actual;
    actual.direccion=sitio;
    actual.cantidad=*cantidad;
    heap_encolar(heap_min,&actual);
    hash_iter_avanzar(iter_hash);
  }
  while(!hash_iter_al_final(iter_hash)){
    char* direccion=hash_iter_ver_actual(iter_hash);
    int* cantidad=hash_obtener(sitios,direccion);
    sitio_t actual;
    actual.direccion=direccion;
    actual.cantidad=*cantidad;
    if(comparar_int(&actual,heap_ver_max(heap_min))==-1){
      heap_desencolar(heap_min);
      heap_encolar(actual);
    }
    hash_iter_avanzar(iter_hash);
  }
  fprintf(stdout, "Sitios mas visitados:\n");
  while(!heap_esta_vacio(heap_min)){
    sitio_t* actual=heap_desencolar(heap_min);
    fprintf(stdout, "\t%s - %d\n",actual->direccion,actual->cantidad);
  }
  heap_destruir(heap_min,NULL);
  hash_iter_destruir(iter_hash);
  return;
}
