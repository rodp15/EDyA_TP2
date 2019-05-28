#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

/**
 * Tipo de las funciones hash a ser consideradas por las tablas hash.
 */
typedef unsigned (*FuncionHash)(void* clave);
typedef int (*FuncionIgualdad)(void* clave1, void* clave2);
typedef void (*FuncionEncadenamiento)(void** inicioLE, void* dato);
typedef void* (*FuncionBusqueda)(void* inicioLE, void* dato);
typedef void (*FuncionEliminacion)(void** inicioLE, void* dato);

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void* clave;
  void* inicioLE;
} CasillaHash;

/**
 * Conjunto de funciones para el manejo de colisiones de la tabla.
 */
typedef struct {
  FuncionEncadenamiento encadenar;
  FuncionBusqueda buscarEnLista;
  FuncionEliminacion eliminarLista;
} funcionesColisiones;

/**
 * Estructura principal que representa la tabla hash.
 */
typedef struct {
  CasillaHash* tabla;
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
  FuncionIgualdad igualdad;
  funcionesColisiones manejoColisiones;
} TablaHash;

/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash fun, FuncionIgualdad fi, funcionesColisiones fc);

/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, void* clave, void* dato);

/**
 * Busca un elemento dado en la tabla, y retorna un puntero al mismo.
 * En caso de no existir, se retorna un puntero nulo.
 */
void* tablahash_buscar(TablaHash* tabla, void* clave);

/**
 * Elimina un elemento de la tabla.
 */
void tablahash_eliminar(TablaHash* tabla, void* clave);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla);

#endif /* __TABLAHASH_H__ */
