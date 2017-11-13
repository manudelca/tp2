#define _POSIX_C_SOURCE 200809L
#include "strutil.h"
#include <string.h>
#include <stdlib.h>
#define ULTIM_STR_Y_NULL 2
#define CARACT_0 1

size_t contar_separador(const char* str, char sep){
  char actual=str[0];
  size_t cantidad_sep=0;
  size_t posicion=0;
  while(actual){
    if(actual==sep){
      cantidad_sep++;
    }
    posicion++;
    actual=str[posicion];
  }
  return cantidad_sep;
}

char* copiar_cadena(const char* cadena, char final, size_t largo, size_t* i){
  char* cadena_nueva=calloc(largo+CARACT_0,sizeof(char));
  char actual=cadena[0];
  size_t j=0;
  while(actual!='\0' && actual!=final){
    cadena_nueva[j]=actual;
    j++;
    *i += 1;
    actual=cadena[j];
  }
  cadena_nueva[j]='\0';
  if(actual==final)
    *i += 1;
  return cadena_nueva;
}

void free_strv(char* strv[]){
  size_t i=0;
  char* actual=strv[0];
  while(actual!=NULL){
    free(actual);
    i++;
    actual=strv[i];
  }
  free(strv);
  return;
}

char** split(const char* str, char sep){
  if(!sep)
    return NULL;
  size_t largo_str=strlen(str);
  size_t cantidad_sep=contar_separador(str,sep);
  char** split=malloc(sizeof(char*)*(cantidad_sep+ULTIM_STR_Y_NULL));
  if(!split)
    return NULL;
  size_t i=0;
  size_t j=0;
  while(str[i]){
    char* cadena_nueva=copiar_cadena(str+i,sep,largo_str,&i);
    if(!cadena_nueva){
      split[j]=NULL;
      free_strv(split);
      return NULL;
    }
    split[j]=cadena_nueva;
    j++;
  }
  if(largo_str==0){
    split[j]=strdup("");
    j++;
  }
  else if(str[i-1]==sep){
    split[j]=strdup("");
    j++;
  }
  split[j]=NULL;
  return split;
}
