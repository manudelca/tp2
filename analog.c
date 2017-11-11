#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "strutil.h"
#include "lista.h"
#include "abb.h"
#include "hash.h"
#include "heap.h"
#include "time.h"
#define TAM_MAX 100

typedef struct datos{
  abb_t* ips;
  hash_t* sitios_visitados;
  hash_t* detector_dos;
} datos_t;

typedef struct sitio{
  char* direccion;
  int cantidad;
}sitio_t;

/*Recibe un puntero a un int alocado dinamicamente y lo destruye.*/
void destruir_int(void* dato){
  int* n_int=dato;
  free(n_int);
  return;
}

/*Recibe un puntero a una lista y lo destruye*/
void destruir_listas_horarios(void* dato){
  lista_t* lista=dato;
  lista_destruir(lista,NULL);
  return;
}

/*Destruye un puntero a un datos_t*/
void datos_destruir(datos_t* datos){
  if(datos){
      hash_destruir(datos->sitios_visitados);
      hash_destruir(datos->detector_dos);
      abb_destruir(datos->ips);
  }
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

/*Recibe dos ips en formato de cadena y las compara.
Devuelve 1 si ip1>ip2; -1 si ip1<ip2; 0 si son iguales.*/
int comparar_ips(const char* ip1,const char* ip2){
  char** ip1_sep=split(ip1,'.');
  char** ip2_sep=split(ip2,'.');
  int resultado=0;
  for(size_t i=0; i<3;i++){
    int ip1_actual=atoi(ip1[i]);
    int ip2_actual=atoi(ip2[i]);
    if(ip1_actual>ip2_actual){
      resultado=1;
      break;
    }
    if(ip1_actual<ip2_actual){
      resultado=-1;
      break;
    }
  }
  free_strv(ip1_sep);
  free_strv(ip2_sep);
  return resultado;
}

/*Actualiza el contador del sitio almacenado en el hash pasado
por parametro. En caso de que el sitio no pertenezca, lo agrega.*/
bool actualizar_sitios_visitados(hash_t* hash,char* sitio){
  if(hash_pertenece(sitio)){
    int* cant_actual=hash_obtener(sitio);
    *cant_actual++;
    if(!hash_guardar(sitio,cant_actual))
      return false;
    return true;
  }
  size_t* cantidad=malloc(sizeof(size_t));
  *cantidad=1;
  if(!hash_guardar(sitio,cantidad))
    return false;
  return true;
}

/*Agrega el horario del log hecho por la ip pasado por parametro
en el hash. En caso de que la ip no se encuentre, la agrega.*/
bool agregar_log(hash_t* detector_dos, char* ip, char* hora){
  if(hash_pertenece(detector_dos, ip)){
    lista_t* lista=hash_obtener(detector_dos,ip);
    if(!lista_insertar_ultimo(lista,hora))
      return false;
    return true;
  }
  lista_t* lista=lista_crear();
  if(!lista_insertar_ultimo(lista,hora))
    return false;
  if(!hash_guardar(ip, lista)){
    lista_destruir(NULL);
    return false;
  }
  return true;
}

/*Recibe un nombre de archivo valido de logs y devuelve un datos_t
con la informacion recopilada de dicho archivo.*/
datos_t* procesar_logs(char* nombre_archivo){
  FILE* archivo=fopen(nombre_archivo,"r");
  if(!archivo)
    return NULL;
  datos_t* datos=malloc(sizeof(datos_t));
  if(!datos){
    fclose(archivo);
    return NULL;
  }
  hash_t* sitios_visitados=hash_crear(destruir_int);
  if(!hash){
    free(datos);
    fclose(archivo);
    return NULL;
  }
  hash_t* detector_dos=hash_crear(destruir_listas_horarios);//Aca habria que pasarle la funcion que destruye listas. Habria que hacerle un wrapper en realidad...
  if(!detector_dos){
    free(datos);
    hash_destruir(sitios_visitados);
    return NULL;
  }
  abb_t* ips=abb_crear(comparar_ips,free_strv);
  if(!abb){
    free(datos);
    hash_destruir(sitios_visitados);
    hash_destruir(detector_dos);
    return NULL;
  }
  char* linea=NULL;
  ssize_t leidos=getline(&linea,&capacidad,archivo_csv);
  while(leidos>2){
    linea[leidos-1]='\0';//Elimino el \n del final de la linea
    char** log_actual=split(linea,'\t');
    agregar_log(detector_dos,log_actual[0],log_actual[1]);
    actualizar_sitios_visitados(sitios_visitados,log_actual[3]);
    abb_guardar(ips,log_actual[0],log_actual);
    leidos=getline(&linea,&capacidad,archivo_csv);
  }
  free(linea);
  fclose(archivo_csv);
  datos->ips=ips;
  datos->sitios_visitados=sitios_visitados;
  datos->detector_dos=detector_dos;
  return datos;
}

void detectar_dos(hash_t* detector_dos){
  hash_iter_t* iter_hash=hash_iter_crear(detector_dos);
  if(!iter_hash)
    return;
  while(!hash_iter_al_final(iter_hash)){
    lista_t* lista=hash_obtener(detector_dos, hash_iter_ver_actual(iter_hash));
    if(lista_largo(lista)>4){
      iter_lista=lista_iter_crear(lista);
      if(!iter_lista)
        break;
      //Hay que pensar como iterar...
      //Como hago??? Para mi se hace de alguna forma independiente de la iteracion...
      //Si detecto alguno, imprimo directo

    }
    hash_iter_avanzar(iter_hash);
  }
  hash_iter_destruir(hash);
  return;
}

/*Recibe los sitios con sus cantidades de visitas almacenados en un hash
y la cantidad de sitiosa imprimir en formato char*. Imprime por pantalla
los sitios mas visitados.*/
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

int main(){
  datos_t* datos=NULL;
  char* input=calloc(TAM_MAX,sizeof(char));
  size_t capacidad=TAM_MAX;
  ssize_t largo_input=getline(&input,&capacidad,stdin);
  while(largo_input>=2){
    input[largo_input-1]='\0';
    char** comandos=split(input, ' ');
    if(strcmp(comandos[0],"agregar_archivo")==0 && comandos[1]){
      datos=procesar_logs(comandos[1]);
      if(!datos){
        fprintf(stderr, "Error\n");
        break;
      }
      detectar_dos(datos->detector_dos);
      fprintf(stdout, "OK\n");
    }
    else if(strcmp(comandos[0],"ver_visitantes")==0 && datos){

    }
    else if(strcmp(comandos[0],"ver_mas_visitados")==0 && comandos[1] && datos){
      ver_mas_visitados(datos->sitios_visitados,comandos[1]);
      fprintf(stdout, "OK\n");
    }
    else{
      fprintf(stderr, "Error en comando %s\n",comandos[0]);
      break;
    }
    largo_input=getline(&input,&capacidad,stdin);
  }
  free(input);
  if(datos)
    datos_destruir(datos);
  return 0;
}
