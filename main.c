#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <assert.h>
#include <wchar.h>


#define MIN_PALABRAS 5000

void leer_palabras(char *archivoEntrada);
int es_simbolo(wchar_t c);
//int es_espacio(char c);
int es_fin_linea(wchar_t c);

int main(int argc,  char **argv)
{
	setlocale(LC_CTYPE, "");

    char *archivoEntrada=malloc(sizeof(char) * 30), *archivoSalida=malloc(sizeof(char) * 30);

    strcpy(archivoEntrada, argv[1]);
    strcpy(archivoSalida, argv[2]);
    wprintf(L"%s %s \n", archivoEntrada, archivoSalida);
    wprintf(L"empiezo a leer_palabras:\n");
    leer_palabras(archivoEntrada);
    wprintf(L"termino de leer_palabras\n");

    free(archivoEntrada);

}

void leer_palabras(char *archivoEntrada){
	FILE* fp = fopen(archivoEntrada, "r");
	assert(fp != NULL);
	wchar_t auxC;
	//printf("entro a la funcion\n");
	wchar_t linea[100];
	int ban=0, largoLinea, nroLineas=1;
	
	//”:”, ”;”, ”,”, ”.”, ”?”, ”!”.
	while( (fwscanf(fp, L"%[^' '\r\n:;,.?!]", linea)) == 1 ){
		// Se que el fwscanf se cruzo un caracter de terminacion y no lo leyo,
		// asique lo leemos para descartarlo.
		auxC = fgetwc(fp);
		wprintf(L"cant lineas: %ld \n", nroLineas);

		if(es_fin_linea(auxC)){
			ban=1;
			wprintf(L"ahora viene la ultima palabra de la linea: %ld\n",ban);
			// TODO Aca podes incrementar la cuenta de en que linea estas aldu.
		}

		// Luego leemos caracteres hasta cruzarnos con uno que no sea de terminacion de palabra.
		while(es_simbolo(auxC)){
			auxC = fgetwc(fp);
		}
		// Hacemos un ungetc para que en la proxima leida del archivo, este caracter que no es de terminacion de palabra
		// sea leido.
		ungetwc(auxC, fp);

		largoLinea = wcslen(linea);
		linea[largoLinea] = '\0';		
		wprintf(L"tamaño linea: %ld\n",largoLinea );
		wprintf(L"linea actual: %s \n", linea);
		/*if(!esta_en_diccionario(linea)){
			buscar_sugerencia(linea);
			wprintf(L"linea %ld, "%s" no esta en el diccionario \n Quizas quiso decir: ", nroLineas, linea);
		}*/

		if(ban==1){
			nroLineas++;
			wprintf(L"CANT lineas: %ld \n", nroLineas);
			ban=0;
		}

	}
	
	fclose(fp);
}

//”:”, ”;”, ”,”, ”.”, ”?”, ”!”.
int es_simbolo(wchar_t c){
	return ((c ==58) || (c==59) || (c==44) || (c==46) || (c==62) || (c==33) || (c==32) || (c=='\r') || (c=='\n') );
}

int es_fin_linea(wchar_t c){
	return ( (c=='\r') || (c=='\n'));
}