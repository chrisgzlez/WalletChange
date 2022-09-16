#include <stdio.h>
#include <string.h>

#include "wallet.h"
#include "utilities.h"

int main() {
    int option;
    char currency[STR_BUFFER_LEN];

    // Inicializamos Monedero
    MONEDERO monedero; monedero.monedas = NULL; monedero.stock = NULL;
    do {
        do {
            printf("1. Escoger Currency \n2. Operaciones Monedero \n3. Imprimir Monedero \n0. Salir\n");
            printf("Elige: ");
            option = getInput();
            if (option == -1) printf("Input no valido\n");
        } while (option == -1);
        printf("\n----------------------------\n\n");
        switch (option) {

            case 1:
                printf("Elige moneda (euro/dollar/libra): ");
                scanf(" %[^\r\n]", currency);
                monedero = cargarMonedero(strncat(currency, ".txt", 5));
                if (monedero.monedas)
                    printMonedero(monedero);
                break;

            case 2:
                if (monedero.monedas){
                    printf("Método (1. LIMITAD0 / 0. ILIMITADO): ");
                    int limited = getInput();
                    if (limited == 1 || limited == 0) {
                        menuDarCambio(&monedero, limited);
                        actualizarArchivo(monedero, currency);
                    }

                } else
                    printf("No se ha creado monedero\n");
                break;

            case 3:
                if (monedero.monedas)
                    printMonedero(monedero);
                else
                    printf("No se ha creado monedero\n");
                break;
            default:
                if (monedero.monedas)
                    liberarMonedero(&monedero);
                break;
        }
        printf("\n----------------------------\n\n");
    } while(option);
    return 0;
}