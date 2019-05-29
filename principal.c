#include "tablahash.h"
#include "sglist.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

unsigned cantidadPalabras(char* nombreArchivo) {
	// TODO ver por que con menos de 10 palabras me devuelve 1 palabra menos
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

unsigned djb2(void* clave) {
	unsigned long key = 5381; // constante magica
	int c;
	wchar_t* p = (wchar_t*)clave;
	while( (c = *p++) ){
		key = ( (key << 5) + key ) + c; /* (key * 33) + c */ 
	}
	return key;
}

int clavesIguales(void* clave1, void* clave2) {
	// TODO Checkear que ande como debe.
	if(clave1 == NULL){
		return 0;
	} else {
		if(clave2 == NULL){
			return 0;
		} else {
			if(wcscmp( (wchar_t*)clave1, (wchar_t*)clave2 ) == 0 ){
				return 1;
			} else {
				return 0;
			}
		}
	}
}

int cargarArchivo(TablaHash *tabla, const char* nombreArchivo){
	// TODO la regex esta sirve para leer el archivo del diccionario. Hay que armar una nueva para leer el archivo de ingreso
	FILE* f = fopen(nombreArchivo, "r");
	wchar_t buff[100];
	int i = 0, largoPalabra;
	void *clave, *dato;
	while( (fwscanf(f, L"%[^\r\n]\r\n", buff)) == 1 ){
		largoPalabra = wcslen(buff);
		buff[largoPalabra] = '\0';
		
		clave = malloc(sizeof(wchar_t) * (largoPalabra + 1) );
		memcpy(clave ,buff, sizeof(wchar_t) * (largoPalabra + 1));
		dato = malloc(sizeof(wchar_t) * (largoPalabra + 1) );
		memcpy(dato ,buff, sizeof(wchar_t) * (largoPalabra + 1));
		tablahash_insertar(tabla, clave, dato);
		
		i++;
	}
	return i;
}

int main() {
	// IMPORTANTE: Cambie la codificacion del archivo a windows 1252. Esto puede hacer q en linux no funque. Aldu
	setlocale(LC_CTYPE, "");

	unsigned palabras = cantidadPalabras("listado-general.txt");

	FuncionHash fh = &djb2;
	FuncionIgualdad fi = &clavesIguales;
	funcionesColisiones manejoColisiones;
	manejoColisiones.encadenar = &glist_agregar_inicio;
	manejoColisiones.buscarEnLista = &glist_buscar;
	manejoColisiones.eliminarLista = &glist_eliminar_nodo;

	TablaHash *MiTabla = tablahash_crear(palabras, fh, fi, manejoColisiones);

	cargarArchivo(MiTabla, "listado-general.txt");
	
	// Testeado de la funcion hash
	int cant_nodos, max = 0, cant_cero=0, cuenta_total = 0, cantidadColisiones = 0;
	for(int i = 0; i < palabras; i++){
		cant_nodos = glist_size((GList)MiTabla->tabla[i].inicioLE);
		if(cant_nodos > max)
			max = cant_nodos;

		if(cant_nodos == 0)
			cant_cero++;

		if(cant_nodos > 1){
			cantidadColisiones++;
		}

		cuenta_total+=cant_nodos;
	}
	printf("Maximas colisiones:%d\nCantidad de casillas sin ocupar:%d\nCheck que se hayan insertado todas las palabras:%d\nCasillas con colisiones:%d\n", max, cant_cero, cuenta_total, cantidadColisiones);

	return 0;
}