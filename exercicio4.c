#include <stdio.h>
#include <stdlib.h>

float calcularPercentual(float contibuicaoEstado, float contribuicaoTotal);

int main(void){
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

}

float calcularPercentual(float contibuicaoEstado, float contribuicaoTotal){
    return (contibuicaoEstado / contribuicaoTotal) * 100;
}
