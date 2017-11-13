#include <time.h>
#include <>
#include <stdlib.h>
#include "time.h"
#include "dos.h"

/*Recibe un iterador de una lista y lo avanza hasta la posicion pasada por parametro*/
void avanzar_iter_pos(lista_iter_t* iter,size_t i){
  for(size_t j=0;j<i && !lista_iter_al_final(iter);j++){
    lista_iter_avanzar(iter);
  }
  return;
}

bool es_dos(lista_t* lista){
  for(size_t i=0; i<lista_largo(lista);i++){
    iter_lista=lista_iter_crear(lista);
    if(!iter_lista)
      return false;
    avanzar_iter_pos(iter_lista,i);
    time_t anterior=lista_iter_ver_actual(iter);
    time_t actual;
    size_t contador=1;
    double tiempo_transcurrido=0;
    while(!lista_iter_al_final(iter)){
      lista_iter_avanzar(iter);
      actual=lista_iter_ver_actual(iter);
      double diferencia=difftime(actual,anterior);
      tiempo_transcurrido += diferencia;
      if (tiempo_transcurrido>=TIEMPO_MAX)
        break;
      anterior=actual;
      contador +=1;
      if(contador >=CANT_LOGS_MIN){
        lista_iter_destruir(iter_lista);
        return true;
      }
    }
    lista_iter_destruir(lista);
  }
  return false;
}

void detectar_dos(hash_t* detector_dos){
  hash_iter_t* iter_hash=hash_iter_crear(detector_dos);
  if(!iter_hash)
    return;
  while(!hash_iter_al_final(iter_hash)){
    lista_t* lista=hash_obtener(detector_dos, hash_iter_ver_actual(iter_hash));
    if(lista_largo(lista)>=5){
      if(es_dos(lista))
        fprintf(stdout, "DoS: %s\n",hash_iter_ver_actual(iter_hash));
    }
    hash_iter_avanzar(iter_hash);
  }
  hash_iter_destruir(hash);
  return;
}
