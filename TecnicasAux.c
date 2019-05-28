#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* intercambiaAdyacentes(char* pal1, int pos1, int pos2){
	char* salida = malloc( sizeof(char) * (strlen(pal1) + 1) );
	strcpy(salida,pal1);
	char temp = salida[pos1];
	salida[pos1] = salida[pos2];
	salida[pos2] = temp;
	return salida;
}

char* insertarEntrePares(char* pal1, int pos1, int pos2, char caracterAInsertar){
	// +2 uno para el \0 y el otro para el nuevo caracter
	int largoPal1 = strlen(pal1);
	char* salida = malloc( sizeof(char) * (largoPal1 + 2) );
	char* temp = salida;
	strncpy(temp, pal1, (pos1+1));
	temp[pos1+1] = caracterAInsertar;
	temp += pos1+2;
	pal1 += pos1+1;
	strncpy(temp, pal1, (largoPal1 - pos2));
	return salida;
}

char* eliminaCaracter(char* pal1, int pos){
	int largoPal1 = strlen(pal1); 
	char* salida = malloc(sizeof(char) * largoPal1);
	char* temp = salida;
	strncpy(temp, pal1, pos);
	temp += pos;
	pal1 += pos+1;
	strncpy(temp, pal1, (largoPal1 - (pos+1)));
	return salida;
}


char* cambiaCaracter(char* pal1, int pos, char caracterACambiar){
	char* salida = malloc(sizeof(char) * (strlen(pal1)+1) );
	strcpy(salida, pal1);
	salida[pos]=caracterACambiar;
	return salida;
}

void separarPalabras(char* pal1, char** subString1, char** subString2, int pos){
	int largoPal1 = strlen(pal1);
	*subString1 = malloc(sizeof(char) * (pos+1));
	*subString2 = malloc(sizeof(char) * (largoPal1 - pos + 1));
	strncpy(*subString1, pal1, pos);
	pal1 += pos;
	strncpy(*subString2, pal1, (largoPal1 - pos));
}