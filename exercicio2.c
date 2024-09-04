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

    printf("Sequência de Fibonacci gerada:\n");
    for (int i = 0; i < tamanhoArray; i++) {
        printf("%d ", sequenciaFibonacci[i]);
    }
    printf("\n");

    printf("Digite um número para verificar se faz parte da Sequência de Fibonacci: ");
    if (scanf("%d", &escolha) != 1) {
        printf("Entrada inválida.\n");
        return 1;
    }

    for (int i = 0; i < tamanhoArray; i++) {
        if (escolha == sequenciaFibonacci[i]) {
            encontro = 1;
            break;
        }
    }

    if (encontro) {
        printf("O número %d faz parte da Sequência de Fibonacci!\n", escolha);
    } else {
        printf("O número %d não faz parte da Sequência de Fibonacci.\n", escolha);
    }

    return 0;
}
