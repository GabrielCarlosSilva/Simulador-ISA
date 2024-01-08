#include "isa.h"

int escolha(FILE* entry, FILE* exit, regs* R, char Nome_arquivo[26], int max_linhas){
    char command[3];
    limpeza(command);
    fscanf(entry, "%s", command);
    if(!strcmp(command, "SET")){
        int reg, info;
        reg = charToBin(entry);
        info = charToBin(entry);
        return SET(R, reg, info);
    }
    if(!strcmp(command, "HOP")){
        int line = charToBin(entry);
        return HOP(entry, line, Nome_arquivo, max_linhas);
    }
    if(!strcmp(command, "MEM")){
        int reg = charToBin(entry);
        return MEM(R, exit, reg);
    }
    if(!strcmp(command, "SUM")){
        int reg1, reg2, reg3;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        reg3 = charToBin(entry);
        SUM(R, reg1, reg2, reg3);
        return 1;
    }
    if(!strcmp(command, "SUB")){
        int reg1, reg2, reg3;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        reg3 = charToBin(entry);
        SUB(R, reg1, reg2, reg3);
        return 1;
    }
    if(!strcmp(command, "MOD")){
        int reg1, reg2, reg3;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        reg3 = charToBin(entry);
        MOD(R, reg1, reg2, reg3);
        return 1;
    }
    if(!strcmp(command, "EXP")){
        int reg1, reg2, reg3;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        reg3 = charToBin(entry);
        EXP(R, reg1, reg2, reg3);
        return 1;
    }
    if(!strcmp(command, "IET")){
        int reg1, reg2, line;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        line = charToBin(entry);
        IET(entry, R, reg1, reg2, line, Nome_arquivo, max_linhas);
        return 1; 
    }
    if(!strcmp(command, "ILT")){
        int reg1, reg2, line;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        line = charToBin(entry);
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

    fclose(entry);
    fclose(result);
    return 0;
}