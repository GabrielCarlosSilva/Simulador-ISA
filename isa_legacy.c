#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
    int info;
}regs;

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
    fprintf(exit, "%d \n", R[reg].info);
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
    R[r3].info = pow(R[r1].info, R[r2].info);
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
void limpeza(char s[4]){
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
    rewind(arq); // Volta ao início do arquivo
    return linhas + 1;
}


//  Função que escolhe o op code apropriado
int escolha(FILE* entry, FILE* exit, regs* R, char Nome_arquivo[26], int max_linhas){
    char command[4];
    limpeza(command);
    fscanf(entry, "%s", command);
    if(!strcmp(command, "SET")){
        int reg, info;
        fscanf(entry, "%d", &reg);
        fscanf(entry, "%d", &info);
        return SET(R, reg, info);
    }
    if(!strcmp(command, "HOP")){
        int line;
        fscanf(entry, "%d", &line);
        return HOP(entry, line, Nome_arquivo, max_linhas);
    }
    if(!strcmp(command, "MEM")){
        int reg;
        fscanf(entry, "%d", &reg);
        return MEM(R, exit, reg);
    }
    if(!strcmp(command, "SUM")){
        int reg1, reg2, reg3;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
        SUM(R, reg1, reg2, reg3);
        return 1;
    }
    if(!strcmp(command, "SUB")){
        int reg1, reg2, reg3;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
        SUB(R, reg1, reg2, reg3);
        return 1;
    }
    if(!strcmp(command, "MOD")){
        int reg1, reg2, reg3;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
        MOD(R, reg1, reg2, reg3);
        return 1;
    }
    if(!strcmp(command, "EXP")){
        int reg1, reg2, reg3;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
        EXP(R, reg1, reg2, reg3);
        return 1;
    }
    if(!strcmp(command, "IET")){
        int reg1, reg2, line;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &line);
        IET(entry, R, reg1, reg2, line, Nome_arquivo, max_linhas);
        return 1; 
    }
    if(!strcmp(command, "ILT")){
        int reg1, reg2, line;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &line);
        ILT(entry, R, reg1, reg2, line, Nome_arquivo, max_linhas);
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

    getchar(); // Limpa o buffer de entrada
    fclose(entry);
    fclose(result);
    return 0;
}