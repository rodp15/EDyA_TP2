#include "tablahash.h"
#include "sglist.h"
#include "tecnicasaux.h"
#include "palabras.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include <ctype.h>

#define CANT_MIN_SUGERENCIAS 5
#define LARGO_ALFABETO 34
#define MIN_PALABRAS 5000

void leer_palabras(char *archivoSalida, char *archivoEntrada, TablaHash *tabla, Predicado p, Predicado2 p2, Eliminadora e, Copia c);
int es_simbolo(wchar_t c);
//int es_espacio(char c);
int es_fin_linea(wchar_t c);
GList buscar_sugerencias(wchar_t* palabra, TablaHash *tabla,Predicado p, Predicado2 palabras_iguales, Eliminadora e, Copia c);
GList posibles_intercambios(wchar_t *palabra,int largoPalabra);
GList posibles_inserciones(wchar_t *palabra,int largoPalabra,wchar_t alfabeto[]);
GList posibles_eliminaciones(wchar_t *palabra,int largoPalabra);
GList posibles_cambios(wchar_t *palabra,int largoPalabra,wchar_t alfabeto[]);
GList separadas_correctas(TablaHash* tabla, wchar_t *palabra,int largoPalabra);