#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>                  /** Usado para validar input */
#include <ctype.h>                  /** Usado para validar input */
#include "TAD/vectordinamico.h"


/**
 * Converte o array dinámico [array] a un vectorD de tamaño [tam].
 *
 * @param array array dinámico con los datos.
 * @param tam numero de datos a convertir.
 * @return Devuelve un vectorD de tamaño [tam] con los datos de [array]
 */
vectorD array2Vector (int *array, int tam);

/**
 * Lee desde la terminal un entero y lo valida.
 *
 * @return Devuelve un entero validado
 */
int getInput();

vectorD copiarVector (vectorD src);

#endif /** UTILITIES_H*/