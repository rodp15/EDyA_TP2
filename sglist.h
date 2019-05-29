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
GList glist_agregar_inicio(GList lista, void* dato);

/**
 * cantidad de elementos de la lista.
 */
int glist_size(GList lista);