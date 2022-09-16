#include "wallet.h"

/** INTERFAZ DE USUARIO */
/**
 * Interfaz de Usuario para dar cambio.
 *
 * @param monedero puntero a estrtuctura MONEDERO.
 * @param limited valor booleano que determina que tipo de stock usar.
 */
void menuDarCambio (MONEDERO *monedero, int limited){
    char operation = 'a';
    if (limited) {
        printf("Operación a realizar: \na) Dar cambio \nb) Aumentar Stock \nElige (a/b): ");
        scanf(" %c", &operation);
    }
    switch (operation) {

        case 'a':
            printf("Cantidad a cambiar  (centimos): ");
            int pago = getInput();
            if (pago < 0) printf("\nERROR!!\nOVERFLOW\nCANTIDAD DEMASIADO GRANDE\n");
            else {
                vectorD cambio = cambioTransaccion(pago, monedero, limited);
                cambio ? printVector(cambio) : printf("No hay cambio posible\n");
                if (cambio)
                    liberar(&cambio);
            }
            break;

        case 'b':
            aumentarStock(&monedero->stock);
            break;

        default:
            printf("Not an option\n");
    }
}

/** FUNCIONES DE CARGA DE DATOS */

/**
 * Carga desde el archivo [moneda] los valores y su stock.
 *
 * @param moneda puntero a char que contiene el nombre del archivo a abrir.
 * @return Devuelve una struct MONEDERO con los datos del archivo
 */
MONEDERO cargarMonedero (char *moneda) {
    MONEDERO monedero; monedero.monedas = NULL; monedero.stock = NULL;
    FILE *arquivo_moneda = NULL;
    if(!(arquivo_moneda = fopen(moneda, "r"))) {
        printf("\n\nErro na abertura do arquivo de lectura!!\n");
    }
    else{
        char linea[STR_BUFFER_LEN];
        fgets(linea, STR_BUFFER_LEN, arquivo_moneda);
        monedero.monedas = cargarValores(linea);
        fgets(linea, STR_BUFFER_LEN, arquivo_moneda);
        monedero.stock = cargarValores(linea);
        fclose(arquivo_moneda);
    }
    return monedero;
}

/**
 * Carga los datos de el char** [linea] los valores en un vectorD.
 *
 * @param linea puntero a char que contiene el los valores a cargar.
 * @return Devuelve un struct vectorD con los valores del char**
 */
vectorD cargarValores (char *linea) {
    int *buffer = (int*)malloc(sizeof(int)*INT_BUFFER_LEN);
    int tam = 0;
    char *value;

    value = strtok(linea, ",");

    // Gardamos os numero de valores e os valores nunha variable
    while(value){

        // Checkeamos si necesitamos ampliar el tamaño del buffer
        if (tam > INT_BUFFER_LEN)
            buffer = (int*)realloc(buffer, sizeof(int)*(int)pow(INT_BUFFER_LEN, 2));

        *(buffer + tam++) = (int)strtol(value, NULL ,10);
        value = strtok(NULL, ",");
    }

    // Devolvemos un vector cos datos do array
    return array2Vector(buffer, tam);
}

/** FUNCIONES DE CARGA DE DATOS*/

/**
 * Escribe los datos de el strucut [MONEDERO] en el archivo con nombre [moneda]
 *
 * @param monedero struct monedero con los datos a escribir.
 * @param linea puntero a char que contiene el los valores a cargar.

 */
void actualizarArchivo (MONEDERO monedero, char* moneda) {
    FILE *arquivo_moneda = NULL;
    if(!(arquivo_moneda = fopen(moneda, "w"))) {
        printf("\n\nErro na abertura do arquivo de escritura!!\n");

    } else {
        int len = longitudVector(monedero.monedas);
        vectorD aux = monedero.monedas;
        // Imprime valores
        int control = 1;
        for (int i = 0; i < len; i++) {
            fprintf(arquivo_moneda, "%d", recuperar(aux, i));

            // Si no es el ultimo elemento imprime comas
            if (i != len - 1)
                fprintf(arquivo_moneda, "%s", ",");
            else {
                if (control) {
                    control = 0;
                    i = -1;
                    aux = monedero.stock;
                }
                fprintf(arquivo_moneda, "%s", "\n");
            }
        }
        fclose(arquivo_moneda);
    }
}

/** OPERACIONES DEL MONEDERO */

/**
 * Devuelve el cambio como un vectorD del [pago] según stock limitado o no
 *
 * @param pago int que indica la cantidad de dinero a la que dar cambio
 * @param monedero puntero a MONEDERO que contiene los valores de la moneda y su stock
 * @param limited booleano que indica si usar stock limitado o ilimitado
 * @return vectorD con los valores del cambio
 */
vectorD cambioTransaccion (int pago, MONEDERO *monedero, int limited){
    int i = 0, j = 0, tam = longitudVector(monedero->monedas);
    int *cambio = (int*)malloc(sizeof(int)*INT_BUFFER_LEN);
    int LENGHT = INT_BUFFER_LEN;

    // Si no nos dan una cantidad retornamos NULL
    if (!pago) return NULL;
    vectorD backup = copiarVector(monedero->stock);

    // Obtiene valores de cambio
    while (i < tam && pago){
        int coin = recuperar(monedero->monedas, i);

        // Si la moneda es menor que el pago da cambio
        if (pago - coin >= 0){
            int reps = pago/coin;
            int stock = recuperar(monedero->stock, i);

            // Determina si usar reps o stock en funcion de su cantidad y limited
            int lim = (reps > stock && limited) ? stock : reps;
            for (int k = 0; k < lim; k++){
                // Incrementa el tamaño del buffer si es necesario
                if (j > LENGHT)
                    cambio = (int *) realloc(cambio, sizeof(int) * (LENGHT*=2));
                cambio[j++] = coin;
            }
            // Actualiza el stock del monedero y reduce pago
            asignar(&monedero->stock, i, stock - lim);
            pago -= coin * lim;
        }
        i++;
    }
    if (pago)
        monedero->stock = copiarVector(backup);
    liberar(&backup);
    return (pago) ? NULL : array2Vector(cambio, j);
}

/**
 * Aumenta el stock de las monedas en 10 unidades
 *
 * @param stock puntero al vectorD que almacena el stock de monedas
 */
void aumentarStock(vectorD *stock) {
    for (int i = 0; i < longitudVector(*stock); i++)
        asignar(stock, i, recuperar(*stock, i) + 10);
}

/**
 * Imprime los distintos valores de las monedas del monedero y su stock
 *
 * @param monedero struct MONEDERO que almacena los valores a imprimir
 */
void printMonedero (MONEDERO monedero) {
    printf("[ ");
    int len = longitudVector(monedero.monedas);
    for(int i = 0; i < len; i++)
        printf("%d: %d,\n ",
               recuperar(monedero.monedas, i), recuperar(monedero.stock, i));
    printf("]\n");
}

/**
 * Libera la memoria del puntero a MONEDERO [monedero] de forma recursiva
 *
 * @param monedero struct MONEDERO a liberar
 */
void liberarMonedero (MONEDERO *monedero) {
    if (longitudVector(monedero->monedas)) {
        liberar(&monedero->monedas);
        liberar(&monedero->stock);
        monedero = NULL;
    } else
        printf("No hai monedero que liberar\n");
}

