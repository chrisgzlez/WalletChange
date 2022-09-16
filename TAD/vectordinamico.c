#include <stdlib.h>
#include <stdio.h>

/*Se vuelve a definir el tipo de datos que contiene el vector*/
typedef int TELEMENTO;

/*Implementacion del TAD vectorD*/
typedef struct{
    TELEMENTO *datos;           /*valores del vector*/
    int tam;                  /*tamaño del vector*/
} STVECTOR;                     /*definicion del tipo de datos estructura*/

typedef STVECTOR* vectorD;      /*puntero a estructura*/

/*Funciones de manipulacion de datos*/
/*Funcion crear: asigna memoria y devuleve la asignacion al vector*/
void crear(vectorD *v, int longitud){
    int i;
    *v = (vectorD)malloc(sizeof(STVECTOR));
    (*v)->datos = (TELEMENTO*)malloc(longitud*sizeof(TELEMENTO));
    (*v)->tam = longitud;
    for(i=0; i<longitud; i++)
        /*Inicializacion a 0 de las componentes del vector*/
        *((*v)->datos + i) = 0;
}

/*Funcion asignar: Asigna un valor a una posicion del vector*/
void asignar(vectorD *v, int posicion, TELEMENTO valor){
    *((*v)->datos + posicion) = valor;
}

void liberar(vectorD *v){
    if (*v != NULL){
        free((*v)->datos);
        free(*v);
        *v = NULL;
    }else
        printf("No hay vector que liberar\n\n");
}

TELEMENTO recuperar(vectorD v, int indice){
    TELEMENTO x = 0;

    if (v != NULL){
        if(indice < (v)->tam){
            x = *(v->datos+indice);
        }else
            printf("Index out of range\n");
    } else
        printf("El vector no existe\n");
    return x;
}

int longitudVector (vectorD v){
    if(v != NULL) return v->tam;
    printf("No existe el vector\n");
    return 0;
}

void printVector (vectorD v){
    printf("[ ");
    for(int i = 0; i < longitudVector(v); i++){
        if (i % 10 == 0) printf("\n\t");
        printf("%d, ",recuperar(v, i));
    }
    printf("\n]\n");
}
