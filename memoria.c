#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CPU.h"


#define MAX_RAM 134217728
#define MAX_INSTRU 32 

int tamanhoArquivo(FILE* arq){
    char linha[99];
    int linhas = 0;
    while (fgets(linha, 99, arq) != NULL){
        linhas++;
    }
    rewind(arq); // Volta ao início do arquivo
    return linhas + 1;
}

int GastoMemoria(char* nome){

    Memoria mem;
    mem.Mem_Instrucao=0;
    FILE* entry = fopen(nome, "r");
    int max_linhas = tamanhoArquivo(entry);
    for(int i=0; i<max_linhas; i++){

        fgets(mem.instrucao,100, entry);
        mem.Mem_Instrucao = analise_opcode(mem.instrucao);
        if(mem.Mem_Instrucao<=MAX_INSTRU){
            mem.RAM=mem.RAM+mem.Mem_Instrucao;
        }
        if(mem.RAM>MAX_RAM || mem.Mem_Instrucao>MAX_INSTRU){
            printf("Memória Principal Sobrecarregada. Abortar Execução!\n");
            fclose(entry);
            return 0;
        }       
    }
    fclose(entry);

    return 1;
}

int EnviaInstrucao(int PC, char*nome){

    Memoria mem;
    FILE* entry = fopen(nome,"r");
    int max_linhas=tamanhoArquivo(entry);
    if(PC>max_linhas){
        fclose(entry);
        return 0;
    }
    for(int i=0; i<PC; i++)
        fgets(mem.instrucao, 100, entry);
    
    FILE* instrucao = fopen("instrucao.txt", "w");
    fprintf(instrucao, "%s", mem.instrucao);
    fclose(entry);
    fclose(instrucao);
    return 1;
}

int analise_opcode(char* linha){
    if(strstr(linha, "SET") != NULL)
        return 32;
    if(strstr(linha, "HOP") != NULL)
        return 32;
    if(strstr(linha, "MEM") != NULL)
        return 8;
    if(strstr(linha, "SUM") != NULL)
        return 16;
    if(strstr(linha, "SUB") != NULL)
        return 16;
    if(strstr(linha, "MUL") != NULL)
        return 16;
    if(strstr(linha, "DIV") != NULL)
        return 16;
    if(strstr(linha, "MOD") != NULL)
        return 16;
    if(strstr(linha, "EXP") != NULL)
        return 16;
    if(strstr(linha, "IET") != NULL)
        return 32;
    if(strstr(linha, "ILT") != NULL)
        return 32;
    return 0;
}
