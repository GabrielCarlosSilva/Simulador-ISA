#include "isa.h"

//// Funções administrativas
//  Pula para a linha recebida (HOP)
void HOP(FILE* entry, int line, char Nome_arquivo[26]){
    char trash[99];
    fclose(entry);
    entry = fopen(Nome_arquivo, "r");
    for(int i = 0; i < line - 1; i++){
        fgets(trash, 98, entry);
    }
}
//  Guarda a informação do registrador na memoria (MEMORY)
void MEM(FILE* exit, double info){
    fprintf(exit, "%.0lf \n", info);
}

//// Funções matemáticas
// Soma simples (r1 + r2)
double SUM(double r1, double r2){
    return r1 + r2;  
}
//  Subtração simples (r1 - r2)
double SUB(double r1, double r2){
    return r1 - r2;  
}
//  Multuplicação simples (r1 * r2)
double MUL(double r1, double r2){
    return r1 * r2;
}
// Divisão simples (r1 / r2)
double DIV(double r1, double r2){
    return r1 / r2;
}
//  Modulo simples (r1 % r2)
double MOD(double r1, double r2){
    return ((int) r1 % (int) r2);  
}
//  Exponeciação simples (r1 ^ r2)
double EXP(double r1, double r2){
    double retn = 1;
    for(int i = 0; i < (int) r2; i++)
        retn *= r1;
    return retn;
}

//// Funções de emulação
// Limpa a string de comando
void limpeza(char s[3]){
    for (int i = 0; i < 4; i++)
        s[i] = ' ';
}
// Calcula o número total de linhas no arquivo recebido
int tamanhoArquivo(FILE* arq){
    char linha[99];
    int linhas = 0;
    while (fgets(linha, 99, arq) != NULL)
        linhas++;
    fclose(arq);
    return linhas + 1;
}
