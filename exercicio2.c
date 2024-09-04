#include <stdio.h>

int main() {
    int numAnterior = 0;
    int numAtual = 1;
    int numInserir = 0;
    int sequenciaFibonacci[40];
    int escolha;
    int encontro = 0;

    int tamanhoArray = sizeof(sequenciaFibonacci) / sizeof(sequenciaFibonacci[0]);

    for (int i = 0; i < tamanhoArray; i++) {
        if (i == 0) {
            sequenciaFibonacci[i] = numAnterior;
        } else if (i == 1) {
            sequenciaFibonacci[i] = numAtual;
        } else {
            numInserir = numAnterior + numAtual;
            sequenciaFibonacci[i] = numInserir;
            numAnterior = numAtual;
            numAtual = numInserir;
        }
    }

    printf("Sequ�ncia de Fibonacci gerada:\n");
    for (int i = 0; i < tamanhoArray; i++) {
        printf("%d ", sequenciaFibonacci[i]);
    }
    printf("\n");

    printf("Digite um n�mero para verificar se faz parte da Sequ�ncia de Fibonacci: ");
    if (scanf("%d", &escolha) != 1) {
        printf("Entrada inv�lida.\n");
        return 1;
    }

    for (int i = 0; i < tamanhoArray; i++) {
        if (escolha == sequenciaFibonacci[i]) {
            encontro = 1;
            break;
        }
    }

    if (encontro) {
        printf("O n�mero %d faz parte da Sequ�ncia de Fibonacci!\n", escolha);
    } else {
        printf("O n�mero %d n�o faz parte da Sequ�ncia de Fibonacci.\n", escolha);
    }

    return 0;
}
