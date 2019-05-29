#include <stdio.h>
#include <stdlib.h>
#include "sglist.h"

int glist_vacia(GList lista) {
  return lista == NULL;
}

GList glist_crear() {
  return NULL;
}

GList glist_agregar_inicio(GList lista, void* p) {
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = p;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void glist_destruir(GList lista, Eliminadora e) {
  GNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    e(nodoAEliminar);
    free(nodoAEliminar);
  }
}

int glist_size(GList lista){
	int cant=0;
	for (GNodo *nodo = lista; nodo != NULL; cant++, nodo = nodo->sig);

	return cant;
}

GList filter(GList lista, Predicado f, Copia c){
  GList listaRetorno=glist_crear();
  for(GList i=lista;i != NULL;i=i->sig){
    if(f(i->dato)){
      void *nuevoNodo=c(i->dato);
      listaRetorno=glist_agregar_inicio(listaRetorno,nuevoNodo);
    }
  }

  return listaRetorno;
}


