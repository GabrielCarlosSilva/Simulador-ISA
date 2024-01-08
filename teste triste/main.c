#include "isa.h"

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