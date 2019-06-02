#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <ctype.h>
#include <locale.h>

wchar_t* intercambiaAdyacentes(wchar_t* pal1, int pos1, int pos2){
	wchar_t* salida = malloc( sizeof(wchar_t) * (wcslen(pal1) + 1) );
	wprintf(L"cadena original: %ls\n",pal1);
	wcscpy(salida,pal1);
	wchar_t temp = salida[pos1];
	salida[pos1] = salida[pos2];
	salida[pos2] = temp;
	return salida;
}

wchar_t* insertarEntrePares(wchar_t* pal1, int pos1, int pos2, wchar_t caracterAInsertar){
	// +2 uno para el \0 y el otro para el nuevo caracter
	int largoPal1 = wcslen(pal1);
	wchar_t* salida = malloc( sizeof(wchar_t) * (largoPal1 + 2) );
	wchar_t* temp = salida;
	wcsncpy(temp, pal1, (pos1+1));
	temp[pos1+1] = caracterAInsertar;
	temp += pos1+2;
	pal1 += pos1+1;
	wcsncpy(temp, pal1, (largoPal1 - pos2));
	return salida;
}

wchar_t* eliminaCaracter(wchar_t* pal1, int pos){
	int largoPal1 = wcslen(pal1); 
	wchar_t* salida = malloc(sizeof(wchar_t) * largoPal1);
	wchar_t* temp = salida;
	wcsncpy(temp, pal1, pos);
	temp += pos;
	pal1 += pos+1;
	wcsncpy(temp, pal1, (largoPal1 - (pos+1)));
	return salida;
}


wchar_t* cambiaCaracter(wchar_t* pal1, int pos, wchar_t caracterACambiar){
	wchar_t* salida = malloc(sizeof(wchar_t) * (wcslen(pal1)+1) );
	wcscpy(salida, pal1);
	salida[pos]=caracterACambiar;
	return salida;
}

void separarPalabras(wchar_t* pal1, wchar_t** subString1, wchar_t** subString2, int pos){
	int largoPal1 = wcslen(pal1);
	*subString1 = malloc(sizeof(wchar_t) * (pos+1));
	*subString2 = malloc(sizeof(wchar_t) * (largoPal1 - pos + 1));
	wcsncpy(*subString1, pal1, pos);
	pal1 += pos;
	wcsncpy(*subString2, pal1, (largoPal1 - pos));
}
