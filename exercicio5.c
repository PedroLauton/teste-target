#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inverterFrase(char frase[]);

int main() {
    char frase[100];
    printf("Digite uma frase com no maximo 100 caracteres: ");
    fgets(frase, sizeof(frase), stdin);

    size_t comprimento = strlen(frase);
    if (comprimento > 0 && frase[comprimento - 1] == '\n') {
        frase[comprimento - 1] = '\0';
    }

    printf("Frase digitada: %s\n", frase);
    inverterFrase(frase);
    printf("Frase invertida: %s\n", frase);

    return 0;
}

void inverterFrase(char frase[]) {
    int comprimento = strlen(frase);
    char fraseAuxiliar[100];

    for (int i = 0; i < comprimento; i++) {
        fraseAuxiliar[i] = frase[comprimento - i - 1];
    }

    fraseAuxiliar[comprimento] = '\0';
    strcpy(frase, fraseAuxiliar);
}
