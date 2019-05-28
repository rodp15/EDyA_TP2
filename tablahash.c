#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash, FuncionIgualdad igual, funcionesColisiones fc) {
  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash* tabla = malloc(sizeof(TablaHash));
  tabla->tabla = malloc(sizeof(CasillaHash) * capacidad);
  tabla->capacidad = capacidad;
  tabla->numElems = 0;
  tabla->hash = hash;
  tabla->igualdad = igual;
  tabla->manejoColisiones = fc;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx) {
    tabla->tabla[idx].clave = NULL;
    tabla->tabla[idx].inicioLE = NULL;
  }

  return tabla;
}


/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, void* clave, void* dato) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  // Old: Si el lugar estaba vacío, incrementamos el número de elementos.
  // New: En la nueva implementacion, siempre deberiamos incrementar el numero de elementos, porque siempre se insertan 
  // aunque la casilla ya tuviese algo.
  //if (tabla->tabla[idx].clave == NULL)
  
  tabla->numElems++;

  // Almacenamos los datos ingresados.
  // La calve se sigue ingresando de la misma manera.
  tabla->tabla[idx].clave = clave;
  // El dato ahora se inserta con la funcion de encadenar que arma la lista enlazada
  //tabla->tabla[idx].dato = dato;
  (tabla->manejoColisiones).encadenar( &(tabla->tabla[idx].inicioLE), dato);
}

/**
 * Busca un elemento dado en la tabla, y retorna un puntero al mismo.
 * En caso de no existir, se retorna un puntero nulo.
 */
void* tablahash_buscar(TablaHash* tabla, void* clave) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  // Si el lugar esta vacío, retornamos un puntero nulo.
  if (!(tabla->igualdad(tabla->tabla[idx].clave, clave)))
    return NULL;

  // La funcion buscarEnLista va a ser la funcion que recorre la LE y busca por la clave.
  // Esto es porque para nosotros la clave es el mismo valor. TODO revisar esto
  return (tabla->manejoColisiones).buscarEnLista(tabla->tabla[idx].inicioLE, clave);
}

/**
 * Elimina un elemento de la tabla.
 */
void tablahash_eliminar(TablaHash* tabla, void* clave) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  // Si el lugar estaba ocupado, decrementamos el número de elementos.
  if (tabla->tabla[idx].clave != NULL)
    tabla->numElems--;

  // Vaciamos la casilla.
  // TODO No se deberia liberar el contenido de los punteros ademas?
  
  // Primero hay que borrar el elemento de la lista enlazada
  (tabla->manejoColisiones).eliminarLista( &(tabla->tabla[idx].inicioLE), clave );

  // Despues hay que ver si la lista enlazada quedo vacia, de ser asi si seteamos la calve a NULL, sino no.
  if(tabla->tabla[idx].inicioLE == NULL)
    tabla->tabla[idx].clave = NULL;
}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla) {
  free(tabla->tabla);
  free(tabla);
}
