#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NOTAS 6
#define MAX_MOEDAS 6

//#define NOTAS {100, 50, 20, 10, 5, 2}
//#define MOEDAS {100, 50, 25, 10, 5, 1}

typedef struct notas{
  int valor;
  int quantidade;
} NOTA;

typedef struct moedas{
  int valor;
  int quantidade;
} MOEDA;

void menu(NOTA *notas, MOEDA *moedas) {
    printf("\n\tSistema de troco:\n\n");
    printf("Para o troco, temos as seguintes notas e moedas:\n");

    printf("Notas:\n");
    for (int i = 0; i < MAX_NOTAS; i++) {
        printf("%d notas de %d", notas[i].quantidade,notas[i].valor);
	if (i != MAX_NOTAS - 1) {
		printf(", ");
	} else {
		printf(".\n");
	}
    }

    printf("Moedas:\n");
    for (int i = 0; i < MAX_MOEDAS; i++) {
        if(i == 0) {
            printf("%d moedas de 1 REAL, ", moedas[i].quantidade);
        } else if (i != MAX_MOEDAS - 1) {
            printf("%d moedas de %d centavos, ", moedas[i].quantidade, moedas[i].valor);
        } else {
            printf("e %d moedas de 1 centavo.\n", moedas[i].quantidade);
        }
    }
    printf("\n");
}

void troco(NOTA *notas, MOEDA *moedas, int inteiro, int decimal) {
    int aux = 0;
    float teste;

    printf("Foram utilizadas as seguintes notas e moedas para o troco:\n");
    for (int i = 0; i < MAX_NOTAS; i++) {
        while(inteiro - notas[i].valor >= 0 && notas[i].quantidade > 0){
          aux++;
          inteiro = inteiro - notas[i].valor;
          notas[i].quantidade = notas[i].quantidade - 1;
        }

        if (aux) {
            printf("%d notas de %d reais\n", aux, notas[i].valor);
        } else {
            // Nothing to do.
        }
        //Reinicia o aux para a proxima iteracao
        aux = 0;
    }

    if (inteiro != 0) {
        aux = inteiro / 1;
        decimal += aux * 100;
        inteiro = 0;
    }

    printf("\n");
    for (int i = 0; i < MAX_MOEDAS; i++) {
      aux = 0;
      while(decimal - moedas[i].valor >= 0 && moedas[i].quantidade > 0){
        aux++;
        decimal = decimal - moedas[i].valor;
        moedas[i].quantidade = moedas[i].quantidade - 1;
      }

      if (aux) {
        if (i == 0) {
          printf("%d moedas de 1 REAL\n", aux);
        } else {
          printf("%d moedas de %d centavos\n", aux, moedas[i].valor);
        }
      }
    }
    printf("\n");
    if(decimal != 0)
      printf("Por insuficiencia do caixa, ficou faltando R$ %.2f do troco\n", (float)decimal/100);
    return;
}

void iniciaCaixa(NOTA *notas,MOEDA *moedas){
    for(int i = 0; i < MAX_NOTAS;i++){
      notas[i].quantidade = rand() %10 + 1;
    }
    for(int i = 0; i < MAX_MOEDAS;i++){
      moedas[i].quantidade = rand() %10 + 1;
    }

}

int main() {

    //int notas[MAX_NOTAS] = NOTAS;
    //int moedas[MAX_MOEDAS] = MOEDAS;
    srand(time(NULL));
    NOTA notas[MAX_NOTAS];
    MOEDA moedas[MAX_MOEDAS];
    int inteiro = 0, decimal = 0;
    float valor_compra = 0, valor_pago = 0,valor_troco = 0;

    //Atribuicao do valor das notas
    notas[0].valor = 100;
    notas[1].valor = 50;
    notas[2].valor = 20;
    notas[3].valor = 10;
    notas[4].valor = 5;
    notas[5].valor = 2;

    // Atribuicao do valor das moedas
    moedas[0].valor = 100;
    moedas[1].valor = 50;
    moedas[2].valor = 25;
    moedas[3].valor = 10;
    moedas[4].valor = 5;
    moedas[5].valor = 1;


    iniciaCaixa(notas,moedas);

    do {
        menu(notas, moedas);

        printf("Insira o valor da compra: Ex:(00.00) ou digite 0 para encerrar o programa\n");
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
