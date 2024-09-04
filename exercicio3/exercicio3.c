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
