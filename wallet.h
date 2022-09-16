#ifndef WALLET_H
#define WALLET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>
#include "utilities.h"
#include "TAD/vectordinamico.h"

#define STR_BUFFER_LEN 200
#define INT_BUFFER_LEN 32

/** ESTRUCTURA DEL MONDERO */
typedef struct {
    vectorD monedas;
    vectorD stock;
} MONEDERO;

/** INTERFAZ DE USUARIO */
/**
 * Interfaz de Usuario para dar cambio.
 *
 * @param monedero puntero a estrtuctura MONEDERO.
 * @param limited valor booleano que determina que tipo de stock usar.
 */
void menuDarCambio (MONEDERO *monedero, int limited);


/** FUNCIONES DE CARGA DE DATOS */

/**
 * Carga desde el archivo [moneda] los valores y su stock.
 *
 * @param moneda puntero a char que contiene el nombre del archivo a abrir.
 * @return Devuelve una struct MONEDERO con los datos del archivo
 */
MONEDERO cargarMonedero(char* moneda);

/**
 * Carga los datos de el char** [linea] los valores en un vectorD.
 *
 * @param linea puntero a char que contiene el los valores a cargar.
 * @return Devuelve un struct vectorD con los valores del char**
 */
vectorD cargarValores (char* linea);

/** FUNCIONES DE CARGA DE DATOS*/

/**
 * Escribe los datos de el strucut [MONEDERO] en el archivo con nombre [moneda]
 *
 * @param monedero struct monedero con los datos a escribir.
 * @param linea puntero a char que contiene el los valores a cargar.

 */
void actualizarArchivo(MONEDERO monedero, char* moneda);

/** OPERACIONES DEL MONEDERO */

/**
 * Devuelve el cambio como un vectorD del [pago] según stock limitado o no
 *
 * @param pago int que indica la cantidad de dinero a la que dar cambio
 * @param monedero puntero a MONEDERO que contiene los valores de la moneda y su stock
 * @param limited booleano que indica si usar stock limitado o ilimitado
 * @return vectorD con los valores del cambio
 */
vectorD cambioTransaccion (int pago, MONEDERO *monedero, int limited);

/**
 * Aumenta el stock de las monedas en 10 unidades
 *
 * @param stock puntero al vectorD que almacena el stock de monedas
 */
void aumentarStock(vectorD *stock);

/**
 * Imprime los distintos valores de las monedas del monedero y su stock
 *
 * @param monedero struct MONEDERO que almacena los valores a imprimir
 */
void printMonedero (MONEDERO monedero);

/**
 * Libera la memoria del puntero a MONEDERO [monedero] de forma recursiva
 *
 * @param monedero struct MONEDERO a liberar
 */
void liberarMonedero(MONEDERO *monedero);

#endif /** WALLET_H */