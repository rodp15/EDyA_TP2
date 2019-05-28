#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

unsigned long long slash_hash(void *string) {
    union { 
    	unsigned long long h; 
    	unsigned char u[8]; 
    } uu;

    char* s = (char*)string;
    int i=0; 
    uu.h=strlen(s);
    
    while(*s){ 
    	uu.u[i%8] += *s + i + (*s >> ( ( (uu.h) / (i+1) ) % 5 ) ); 
    	s++; 
    	i++; 
    }

    return uu.h;
}

unsigned funcionPropia(void *clave) {
	unsigned key = 0;
	char *palabra = (char*)clave;
	for(int i = 0; palabra[i]; i++){
		key += palabra[i]*(pow(33,i));
	}
	key = key * strlen(palabra);
	return key;
}

unsigned djb2(void* clave) {
	unsigned long key = 5381; // constante magica
	int c;
	unsigned char* p = (unsigned char*)clave;
	while( (c = *p++) ){
		key = ( (key << 5) + key ) + c; /* (key * 33) + c */ 
	}
	return key;
}

unsigned cantidadPalabras(char* nombreArchivo) {
	unsigned i = 0, palabras, longitudPromedio = 10;
    float aux;

    FILE* fp=fopen(nombreArchivo,"r");
    
    fseek(fp,0,SEEK_END);
    aux = ftell(fp);
    fclose(fp);

    while(aux > 10.0){
    	aux = aux / 10.0;
    	i++;
    }

    palabras = ceil(aux)*pow(10,i);
    return palabras/longitudPromedio;
}

int ClavesUnsignedIguales(void* clave1, void* calve2) {
	// TODO Esto debe estar mal. Checkear que ande como debe.
	if(clave1 == NULL){
		return 0;
	} else {
		if(calve2 == NULL){
			return 0;
		} else {
			return ( (*((unsigned*)clave1)) == (*((unsigned*)calve2)) );
		}
	}
}

int main() {
	unsigned palabras = cantidadPalabras("listado-general.txt");

	FuncionHash fh = &djb2;
	FuncionIgualdad fi = &ClavesUnsignedIguales;
	funcionesColisiones manejoColisiones;
	/*
	NECESITO LO DE LISTAS

	manejoColisiones.encadenar = ;
	manejoColisiones.buscarEnLista = ;
	manejoColisiones.eliminarLista = ;
	TablaHash *MiTabla = tablahash_crear(palabras, fh, fi, manejoColisiones);
	*/

	return 0;
}