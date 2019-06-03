#include <stdlib.h>
#include <string.h>
#include "sglist.h"
#include "palabras.h"
#include <assert.h>
#include <stdio.h>
#include <wchar.h>

void eliminar_palabra(GList nodoAEliminar){
  wchar_t* aux= nodoAEliminar->dato;
  free(aux);
}

void* copiar_palabra(void* dato){
  void* copia= malloc(sizeof(wchar_t)*(wcslen(((wchar_t*)dato)))+1);
  wcscpy(copia,dato);
  return copia;
}