#include <stdbool.h>
#include <stdlib.h>

typedef struct heap heap_t;

/*Funcion de comparacion que devuelve >0 si a>b; ==0 si a==b; <0 si a<b.*/
typedef int (*cmp_func_t) (const void *a, const void *b);

/*Recibe una funcion de comparacion de tipo cmp_func_t y crea el heap. Devuelve
NULL en caso de error.
  Pre: La funcion cmp es una funcion de comparacion valida.*/
heap_t *heap_crear(cmp_func_t cmp);

/*Recibe un arreglo junto con su cantidad de elementos y una funcion de comparacion
y devuelve un heap formado por los elementos del arreglo.*/
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp);

/*Recibe un heap y una funcion para destruir sus elementos y lo destruye liberando memoria.*/
void heap_destruir(heap_t *heap, void destruir_elemento(void *e));

/*Recibe un heap y devuelve la cantidad de elementos en el mismo.*/
size_t heap_cantidad(const heap_t *heap);

/*Recibe un heap y devuelve true si el heap esta vacio.*/
bool heap_esta_vacio(const heap_t *heap);

/*Recibe un heap y un elemento y lo encola. Devuelve false en caso de error.*/
bool heap_encolar(heap_t *heap, void *elem);

/*Recibe un heap y devuelve el maximo elemento del mismo. Devuelve NULL en caso
de que el heap se encuentre vacio.*/
void *heap_ver_max(const heap_t *heap);

/*Desencola el proximo elemento del heap. Devuelve NULL en caso de encontrarse vacio.*/
void *heap_desencolar(heap_t *heap);

/*Recibe un arreglo de elementos, su cantidad y una funcion de comparacion y ordena
los elementos del arreglo.*/
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp);
