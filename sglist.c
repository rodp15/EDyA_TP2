#include <stdlib.h>
#include <wchar.h>
#include "sglist.h"

int glist_vacia(GList lista) {
  return lista == NULL;
}

GList glist_crear() {
  return NULL;
}

void glist_agregar_inicio(void **lista, void *p) {
  GList *inicioLE = (GList*)lista;
  GNodo *nuevoNodo = malloc(sizeof(GNodo));
  nuevoNodo->dato = p;
  nuevoNodo->sig = *inicioLE;
  *inicioLE = nuevoNodo;
}

int valoresIguales(void *valor1, void *valor2){
  if(wcscmp( (wchar_t*)valor1, (wchar_t*)valor2 ) == 0)
    return 1;

  return 0;
}

void* glist_buscar(void *lista, void *dato) {
  GList inicioLE = (GList)lista;
  for(; !glist_vacia(inicioLE) && !valoresIguales(inicioLE->dato, dato); inicioLE = inicioLE->sig);
  if(glist_vacia(inicioLE)){
    return NULL;
  } else {
    return inicioLE->dato;  
  }
}

void glist_eliminar_nodo(void **lista, void *dato){
  // TODO revisar esta funcion
  GList *inicioLEReal = (GList*)lista;
  
  // Si el inicio de la lista es vacio no hago nada
  if(glist_vacia(*inicioLEReal))
    return;

  // Si el primer dato de la lista es el dato, lo elimino y apunto al segundo nodo
  if(valoresIguales( (*inicioLEReal)->dato, dato )){
    GList aux = (*inicioLEReal)->sig;
    free(*inicioLEReal);
    *inicioLEReal = aux;
  }

  // Sino recorro la lista hasta encontrar el nodo con el dato
  // se hace un puntero auxiliar para no modificar la lista real.
  GList inicioLEAux = *inicioLEReal;
  for(; !glist_vacia(inicioLEAux->sig) && !valoresIguales(inicioLEAux->sig->dato, dato) ; inicioLEAux = inicioLEAux->sig);
  
  // Si llegue al final de la lista, no hago nada.
  // Sino, debo eliminar el nodo que tiene el dato
  if(glist_vacia(inicioLEAux->sig)){
    return;
  } else {
    GList aux = inicioLEAux->sig;
    inicioLEAux->sig = inicioLEAux->sig->sig;
    free(aux);
  }
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

/*
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
*/

