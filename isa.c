#include "isa.h"

//// Funções administrativas
//  Pula para a linha recebida (HOP)
void HP(FILE* entry, int line, char Nome_arquivo[26]){
    char trash[99];
    fclose(entry);
    entry = fopen(Nome_arquivo, "r");
    for(int i = 0; i < line - 1; i++){
        printf("ping %d\n", i);
        fgets(trash, 98, entry);
    }
}
//  Guarda a informação do registrador na memoria (MEMORY)
void MM(FILE* exit, float info){
    fprintf(exit, "%.0f \n", info);
}

//// Funções matemáticas
// Soma simples, resultado em r3 (r1 + r2 = r3)
float SM(float r1, float r2){
    return r1 + r2;  
}
//  Subtração simples, resultado em r3 (r1 - r2 = r3)
float SB(float r1, float r2){
    return r1 - r2;  
}
//  Modulo simples, resultado em r3 (r1 % r2 = r3)
float MD(float r1, float r2){
    return ((int) r1 % (int) r2);  
}
//  Exponeciação simples, resultado em r3 (r²)
float EX(float r1, float r2){
    float retn = 1;
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
// Converte binário para ponto flutuante
float binToFloat(char *bin){
    float saida = 0.0;
    int potencia = 1;
    for (int i = 7; i >= 0; i--){
        if(bin[i] == '1')
            saida += potencia;
        potencia *= 2;
    }
    return saida;
}
// Converte charactere para binário
float charToBin(FILE* entry){
    char bin1[8], bin2[8];
    fscanf(entry, "%s", bin1);
    for(int i = 0; i < 8; i++)
        bin2[i] = '0';
    for (int i = 0; i < (int) strlen(bin1); i++)
        bin2[7 - i] = bin1[strlen(bin1) - i - 1];
    return binToFloat(bin2);
}
