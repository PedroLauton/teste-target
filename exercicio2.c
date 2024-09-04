#include <stdio.h>

void gerarSequencia(int sequenciaFibonacci[], int tamanhoArray);
void imprimirSequencia(int sequenciaFibonacci[], int tamanhoArray);
void encontrarNumero(int sequenciaFibonacci[], int escolha, int tamanhoArray);


int main() {
    int sequenciaFibonacci[40];
    int escolha;
    
    int tamanhoArray = sizeof(sequenciaFibonacci) / sizeof(sequenciaFibonacci[0]);
    gerarSequencia(sequenciaFibonacci, tamanhoArray);
    imprimirSequencia(sequenciaFibonacci, tamanhoArray);
    
    printf("Digite um numero para verificar se faz parte da Sequencia de Fibonacci: ");
    if (scanf("%d", &escolha) != 1) {
        printf("Entrada invalida.\n");
        return 1;
    }

    encontrarNumero(sequenciaFibonacci, escolha, tamanhoArray);

    return 0;
}

void gerarSequencia(int sequenciaFibonacci[], int tamanhoArray){
    int numAnterior = 0;
    int numAtual = 1;
    int numInserir = 0;
    
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
}

void imprimirSequencia(int sequenciaFibonacci[], int tamanhoArray){
    printf("Sequencia de Fibonacci gerada:\n");
    for (int i = 0; i < tamanhoArray; i++) {
        printf("%d ", sequenciaFibonacci[i]);
    }
    printf("\n\n");
}

void encontrarNumero(int sequenciaFibonacci[], int escolha, int tamanhoArray){
    int encontro = 0;
    
    for (int i = 0; i < tamanhoArray; i++) {
        if (escolha == sequenciaFibonacci[i]) {
            encontro = 1;
            break;
        }
    }
    
    if (encontro) {
        printf("\nO número %d faz parte da Sequencia de Fibonacci!\n", escolha);
    } else {
        printf("\nO número %d não faz parte da Sequencia de Fibonacci.\n", escolha);
    }
}
