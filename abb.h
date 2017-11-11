#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>

/* Los structs deben llamarse "abb" y "abb_iter".*/
typedef struct abb abb_t;

/*Funcion para comparar una clave pasada por parametro con una clave de posicion
 * actual del abb.
 * Debe devolver 0 si los elementos comparados son iguales. Un número menor a 0
 * si el primer elemento es menor al segundo, o mayor a 0 si es mayor.*/
typedef int (*abb_comparar_clave_t) (const char *, const char *);

/* Tipo de función para destruir dato.*/
typedef void (*abb_destruir_dato_t) (void *);


/* Crea el abb*/
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/* Guarda un elemento en el abb, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura abb fue inicializada
 * Post: Se almacenó el par (clave, dato) */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);


/* Borra un elemento del abb y devuelve el dato asociado.  Devuelve
 * NULL si el dato no se encuentra.
 * Pre: La estructura abb fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado. */
void *abb_borrar(abb_t *arbol, const char *clave);

/* Obtiene el valor de un elemento del abb, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura abb fue inicializada
 * Post: Devuelve un elemento*/
void *abb_obtener(const abb_t *arbol, const char *clave);

/* Determina si clave pertenece o no al abb, devolviendo True o False.
 * Pre: La estructura abb fue inicializada */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* Devuelve la cantidad de elementos del abb.
 * Pre: La estructura abb fue inicializada
 * Pos: Devuelve cantidad de elementos del abb*/
size_t abb_cantidad(abb_t *arbol);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura abb fue inicializada
 * Post: La estructura abb fue destruida */
void abb_destruir(abb_t *arbol);

/****************************************************************************
*                         ITERADOR INTERNO                                  *
****************************************************************************/


/* Iterador interno in orden.*/
/* Crea un iterador in orden.
 * Pre: El abb fue creado, fue creada la funcion para pasar por parametro.
 * Pos: Modifica el abb segun la funcion que se le pasa por parametro.*/
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/*Iterador interno in orden con inicio y fin.
  Recibe una clave de inicio y otra de fin y aplica la funcion de visitar a los
elementos del arbol que se encuentran en ese rango.*/
void abb_in_order_mod(abb_t* arbol,const char* ini,const char* fin, bool visitar(const char*,void*,void*),void* extra);

/****************************************************************************
*                         ITERADOR EXTERNO                                  *
****************************************************************************/

/*Estructura del Iterador externo*/
typedef struct abb_iter abb_iter_t;

/* Iterador del abb */
/* Crea iterador in orden.
 * En caso de error, devuelve NULL.
 * Pre: El abb fue creado.
 * Post: Devuelve un iterador.*/
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

/* Devuelve True o False si se pudo avanzar el iterador al siguiente elemento.
En caso de que esté al final del iterador, devuelve false.
 * Pre: El iterador fue creado.*/
bool abb_iter_in_avanzar(abb_iter_t *iter);

/*Devuelve clave actual, esa clave no se puede modificar ni liberar.  Si se está al final del iterador, devuelve NULL.
 * Pre: el iterador fue creado.
 * Post: Se devolvió la clave de la posición actual del iterador.*/
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

/* Devuelve verdadero o falso, si el iterador llegó al final.
 * Pre: el iterador fue creado.*/
bool abb_iter_in_al_final(const abb_iter_t *iter);

/* Destruye iterador*/

void abb_iter_in_destruir(abb_iter_t* iter);

#endif // ABB_H
