#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <ctype.h>
#include <locale.h>

wchar_t* intercambia_adyacentes(wchar_t* pal1, int largoPalabra, int pos1, int pos2){
	wchar_t* salida = malloc( sizeof(wchar_t) * (largoPalabra + 1) );
	wcscpy(salida,pal1);
	wchar_t temp = salida[pos1];
	salida[pos1] = salida[pos2];
	salida[pos2] = temp;
	return salida;
}

wchar_t* insertar_entre_pares(wchar_t* pal1,int largoPalabra, int pos1, int pos2, wchar_t caracterAInsertar){
	// +2 uno para el \0 y el otro para el nuevo caracter
	wchar_t* salida = malloc( sizeof(wchar_t) * (largoPalabra + 2) );
	wchar_t* temp = salida;
	wcsncpy(temp, pal1, (pos1+1));
	temp[pos1+1] = caracterAInsertar;
	temp += pos1+2;
	pal1 += pos1+1;
	wcsncpy(temp, pal1, (largoPalabra - pos2));
	return salida;
}

wchar_t* elimina_caracter(wchar_t* pal1,int largoPalabra, int pos){
	wchar_t* salida = malloc(sizeof(wchar_t) * largoPalabra);
	wchar_t* temp = salida;
	wcsncpy(temp, pal1, pos);
	temp += pos;
	pal1 += pos+1;
	wcsncpy(temp, pal1, (largoPalabra - (pos+1)));
	return salida;
}


wchar_t* cambia_caracter(wchar_t* pal1, int largoPalabra, int pos, wchar_t caracterACambiar){
	wchar_t* salida = malloc(sizeof(wchar_t) * (largoPalabra+1) );
	wcscpy(salida, pal1);
	salida[pos]=caracterACambiar;
	return salida;
}

void separar_palabras(wchar_t* pal1,int largoPalabra, wchar_t** subString1, wchar_t** subString2, int pos){
	*subString1 = malloc(sizeof(wchar_t) * (pos+1));
	*subString2 = malloc(sizeof(wchar_t) * (largoPalabra - pos + 1));
	wcsncpy(*subString1, pal1, pos);
	pal1 += pos;
	wcsncpy(*subString2, pal1, (largoPalabra - pos));
}