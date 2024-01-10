#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_RAM 134217728
#define MAX_INSTRU 32 

typedef struct{
    int* RAM;
    int Mem_Instrucao;
}Memoria;



FILE* memoria(char* nom){

    Memoria mem;
    char linha[1024];
    mem.RAM=0;
    mem.Mem_Instrucao=0;
    FILE* entry = fopen(nom, "r");
    int max_linhas = tamanhoArquivo(entry);
    for(int i=0; i<max_linhas; i++){

        fgets(linha,1024, entry);
        mem.Mem_Instrucao = analise_opcode(linha);
        if(mem.Mem_Instrucao<=MAX_INSTRU){
            mem.RAM=mem.RAM+mem.Mem_Instrucao;
        }
        if(mem.RAM>MAX_RAM){
            printf("Memória Principal Sobrecarregada. Abortar Execução!\n");
            exit(1);
        }
            
    }
    
    rewind(entry);
    return entry;
    
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
}
