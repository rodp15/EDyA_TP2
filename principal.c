#include "tablahash.h"
#include "sglist.h"
#include "tecnicasaux.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

#define CANT_MIN_SUGERENCIAS 5

GList buscar_sugerencias(wchar_t* palabra, TablaHash *tabla);
GList posibles_intercambios(wchar_t *palabra,int largoPalabra);
GList posibles_inserciones(wchar_t *palabra,int largoPalabra,wchar_t alfabeto[]);
GList posibles_eliminaciones(wchar_t *palabra,int largoPalabra);
GList posibles_cambios(wchar_t *palabra,int largoPalabra,wchar_t alfabeto[]);
GList separadas_correctas(wchar_t *palabra,int largoPalabra);


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
	manejoColisiones.eliminarLista = &glist_eliminar_dato;

	TablaHash *MiTabla = tablahash_crear(palabras, fh, fi, manejoColisiones);

	cargarArchivo(MiTabla, "listado-general.txt");
	/*
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
	*/
	GList sugerencias=buscar_sugerencias("aolh", MiTabla);
	return 0;
}

GList buscar_sugerencias(wchar_t* palabra, TablaHash *tabla){

	int d=1,len=wcslen(palabra);
	wchar_t alfabeto[34]="abcdefghijklmnñopqrstuvwxyzáéíóúöü";
	GList sugerencias=glist_crear();

	//busco TODAS las posibles a distancia 1
	GList intercambiadas=posibles_intercambios(palabra,len);
	intercambiadas=eliminar_repetidos(intercambiadas);
	sugerencias=filter(intercambiadas, esta_en_diccionario);

	GList insertadas=posibles_inserciones(palabra,len,alfabeto);
	insertadas=eliminar_repetidos(insertadas);
	sugerencias=concatenar_listas(sugerencias,filter(insertadas, esta_en_diccionario, copiar_nodo));

	GList eliminaciones=posibles_eliminaciones(palabra,len);
	eliminaciones=eliminar_repetidos(eliminaciones);
	sugerencias=concatenar_listas(sugerencias,filter(eliminaciones, esta_en_diccionario, copiar_nodo));


	GList cambiadas=posibles_cambios(palabra,len,alfabeto);
	cambiadas=eliminar_repetidos(cambiadas);
	sugerencias=concatenar_listas(sugerencias,filter(cambiadas, esta_en_diccionario, copiar_nodo));

	sugerencias=concatenar_listas(sugerencias, separadas_correctas(palabra,len));

	if(glist_size(sugerencias)>=5){
		return sugerencias;
	}
	//busco en la siguientes distancias
	else{
		while(glist_size(sugerencias)<CANT_MIN_SUGERENCIAS){

			for (GNodo *nodo = intercambiadas; nodo != NULL && glist_size(sugerencias)<CANT_MIN_SUGERENCIAS; nodo = nodo->sig)
			{
				GList intercambiadas2=glist_crear();
				intercambiadas2=posibles_intercambios(nodo->dato,wcslen(nodo->dato),alfabeto);
				intercambiadas2=eliminar_repetidos(intercambiadas2);
				sugerencias=concatenar_listas(sugerencias,filter(intercambiadas2,esta_en_diccionario));
				GList intercambiadasFinal=glist_crear();
				intercambiadasFinal=concatenar_listas(intercambiadasFinal,intercambiadas2);
			}
			glist_destruir(intercambiadas);
			intercambiadas=intercambiadasFinal;

			for (GNodo *nodo = insertadas; nodo != NULL && glist_size(sugerencias)<CANT_MIN_SUGERENCIAS; nodo = nodo->sig)
			{
				GList insertadas2=glist_crear();
				insertadas2=posibles_inserciones(nodo->dato,wcslen(nodo->dato),alfabeto);
				insertadas2=eliminar_repetidos(insertadas2);
				sugerencias=concatenar_listas(sugerencias,filter(insertadas2,esta_en_diccionario));
				GList insertadasFinal=glist_crear();
				insertadasFinal=concatenar_listas(insertadasFinal,insertadas2);
			}
			glist_destruir(insertadas);
			insertadas=insertadasFinal;

			for (GNodo *nodo = eliminaciones; nodo != NULL && glist_size(sugerencias)<CANT_MIN_SUGERENCIAS; nodo = nodo->sig)
			{
				GList eliminaciones2=glist_crear();
				eliminaciones2=posibles_eliminaciones(nodo->dato,wcslen(nodo->dato),alfabeto);
				eliminaciones2=eliminar_repetidos(eliminaciones2);
				sugerencias=concatenar_listas(sugerencias,filter(eliminaciones2,esta_en_diccionario));
				GList eliminacionesFinal=glist_crear();
				eliminacionesFinal=concatenar_listas(eliminacionesFinal,eliminaciones2);
			}
			glist_destruir(eliminaciones);
			eliminaciones=eliminacionesFinal;

			for (GNodo *nodo = cambiadas; nodo != NULL && glist_size(sugerencias)<CANT_MIN_SUGERENCIAS; nodo = nodo->sig)
			{
				GList cambiadas2=glist_crear();
				cambiadas2=posibles_cambios(nodo->dato,wcslen(nodo->dato),alfabeto);
				cambiadas2=eliminar_repetidos(cambiadas2);
				sugerencias=concatenar_listas(sugerencias,filter(cambiadas2,esta_en_diccionario));
				GList cambiadasFinal=glist_crear();
				cambiadasFinal=concatenar_listas(cambiadasFinal,cambiadas2);
			}
			glist_destruir(cambiadas);
			cambiadas=cambiadasFinal;

		}
	}

	return sugerencias;	
}

