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

void glist_eliminar_dato(void **lista, void *dato){
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
  GList nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    e(nodoAEliminar);
    free(nodoAEliminar);
  }
}

/*
GList glist_borrar_nodo(GList lista, GList nodoAEliminar){

}
*/

void borrarint(GList nodo){
  free(nodo->dato);
}

int glist_size(GList lista){
	int cant=0;
	for (GNodo *nodo = lista; nodo != NULL; cant++, nodo = nodo->sig);

	return cant;
}

void eliminar_repetidos(GList lista, Predicado2 valoresIguales, Copia c, Eliminadora e){
  GList resultado;
  for (; lista != NULL; lista = lista->sig){
    resultado=filter2(lista->sig, valoresIguales, c, lista->dato);
    glist_destruir(lista->sig, e);
    lista->sig = resultado;
  }
}


GList filter(GList lista, Predicado f, Copia c){
  GList listaRetorno=glist_crear();
  for(GList i=lista;i != NULL;i=i->sig){
    if(f(i->dato)){
      void *nuevoNodo=c(i->dato);
      /*listaRetorno=*/glist_agregar_inicio(((void**)&listaRetorno),nuevoNodo);
    }
  }

  return listaRetorno;
}

// TODO, ver que hacer con esto
GList filter2(GList lista, Predicado2 f, Copia c, void* dato){
  GList listaRetorno=glist_crear();
  for(GList i=lista; i != NULL; i=i->sig){
    if(f(i->dato,dato)){
      void *nuevoNodo=c(i->dato);
      glist_agregar_inicio(((void**)&listaRetorno),nuevoNodo);
    }
  }

  return listaRetorno;
}

// TODO ver que ande copiar_palabra
void* copiar_palabra(void* dato){
  void* copia= malloc(sizeof(wchar_t)*(wcslen(((wchar_t*)dato)))+1);
  wcscpy(copia,dato);
  return copia;
}


void* copiar_int(void* dato){
  void* copia = malloc(sizeof(int));
  *((int*)copia) = *((int*)dato);
  return copia;
}

int intNoIguales(void* dato1, void* dato2){
  return (*((int*)dato1)) != (*((int*)dato2));
}


int main(){
  GList l = glist_crear();
  int *j, *k;

  for (int i = 0; i < 5; ++i)
  {
    j = malloc(sizeof(int));
    k = malloc(sizeof(int));
    *j=i;
    *k=i;
    glist_agregar_inicio(((void**)&l),(void*)(j));
    glist_agregar_inicio(((void**)&l),(void*)(k));
  }

  for (GList i = l; i != NULL; i=i->sig)
  {
    printf("%d\n",*((int*)(i->dato)));
  }

  Copia c = &copiar_int;

  Predicado2 p = &intNoIguales;

  Eliminadora e = &borrarint;

  eliminar_repetidos(l,p,c,e);

  for (GList i = l; i != NULL; i=i->sig)
  {
    printf("%d\n",*((int*)(i->dato)));
  }

}
