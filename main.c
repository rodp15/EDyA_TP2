#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <assert.h>
#include <wchar.h>


#define MIN_PALABRAS 50000

wchar_t **leer_palabras(char *archivoEntrada, int *cant1, int *cant2, int size);
int es_simbolo(char c);
//int es_espacio(char c);
int es_fin_linea(char c);

int main(int argc,  char **argv)
{
	setlocale(LC_CTYPE, "");

    char *archivoEntrada=malloc(sizeof(char) * 30), *archivoSalida=malloc(sizeof(char) * 30);
    wchar_t **palabrasEntrada;
    int size=MIN_PALABRAS, cantLineas=0, cantPalabras=0;

    strcpy(archivoEntrada, argv[1]);
    strcpy(archivoSalida, argv[2]);
    printf("%s %s \n", archivoEntrada, archivoSalida);
    printf("empiezo a leer_palabras:\n");
    palabrasEntrada=leer_palabras(archivoEntrada, &cantLineas, &cantPalabras, size);
    printf("termino de leer_palabras\n");
    for(int i = 0; i < 6; i++){
    	wprintf(L"%s\n", palabrasEntrada[i]);
    }
    free(archivoEntrada);

}

wchar_t** leer_palabras(char *archivoEntrada, int *cantLineas, int *cantPalabras, int size){
	FILE* fp = fopen(archivoEntrada, "r");
	assert(fp != NULL);
	char auxC;
	//printf("entro a la funcion\n");
	wchar_t linea[100], **array=malloc(sizeof(wchar_t*) * MIN_PALABRAS);
	int /*i, aux,*/ largoLinea, nroLineas=0, palabra=0;
	
	//”:”, ”;”, ”,”, ”.”, ”?”, ”!”.
	while( (fwscanf(fp, L"%[^' '\r\n:;,.?!]", linea)) == 1 ){
		//printf("entro al while\n");
		//wprintf (L"%ls \n", L"A wide string"); //NO ME DA BOLA EN NADA
		//wprintf (L"wtfff");
		//wprintf (L"linea: %ls \n", linea);

		// Se que el fwscanf se cruzo un caracter de terminacion y no lo leyo,
		// asique lo leemos para descartarlo.
		auxC = fgetc(fp);

		if(es_fin_linea(auxC)){
			// TODO Aca podes incrementar la cuenta de en que linea estas aldu.
		}

		// Luego leemos caracteres hasta cruzarnos con uno que no sea de terminacion de palabra.
		while(es_simbolo(auxC)){
			auxC = fgetc(fp);
		}
		// Hacemos un ungetc para que en la proxima leida del archivo, este caracter que no es de terminacion de palabra
		// sea leido.
		ungetc(auxC, fp);



		if(palabra>=size){
			//printf("no deberia entrar aca \n");
			array=realloc(array, sizeof(wchar_t*) * (palabra+(size/2)));
			size+=size/2;
		}
		
		largoLinea = wcslen(linea);
		printf("tamaño linea: %d\n",largoLinea );
		linea[largoLinea] = '\0';		
		array[nroLineas] = malloc(sizeof(wchar_t*) * (largoLinea + 1));
		wcscpy(array[nroLineas], linea);
		nroLineas++;

		/*
		for (i=0,aux=0; i < largoLinea; aux++, ++i)
		{
			if(es_simbolo(linea[aux])){
				array[nroLineas][palabra] = malloc(sizeof(wchar_t*) * (aux+1));
				memcpy(array[nroLineas][palabra],linea,aux);
				array[nroLineas][palabra][aux]='\0';
				i+=2; //por el espacio hasta el siguiente caracter
				linea+=i;
				aux=-1; //al finalizar le va a sumar 1
				palabra++;
				i--;
			}

			if(es_espacio(linea[aux])){
				array[nroLineas][palabra] = malloc(sizeof(wchar_t*) * (aux+1));
				memcpy(array[nroLineas][palabra],linea,aux);
				array[nroLineas][palabra][aux]='\0';
				i++;
				linea+=i;
				aux=-1;
				palabra++;
				i--;
			}

		}
		if(aux!=0){
			array[nroLineas][palabra] = malloc(sizeof(wchar_t*) * (aux+1));
			memcpy(array[nroLineas][palabra],linea,aux);
			array[nroLineas][palabra][aux]='\0';
			i++;
			linea+=i;
			aux=-1;
			palabra++;
		}
	nroLineas++;
	*/	
	}
	

	*(cantLineas) = nroLineas;
	fclose(fp);
	return array;
}

//”:”, ”;”, ”,”, ”.”, ”?”, ”!”.
int es_simbolo(char c){
	return ((c ==58) || (c==59) || (c==44) || (c==46) || (c==62) || (c==33) || (c==32) || (c=='\r') || (c=='\n') );
}

int es_fin_linea(char c){
	return ( (c=='\r') || (c=='\n'));
}