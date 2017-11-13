#include <stdbool.h>
#include <stdlib.h>

typedef struct lista lista_t;

/*Crea una lista.
  Post: devuelve una nueva lista vacia.*/
lista_t* lista_crear();

/*Devuelve verdadero o falso, de acuerdo a si la lista tiene o no elementos.
  Pre: la lista fue creada.*/
bool lista_esta_vacia(const lista_t* lista);

/*Agrega un elemento a la lista. Devuelve falso en caso de error.
  Pre: la lista fue creada.
  Post: el elemento fue insertado en la primera posicion. */
bool lista_insertar_primero(lista_t* lista, void* dato);

/*Agrega un elemento a la lista. Devuelve falso en caso de error.
  Pre: la lista fue creada.
  Post: el elemento fue insertado en la ultima posicion.*/
bool lista_insertar_ultimo(lista_t* lista, void* dato);

/*Borra el primer elemento de la lista y lo devuelve. Si la lista no tiene elementos,
devuelve NULL.
  Pre: la lista fue creada.
  Post: se devuelve el primer elemento en caso de que no este vacia.*/
void* lista_borrar_primero(lista_t* lista);

/*Devuelve el primer elemento de la lista. Si la lista esta vacia, devuelve NULL.
  Pre: la lista fue creada.
  Post: se devuelve el primer elemento si la lista no esta vacia.*/
void* lista_ver_primero(const lista_t* lista);

/*Devuelve el ultimo elemento de la lista. Si la lista esta vacia, devuelve NULL.
  Pre: la lista fue creada.
  Post: se devuelve el ultimo elemento si la lista no se encuentra vacia.*/
void* lista_ver_ultimo(const lista_t* lista);

/*Devuelve el largo de la lista.
  Pre: la lista fue creada.
  Post: se devuelve el largo de la lista.*/
size_t lista_largo(const lista_t* lista);

/*Destruye la lista. Si recibe la funcion destruir_dato, llama a dicha funcion
para cada uno de los elementos de la lista.
  Pre: la lista fue creada. destruir_dato es una funcion capaz de destruir los
elementos almacenados, o NULL en caso de que no sea necesaria.
  Post: se elimino la lista y todos sus elementos.*/
void lista_destruir(lista_t* lista, void destruir_dato(void*));

/*Recibe una lista y una funcion visitar. Itera a lo largo de la lista aplicando,
dicha funcion a cada dato de la lista.
  Pre: la lista fue creada. La funcion visitar devuelve un booleano.
  Post: la lista es modificada de acuerdo con la funcion pasada por parametro.
Si la funcion devuelve false para algun elemento, la iteracion se corta.*/
void lista_iterar(lista_t* lista, bool (*visitar)(void* dato, void* extra), void* extra);

typedef struct lista_iter lista_iter_t;

/*Crea un iterador de la lista pasada por parametro.
  Pre: la lista fue creada. No se utilizaran primitivas de la lista que modifiquen
la misma mientras se utilice el iterador.
  Post: devuelve el iterador creado que se encuentra sobre la primera posicion.*/
lista_iter_t* lista_iter_crear(lista_t* lista);

/*Avanza el iterador en una posicion. Devuelve false en caso de error.
  Pre: el iterador fue creado.
  Post: el iterador avanza una posicion.*/
bool lista_iter_avanzar(lista_iter_t* iter);

/*Devuelve el elemento sobre el que se encuentra parado el iterador. Si se
encuentra al final, devuelve NULL.
  Pre: el iterador fue creado.
  Post: se devuelve el elemento sobre el que esta el iterador.*/
void* lista_iter_ver_actual(const lista_iter_t* iter);

/*Devuelve true en caso de que el iterador se encuentre al final de la lista, es decir
a continuacion del ultimo elemento. false en caso de que no.
  Pre: el iterador fue creado.
  Post: Devuelve un booleano de acuerdo a si esta o no al final.*/
bool lista_iter_al_final(const lista_iter_t* iter);

/*Destruye el iterador.
  Pre: el iterador fue creado.*/
void lista_iter_destruir(lista_iter_t* iter);

/*Inserta el dato pasado por parametro en la lista.
  Pre: la lista y el iterador fueron creados.
  Post: Agrega el elemento en la posicion en que se encuentra el iterador.*/
bool lista_iter_insertar(lista_iter_t* iter, void* dato);

/*Borra el elemento sobre el que se encuentra el iterador de la lista y lo devuelve.
  Pre: la lista no esta vacia. El iterador fue creado.
  Post: el elemento eliminado es devuelto.*/
void* lista_iter_borrar(lista_iter_t* iter);
