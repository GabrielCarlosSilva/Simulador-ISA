#include "isa.h"

//// Funções administrativas
//  Salva a informação recibida em um registrador cuja posição foi recebida (SET)
int SET(regs* R, int reg, int info){
    if(reg > 15 || reg <= 1)
        return 0;
    R[reg].info = info;
    return 1;
}

//  Pula para a linha recebida (HOP)
int HOP(FILE* entry, int line, char Nome_arquivo[26], int max_linhas){
    if(line > max_linhas || line < 0)
        return 0;
    char trash[99];
    fclose(entry);
    entry = fopen(Nome_arquivo, "r");
    for(int i = 0; i < line - 1; i++)
        fgets(trash, 99, entry);
    return 1;
}

//  Guarda a informação do registrador na memoria (MEMORY)
int MEM(regs* R, FILE* exit, int reg){
    if(reg > 15 || reg <= 1)
        return 0;
    fprintf(exit, "%.0f \n", R[reg].info);
    return 1;
}

//// Funções matemáticas
// Soma simples, resultado em r3 (r1 + r2 = r3)
void SUM(regs* R, int r1, int r2, int r3){
    R[r3].info = R[r1].info + R[r2].info;
}

//  Subtração simples, resultado em r3 (r1 - r2 = r3)
void SUB(regs* R, int r1, int r2, int r3){
    R[r3].info = R[r1].info - R[r2].info;
}

//  Modulo simples, resultado em r3 (r1 % r2 = r3)
void MOD(regs* R, int r1, int r2, int r3){
    R[r3].info = (int) R[r1].info % (int) R[r2].info;
}

//  Exponeciação simples, resultado em r3 (r²)
void EXP(regs* R, int r1, int r2, int r3){
    R[r3].info = R[r1].info;
    for (int i = 0; i < (int) R[r2].info; i++){
        R[r3].info *= R[r1].info; 
    }
}

////  Funções lógicas
//  Verifica igualdade, caso positivo, pule para linha recebida (r1 == r2 ? line)
void IET(FILE* entry, regs* R, int r1, int r2, int line, char Nome_arquivo[26], int max_linhas){
    if(R[r1].info == R[r2].info)
        HOP(entry, line, Nome_arquivo, max_linhas);
}

//  Verifica se r1 é menor que r2, caso positivo, pule para linha recebida (r1 < r2 ? line)
void ILT(FILE* entry, regs* R, int r1, int r2, int line, char Nome_arquivo[26], int max_linhas){
    if(R[r1].info < R[r2].info)
        HOP(entry, line, Nome_arquivo, max_linhas);
}


//// Funções de emulação
// Limpa a string de comando
void limpeza(char s[3]){
    for (int i = 0; i < 4; i++){
        s[i] = ' ';
    } 
}

// Calcula o número total de linhas no arquivo recebido
int tamanhoArquivo(FILE* arq){
    char linha[99];
    int linhas = 0;
    while (fgets(linha, 99, arq) != NULL){
        linhas++;
    }
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
int charToBin(FILE* entry){
    char bin1[8], bin2[8];
    fscanf(entry, "%s", bin1);
    for(int i = 0; i < 8; i++)
        bin2[i] = '0';
    for (int i = 0; i < (int) strlen(bin1); i++)
        bin2[7 - i] = bin1[strlen(bin1) - i - 1];
    return binToFloat(bin2);
}
