#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
    float info;
}regs;

//// Funções administrativas
//  Salva a informação recibida em um registrador cuja posição foi recebida (SET)
int ST(regs* R, int reg, int info){
    if(reg > 15 || reg <= 1)
        return 0;
    R[reg].info = info;
    return 1;
}

//  Pula para a linha recebida (HOP)
int HP(FILE* entry, int line, char Nome_arquivo[26], int max_linhas){
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
int MM(regs* R, FILE* exit, int reg){
    if(reg > 15 || reg <= 1)
        return 0;
    fprintf(exit, "%.0f \n", R[reg].info);
    return 1;
}

//// Funções matemáticas
// Soma simples, resultado em r3 (r1 + r2 = r3)
void SM(regs* R, int r1, int r2, int r3){
    R[r3].info = R[r1].info + R[r2].info;
}

//  Subtração simples, resultado em r3 (r1 - r2 = r3)
void SB(regs* R, int r1, int r2, int r3){
    R[r3].info = R[r1].info - R[r2].info;
}

//  Modulo simples, resultado em r3 (r1 % r2 = r3)
void MD(regs* R, int r1, int r2, int r3){
    R[r3].info = (int) R[r1].info % (int) R[r2].info;
}

//  Exponeciação simples, resultado em r3 (r²)
void EX(regs* R, int r1, int r2, int r3){
    R[r3].info = pow(R[r1].info, R[r2].info);
}

////  Funções lógicas
//  Verifica igualdade, caso positivo, pule para linha recebida (r1 == r2 ? line)
void IE(FILE* entry, regs* R, int r1, int r2, int line, char Nome_arquivo[26], int max_linhas){
    if(R[r1].info == R[r2].info)
        HP(entry, line, Nome_arquivo, max_linhas);
}

//  Verifica se r1 é menor que r2, caso positivo, pule para linha recebida (r1 < r2 ? line)
void IL(FILE* entry, regs* R, int r1, int r2, int line, char Nome_arquivo[26], int max_linhas){
    if(R[r1].info < R[r2].info)
        HP(entry, line, Nome_arquivo, max_linhas);
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

//  Função que escolhe o op code apropriado
int escolha(FILE* entry, FILE* exit, regs* R, char Nome_arquivo[26], int max_linhas){
    char command[3];
    limpeza(command);
    fscanf(entry, "%s", command);
    if(!strcmp(command, "ST")){
        int reg, info;
        reg = charToBin(entry);
        info = charToBin(entry);
        return ST(R, reg, info);
    }
    if(!strcmp(command, "HP")){
        int line = charToBin(entry);
        return HP(entry, line, Nome_arquivo, max_linhas);
    }
    if(!strcmp(command, "MM")){
        int reg = charToBin(entry);
        return MM(R, exit, reg);
    }
    if(!strcmp(command, "SM")){
        int reg1, reg2, reg3;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        reg3 = charToBin(entry);
        SM(R, reg1, reg2, reg3);
        return 1;
    }
    if(!strcmp(command, "SB")){
        int reg1, reg2, reg3;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        reg3 = charToBin(entry);
        SB(R, reg1, reg2, reg3);
        return 1;
    }
    if(!strcmp(command, "MD")){
        int reg1, reg2, reg3;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        reg3 = charToBin(entry);
        MD(R, reg1, reg2, reg3);
        return 1;
    }
    if(!strcmp(command, "EX")){
        int reg1, reg2, reg3;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        reg3 = charToBin(entry);
        EX(R, reg1, reg2, reg3);
        return 1;
    }
    if(!strcmp(command, "IE")){
        int reg1, reg2, line;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        line = charToBin(entry);
        IE(entry, R, reg1, reg2, line, Nome_arquivo, max_linhas);
        return 1; 
    }
    if(!strcmp(command, "IL")){
        int reg1, reg2, line;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        line = charToBin(entry);
        IL(entry, R, reg1, reg2, line, Nome_arquivo, max_linhas);
        return 1;
    }
    return 0;
}


int main(){
    char Nome_arquivo[26];
    regs R[16];
    R[0].info = 0;
    R[1].info = 1;

    int saida = 1;

    printf("Nome do arquivo de entrada: ");
    scanf("%s", Nome_arquivo);

    FILE* entry = fopen(Nome_arquivo, "r");
    int max_linhas = tamanhoArquivo(entry);
    entry = fopen(Nome_arquivo, "r");
    FILE* result = fopen("saida.txt", "w");

    while (saida == 1){
        saida = escolha(entry, result, R, Nome_arquivo, max_linhas);
    }

    fclose(entry);
    fclose(result);
    return 0;
}