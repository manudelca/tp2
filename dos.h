#ifndef DOS_H
#define DOS_H

#include "lista.h"
#include "hash.h"

/*Recibe un hash con ips como claves y los horarios de los logs como valor e Imprime
por pantalla todos las ips sospechosas de ataques DoS*/
void detectar_dos(hash_t* detector_dos);

/*Recibe una lista con los horarios de los logs de una ip en formato de cadena y
devuelve true en caso de que la ip sea sospechosa de ataque dos.*/
bool es_dos(lista_t* lista);

#endif
