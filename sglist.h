#include <stdlib.h>
#include <stdio.h>

typedef struct _GNodo{
  void* dato;
  struct _GNodo *sig;
} GNodo;

typedef GNodo *GList;

typedef int (*Predicado) (TablaHash* tabla, void* dato);
typedef int (*Predicado2) (void* dato1, void* dato2);
typedef void* (*Copia) (void*);
typedef void (*Eliminadora) (GList);
typedef void (*Escritora) (FILE* fp, GList i);

GList filter(GList lista, Predicado f, Copia c);

GList filter2(GList lista, Predicado2 f, Copia c, void* dato);

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
void glist_eliminar_dato(void **lista, void *dato);

/**
 * cantidad de elementos de la lista.
 */
int glist_size(GList lista);

/**
 * Compara el dato de un nodo contra otro. Si son iguales retorna 1 sino 0.
 */
int valoresIguales(void *valor1, void *valor2);

/*
Elimina valores repetidos de la lista, por lo que la ocurrencia de cada valor es única
*/
void eliminar_repetidos(GList lista, Predicado2 valoresIguales, Copia c, Eliminadora e);

/*
Concatena dos listas
*/
GList concatenar_listas(GList lista1, GList lista2);