GList posibles_intercambios(wchar_t *palabra,int largoPalabra){
	GList resultado=glist_crear();
	for (int i = 0, j=1; j < largoPalabra; ++i,j++)
	{
		wchar_t palabraResultante=intercambia_adyacentes(palabra,largoPalabra,i,j);
		resultado=glist_agregar_inicio(palabraResultante,&resultado);
	}
	return resultado;
}

GList posibles_inserciones(wchar_t *palabra,int largoPalabra,wchar_t alfabeto[]){
	GList resultado=glist_crear();
	//al inicio
	wchar_t* salida = malloc( sizeof(wchar_t) * (largoPalabra + 2) );
	for(int i=0;i<LARGO_ALFABETO,i++){
		wchar_t* temp = salida;
		temp[0]=alfabeto[i];
		temp++;
		wcsncpy(temp, palabra, largoPalabra);
		resultado=glist_agregar_inicio(salida,&resultado);
	}
	//al final
	for(int i=0;i<LARGO_ALFABETO, i++){
		wchar_t* temp = salida;
		temp[largoPalabra]=alfabeto[i];
		wcsncpy(temp, palabra, largoPalabra);
		resultado=glist_agregar_inicio(salida,&resultado);
	}
	free(salida);

	for (int i = 0,j=1; j < largoPalabra; ++i,j++)
	{
		for (int k = 0; k < LARGO_ALFABETO; ++k)
		{
			salida=insertar_entre_pares(palabra, largoPalabra, i,j,alfabeto[k]);
			resultado=glist_agregar_inicio(salida,&resultado);

		}
	}

	return resultado;
}

GList posibles_eliminaciones(wchar_t *palabra,int largoPalabra){
	wchar_t *salida;
	GList resultado=glist_crear();
	for (int i = 0; i < largoPalabra; ++i)
	{
		salida=elimina_caracter(palabra,largoPalabra,i);
		resultado=glist_agregar_inicio(salida,&resultado);
	}

	return resultado;
}
GList posibles_cambios(wchar_t *palabra,int largoPalabra,wchar_t alfabeto[]){
	wchar_t *salida;
	GList resultado=glist_crear();
	for (int i = 0; i < largoPalabra; ++i)
	{
		for (int j = 0; j < LARGO_ALFABETO; ++j)
		{
			salida=cambia_caracter(palabra,largoPalabra,i,alfabeto[j]);
			resultado=glist_agregar_inicio(salida,&resultado);

		}
	}

	return resultado;
}
GList separadas_correctas(wchar_t *palabra,int largoPalabra){
	GList resultado=glist_crear();
	wchar_t *salida1, *salida2;
	for (int i = 1; i < largoPalabra; ++i)
	{
		separar_palabras(palabra,largoPalabra,&salida1,&salida2,i);
		if(esta_en_diccionario(salida1)&&esta_en_diccionario(salida2))
		{
			resultado=glist_agregar_inicio(salida1,&resultado);
			resultado=glist_agregar_inicio(salida2,&resultado);
		}
	}

	return resultado;
}
