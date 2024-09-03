# Estágio Target Sistemas

Este repositório contém as respostas para as perguntas técnicas solicitadas.

## 1ª Pergunta

Considere o seguinte trecho de código:

```c
int INDICE = 13, SOMA = 0, K = 0;
Enquanto K < INDICE faça {
    K = K + 1;
    SOMA = SOMA + K;
}
Imprimir(SOMA);
```

Pergunta: Ao final do processamento, qual será o valor da variável SOMA?

**Resposta**: A variável SOMA terá o valor 78.

Código em C:

```c
#include <stdio.h>

int main() {
    int soma = 0;
    int indice = 13;
    int k = 0;
    
    for (k; k < indice; k++) {
        soma += k + 1;
    }
    
    printf("O valor da variável SOMA é: %d\n", soma);
    return 0;
}
```

## 2ª Pergunta
Dado a sequência de Fibonacci, onde se inicia por 0 e 1 e o próximo valor sempre será a soma dos dois valores anteriores (exemplo: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34...), escreva um programa em C que calcule a sequência de Fibonacci e retorne uma mensagem indicando se um número informado pertence ou não à sequência.

Código em C:

```c
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
```
