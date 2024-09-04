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
<hr>
Pergunta: Ao final do processamento, qual será o valor da variável SOMA?

**Resposta**: A variável SOMA terá o valor 91.

<br>
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
    
    printf("O valor da variável SOMA e: %d\n", soma);

    return 0;
}
```

## 2ª Pergunta
Dado a sequência de Fibonacci, onde se inicia por 0 e 1 e o próximo valor sempre será a soma dos dois valores anteriores (exemplo: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34...), escreva um programa em C que calcule a sequência de Fibonacci e retorne uma mensagem indicando se um número informado pertence ou não à sequência.

IMPORTANTE:
Esse número pode ser informado através de qualquer entrada de sua preferência ou pode ser previamente definido no código;

Código em C:

```c
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
```

## 3ª Pergunta
Dado um vetor que guarda o valor de faturamento diário de uma distribuidora, faça um programa, na linguagem que desejar, que calcule e retorne:

   • O menor valor de faturamento ocorrido em um dia do mês;<br>
   • O maior valor de faturamento ocorrido em um dia do mês;<br>
   • Número de dias no mês em que o valor de faturamento diário foi superior à média mensal.<br>

IMPORTANTE:<br>
a) Usar o json ou xml disponível como fonte dos dados do faturamento mensal;<br>
b) Podem existir dias sem faturamento, como nos finais de semana e feriados. Estes dias devem ser ignorados no cálculo da média;

Código em C:
```c
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "cJSON.c"

typedef struct faturamento{
    int data;
    float valor;
} FATURAMENTO;

char *ler_arquivo(char *nome_arquivo);
void menorFaturamento(FATURAMENTO *faturamentoMes, int tamanhoArray);
void maiorFaturamento(FATURAMENTO *faturamentoMes, int tamanhoArray);
void diasSuperioresMedia(FATURAMENTO *faturamentoMes, int tamanhoArray);
float calcularMedia(FATURAMENTO *faturamentoMes, int tamanhoArray);
void transformarJsonFaturamento(FATURAMENTO *faturamentoMes, cJSON *json, int tamanhoJson);

int main(){
    char *nome_arquivo = "dados.json";
    int tamanhoJson = 0;

    char *json_string = ler_arquivo(nome_arquivo);
    if (json_string == NULL) {
        printf("Erro ao abrir o arquivo.\n\n");
        system("pause");
        return 1;
    } else{
        printf("Arquivo Json lido com sucesso!\n\n");
    }

    cJSON *json = cJSON_Parse(json_string);
    if (json == NULL) {
        printf("\nErro ao tranformar o Json.\n\n");
        system("pause");
        return 1;
    }

    free(json_string);
    tamanhoJson = cJSON_GetArraySize(json);

    FATURAMENTO *faturamentoMes = (FATURAMENTO *)malloc(sizeof(FATURAMENTO) * tamanhoJson);
    if (faturamentoMes == NULL) {
        printf("\nErro ao alocar memoria.\n\n");
        system("pause");
        return 1;
    }

    transformarJsonFaturamento(faturamentoMes, json, tamanhoJson);
    menorFaturamento(faturamentoMes, tamanhoJson);
    maiorFaturamento(faturamentoMes, tamanhoJson);
    diasSuperioresMedia(faturamentoMes, tamanhoJson);
    free(faturamentoMes);

    return 0;
}

void transformarJsonFaturamento(FATURAMENTO *faturamentoMes, cJSON *json, int tamanhoJson){
    if (faturamentoMes == NULL) {
        printf("\nErro ao alocar memoria.\n\n");
        system("pause");
        return;
    }

    for(int i = 0; i < tamanhoJson; i++){
        FATURAMENTO faturamentoDia;
        cJSON *dados = cJSON_GetArrayItem(json, i);

        cJSON *jsonDia = cJSON_GetObjectItemCaseSensitive(dados, "dia");
        cJSON *jsonValor = cJSON_GetObjectItemCaseSensitive(dados, "valor");

        faturamentoDia.data = jsonDia->valueint;
        faturamentoDia.valor = jsonValor->valuedouble;

        faturamentoMes[i] = faturamentoDia;
    }
}

void diasSuperioresMedia(FATURAMENTO *faturamentoMes, int tamanhoJson){
    if (faturamentoMes == NULL) {
        printf("\nErro ao alocar memoria.\n\n");
        system("pause");
        return;
    }

    float mediaMensal = calcularMedia(faturamentoMes, tamanhoJson);
    if (mediaMensal == 0) {
        printf("\nErro ao calcular a media.\n\n");
        system("pause");
        return;
    }

    int qtdDiasSuperioresMedia = 0;

    for(int i = 0; i < tamanhoJson; i++){
        if(faturamentoMes[i].valor > mediaMensal){
            qtdDiasSuperioresMedia += 1;
        }
    }
    printf("\n%d dias superaram a media mensal de faturamento! a media mensal e de %.2f reais!\n\n", qtdDiasSuperioresMedia, mediaMensal);
}

