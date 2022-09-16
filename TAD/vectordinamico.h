#ifndef VECOTRDINAMICO_H
#define VECTORDINAMICO_H

/*Tipo de datos del vector*/
typedef int TELEMENTO;

/*Tipo opaco, los detalles de implementacion estan ocultos al usuario*/
typedef void* vectorD;

/*Funcion crear: asigna memoria y devuelve la asignacion al vector. Recibe v
*por referencia para devolver al programa principal al direccion de memoria
*reservada por este procedimiento*/
void crear(vectorD *v, int longitud);

/*Funcion asignar: LLena una posicion del vector con un valor. Recibe una copia
*de la direccion de memoria reservada para el vector v*/
void asignar(vectorD *v, int posicion, TELEMENTO valor);

/*Funcion liberar: Libera memoria de los datos del vector y del vector en si*/
void liberar(vectorD *v);

/* Funcion recuperar: Obtiene el elemento guardado en la posición dada por el usuario*/
TELEMENTO recuperar(vectorD v, int indice);

/* Funcion longitudVector: Devuelve la longitud del vector*/
int longitudVector (vectorD v);

void printVector (vectorD v);

#endif /* VECTORDINAMICO_H */