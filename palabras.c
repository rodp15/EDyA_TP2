#include <stdlib.h>
#include <string.h>
#include "sglist.h"
#include "palabras.h"
#include <assert.h>
#include <stdio.h>

void eliminar_palabra(GList nodoAEliminar){
  char* aux= nodoAEliminar->dato;
  free(aux);
}

void* copiar_palabra(void* p){
    char* nuevap = malloc(sizeof(char)*(strlen((char*) p)+1));

    assert(nuevap!=NULL);

    strcpy(nuevap, ((char*) p));

    return nuevap;
}