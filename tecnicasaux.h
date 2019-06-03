#include <stdlib.h>

wchar_t* intercambia_adyacentes(wchar_t* pal1, int largoPalabra, int pos1, int pos2);

wchar_t* insertar_entre_pares(wchar_t* pal1,int largoPalabra, int pos1, int pos2, wchar_t caracterAInsertar);

wchar_t* elimina_caracter(wchar_t* pal1,int largoPalabra, int pos);

wchar_t* cambia_caracter(wchar_t* pal1, int largoPalabra, int pos, wchar_t caracterACambiar);

void separar_palabras(wchar_t* pal1,int largoPalabra, wchar_t** subString1, wchar_t** subString2, int pos);