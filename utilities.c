#include "utilities.h"

/**
 * Converte o array dinámico [array] a un vectorD de tamaño [tam].
 *
 * @param array array dinámico con los datos.
 * @param tam numero de datos a convertir.
 * @return Devuelve un vectorD de tamaño [tam] con los datos de [array]
 */
vectorD array2Vector (int *array, int tam) {
    vectorD vector = NULL;
    crear(&vector, tam);
    for (int i = 0; i < tam; i++)
        asignar(&vector, i, array[i]);
    free(array);
    return vector;
}

/**
 * Lee desde la terminal un entero y lo valida.
 *
 * @return Devuelve un entero validado
 */
int getInput () {
    char s[32];
    if (scanf("%31s", s) != 1)
        return -1;
    else {
        errno = 0;
        char *endptr;
        long int l = strtol(s, &endptr, 10);

        if ((endptr == s) ||        // no digit
            ((*endptr != 0) && !isspace(*endptr)) || /* e.g. 12a */
            (errno != 0) ||         // overflow en long
            ((int)l != l))          // overflow en int
            return -1;

        return (int)l;
    }
}
/**
 * Devuelve la copia del vectorD [src]
 *
 * @param src vectorD al que copiar
 * @return Devuelve la copia de un vectorD [src]
 */
vectorD copiarVector (vectorD src) {
    vectorD dest = NULL;
    int tam = longitudVector(src);
    crear(&dest, tam);
    for (int i = 0; i < tam; i++)
        asignar(&dest, i, recuperar(src, i));
    return dest;
}