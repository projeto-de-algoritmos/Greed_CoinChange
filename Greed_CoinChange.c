#include <stdio.h>
#include <stdlib.h>

#define MAX_NOTAS 6
#define MAX_MOEDAS 6

#define NOTAS {100, 50, 20, 10, 5, 2}
#define MOEDAS {100, 50, 25, 10, 5, 1}

void menu(int notas[], int moedas[]) {
    printf("\n\tSistema de troco:\n\n");
    printf("Para o troco, temos as seguintes notas e moedas:\n");

    printf("Notas de ");
    for (int i = 0; i < MAX_NOTAS; i++) {
        printf("%d, ", notas[i]);
    }

    printf("e moedas de ");
    for (int i = 0; i < MAX_MOEDAS; i++) {
        if(i == 0) {
            printf("1 REAL, ");
        } else if (i != MAX_MOEDAS - 1) {
            printf("%d centavos, ", moedas[i]);
        } else {
            printf("e 1 centavo.\n");
        }
    }
}

void troco(int notas[], int moedas[], int inteiro, int decimal) {
    int aux;

    printf("Foram utilizadas as seguintes notas e moedas para o troco:\n");
    for (int i = 0; i < MAX_NOTAS; i++) {
        aux = inteiro/notas[i];
        if (aux) {
            printf("%d notas de %d reais\n", aux, notas[i]);
        } else {
            // Nothing to do.
        }
        inteiro = inteiro % notas[i];
    }

    if (inteiro != 0) {
        aux = inteiro / 1;
        decimal += aux * 100;
    }

    printf("\n");
    for (int i = 0; i < MAX_MOEDAS; i++) {
        aux = decimal/moedas[i];
        decimal = decimal % moedas[i];
        if (aux) {
            if (i == 0) {
                printf("%d moedas de 1 REAL\n", aux);
            } else {
                printf("%d moedas de %d centavos\n", aux, moedas[i]);
            }
        }
    }
    printf("\n");
    return;
}

int main() {

    int notas[MAX_NOTAS] = NOTAS;
    int moedas[MAX_MOEDAS] = MOEDAS;
    int inteiro = 0, decimal = 0;
    float valor_compra = 0, valor_pago = 0,valor_troco = 0;

    do {
        menu(notas, moedas);

        printf("Insira o valor da compra: Ex:(00.00)\n");
        scanf("%f", &valor_compra);
        if (valor_compra) {
            printf("Insira o valor pago: Ex:(00.00)\n");
            scanf("%f", &valor_pago);
            
            valor_troco = valor_pago - valor_compra;
            inteiro = valor_troco/1;
            decimal = 100 * (valor_troco - inteiro);

            printf("Troco: %d,%d\n",inteiro,decimal);

            printf("\n");
            if (inteiro != 0 || decimal != 0) {
                troco(notas, moedas, inteiro, decimal);
            }
        }
        
    } while(valor_compra != 0);

    return 0;
}
