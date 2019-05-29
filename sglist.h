#include <stdlib.h>
#include <stdio.h>

typedef struct _GNodo{
  void* dato;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *GList;

typedef int (*Predicado) (void* dato);
typedef void* (*Copia) (void*);
typedef void (*Eliminadora) (GList);
typedef void (*Escritora) (FILE* fp, GList i);

GList filter(GList lista, Predicado f, Copia c);

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista, Eliminadora e);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
void glist_agregar_inicio(void **lista, void* dato);

/**
 * Agrega un elemento busca un elemento de la lista, y lo retorna si esta.
 */
void* glist_buscar(void *lista, void *dato);

/**
 * Elimina un elemento de la lista.
 */
void glist_eliminar_nodo(void **lista, void *dato);

/**
 * cantidad de elementos de la lista.
 */
int glist_size(GList lista);

/**
 * Compara el dato de un nodo contra otro. Si son iguales retorna 1 sino 0.
 */
int valoresIguales(void *valor1, void *valor2);