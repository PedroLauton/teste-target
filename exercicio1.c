#include <stdio.h>

int main() {
    int soma = 0;
    int indice = 13;
    int k = 0;

    for (k; k < indice; k++) {
        soma += k + 1;
    }

    printf("O valor da vari�vel SOMA �: %d\n", soma);

    return 0;
}
