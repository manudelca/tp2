#ifndef VISITAS_H
#define VISITAS_H

#include "hash.h"
#include "abb.h"

typedef struct sitio sitio_t;

/*Recibe los sitios con sus cantidades de visitas almacenados en un hash
y la cantidad de sitiosa imprimir en formato char*. Imprime por pantalla
los sitios mas visitados.*/
void ver_mas_visitados(hash_t* sitios, char* cantidad);

/*Recibe un arbol binario con las ips de los visitantes, una ip de inicio y otra
de fin e imprime por pantalla todas las ips que se encuentran dentro del rango.*/
void ver_visitantes(abb_t* visitantes,const char* ini,const char* fin);

/*Recibe los sitios con sus cantidades de visitas almacenados en un hash
y la cantidad de sitiosa imprimir en formato char*. Imprime por pantalla
los sitios mas visitados.*/
void ver_mas_visitados(hash_t* sitios, char* cantidad);

#endif