float calcularMedia(FATURAMENTO *faturamentoMes, int tamanhoJson){
    if (faturamentoMes == NULL) {
        printf("\nErro ao alocar memoria.\n\n");
        system("pause");
        return 0;
    }

    float receitaTotal = 0;
    int diasConsiderados = 0;

    for(int i = 0; i < tamanhoJson; i++){
        if(faturamentoMes[i].valor != 0.0){
            receitaTotal += faturamentoMes[i].valor;
            diasConsiderados++;
        }
    }
    return receitaTotal / diasConsiderados;
}

void menorFaturamento(FATURAMENTO *faturamentoMes, int tamanhoArray){
    if (faturamentoMes == NULL) {
        printf("\nErro ao alocar memoria.\n\n");
        system("pause");
        return;
    }

    FATURAMENTO menorReceita = faturamentoMes[0];
    for(int i = 1; i < tamanhoArray; i++){
        if(menorReceita.valor > faturamentoMes[i].valor && faturamentoMes[i].valor != 0.0){
            menorReceita.data = faturamentoMes[i].data;
            menorReceita.valor = faturamentoMes[i].valor;
        }
    }
    printf("\nO menor valor de faturamento ocorreu no dia %d, com um valor de %.2f reais", menorReceita.data, menorReceita.valor);
}

void maiorFaturamento(FATURAMENTO *faturamentoMes, int tamanhoArray){
    if (faturamentoMes == NULL) {
        printf("\nErro ao alocar memoria.\n\n");
        system("pause");
        return;
    }

    FATURAMENTO maiorReceita = faturamentoMes[0];
    for(int i = 1; i < tamanhoArray; i++){
        if(maiorReceita.valor < faturamentoMes[i].valor){
            maiorReceita.data = faturamentoMes[i].data;
            maiorReceita.valor = faturamentoMes[i].valor;
        }
    }
    printf("\nO maior valor de faturamento ocorreu no dia %d, com um valor de %.2f reais", maiorReceita.data, maiorReceita.valor);
}

char *ler_arquivo(char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n\n", nome_arquivo);
        system("pause");
        return NULL;
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    rewind(arquivo);

    char *conteudo = (char *)malloc(sizeof(char) * (tamanho_arquivo + 1));
    if (conteudo == NULL) {
        printf("Erro ao alocar memoria.\n\n");
        system("pause");
        fclose(arquivo);
        return NULL;
    }

    fread(conteudo, 1, tamanho_arquivo, arquivo);
    conteudo[tamanho_arquivo] = '\0';
    fclose(arquivo);

    return conteudo;
}
```
Utilizei a biblioteca cJSON para manipular o arquivo Json. Abaixo segue o link para o repositório:<br>
https://github.com/DaveGamble/cJSON?tab=readme-ov-file

Além disso, vale ressaltar que desconsiderei os dias com faturamento nulo ou 0 nas operações (maior, menor e média). 

## 4ª Pergunta
Dado o valor de faturamento mensal de uma distribuidora, detalhado por estado:

   SP – R$67.836,43<br>
   RJ – R$36.678,66<br>
   MG – R$29.229,88<br>
   ES – R$27.165,48<br>
   Outros – R$19.849,53<br>

Escreva um programa na linguagem que desejar onde calcule o percentual de representação que cada estado teve dentro do valor total mensal da distribuidora.

Código em C:
```c
#include <stdio.h>
#include <stdlib.h>

float calcularPercentual(float contibuicaoEstado, float contribuicaoTotal);

int main(){
    float contribuicaoSp = 67836.43;
    float contribuicaoRj = 36678.66;
    float contribuicaoMg = 29229.88;
    float contribuicaoEs = 27165.48;
    float contribuicaoOutros = 19849.53;
    float contribuicaoTotal = contribuicaoSp + contribuicaoRj + contribuicaoMg + contribuicaoEs + contribuicaoOutros;

    printf("A contribuicao de SP no lucro total foi de %.2f%%", calcularPercentual(contribuicaoSp, contribuicaoTotal));
    printf("\nA contribuicao de RJ no lucro total foi de %.2f%%", calcularPercentual(contribuicaoRj, contribuicaoTotal));
    printf("\nA contribuicao de MG no lucro total foi de %.2f%%", calcularPercentual(contribuicaoMg, contribuicaoTotal));
    printf("\nA contribuicao de ES no lucro total foi de %.2f%%", calcularPercentual(contribuicaoEs, contribuicaoTotal));
    printf("\nA contribuicao de Outros estados no lucro total foi de %.2f%%", calcularPercentual(contribuicaoOutros, contribuicaoTotal));
    printf("\n\nA contribuicao total foi de %.2f reais", contribuicaoTotal);
    
    return 0
}

float calcularPercentual(float contibuicaoEstado, float contribuicaoTotal){
    return (contibuicaoEstado / contribuicaoTotal) * 100;
}
```

## 5ª Pergunta
Escreva um programa que inverta os caracteres de um string.

IMPORTANTE:<br>
a) Essa string pode ser informada através de qualquer entrada de sua preferência ou pode ser previamente definida no código<br>
b) Evite usar funções prontas, como, por exemplo, reverse;

Código em C:

```c
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
```
