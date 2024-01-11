#include <stdio.h>
#include "CPU.h"

void limpeza(char s[4]){
    for (int i = 0; i < 4; i++){
        s[i] = ' ';
    }
}

int EnderecoToInt(char endereco[4]){

    int num,aux=2;
    char enderecoC[3];
    if(endereco[3]=='\0')
        aux=3;
    for(int i=0; i<aux; i++)
        enderecoC[i]=endereco[i+1];
    num=atoi(enderecoC);
    return num;    
}

int escolha(regs* R, int PC, FILE* exit){
    char command[4], regc[4];
    limpeza(command);
    limpeza(regc);
    FILE* entry = fopen("instrucao.txt", "r");
    fscanf(entry, "%s", command);
    if(!strcmp(command, "SET")){
        int reg;
        float info;
        fscanf(entry, "%s", regc);
        reg=EnderecoToInt(regc);
        fscanf(entry, "%f", &info);
        fclose(entry);
        SET(R, reg, info);
    }
    if(!strcmp(command, "HOP")){
        int line;
        fscanf(entry, "%d", &line);
        fclose(entry);
        return HOP(line) -1;
    }
    if(!strcmp(command, "MEM")){
        int reg;
        fscanf(entry, "%s", regc);
        reg=EnderecoToInt(regc);
        fclose(entry);
        MEM(R, exit, reg);
    }
    if(!strcmp(command, "SUM")){
        int reg[3];
        for(int i=0; i<3; i++){
            fscanf(entry, "%s", regc);
            reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        SUM(R, reg[0], reg[1], reg[2]);
    }
    if(!strcmp(command, "SUB")){
        int reg[3];
        for(int i=0; i<3; i++){
            fscanf(entry, "%s", regc);
            reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        SUB(R, reg[0], reg[1], reg[2]);

    }
    if(!strcmp(command, "MUL")){
        int reg[3];
        for(int i=0; i<3; i++){
            fscanf(entry, "%s", regc);
            reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        MUL(R, reg[0], reg[1], reg[2]);
    }
    if(!strcmp(command, "DIV")){
        int reg[3];
        for(int i=0; i<3; i++){
            fscanf(entry, "%s", regc);
            reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        DIV(R, reg[0], reg[1], reg[2]);

    }
    if(!strcmp(command, "MOD")){
        int reg[3];
        for(int i=0; i<3; i++){
            fscanf(entry, "%s", regc);
            reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        MOD(R, reg[0], reg[1], reg[2]);
    }
    if(!strcmp(command, "EXP")){
        int reg[3];
        for(int i=0; i<3; i++){
            fscanf(entry, "%s", regc);
            reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        EXP(R, reg[0], reg[1], reg[2]);
    }
    if(!strcmp(command, "IET")){
        
        int reg[2], line;
        for(int i=0; i<2; i++){
            fscanf(entry, "%s", regc);
            reg[i]= EnderecoToInt(regc);
        }
        fscanf(entry, "%d", &line);
        fclose(entry);
        return IET(R, reg[0], reg[1], line,PC);
    }
    if(!strcmp(command, "ILT")){
        int reg[2], line;
        for(int i=0; i<2; i++){
            fscanf(entry, "%s", regc);
            reg[i]= EnderecoToInt(regc);
        }
        fscanf(entry, "%d", &line);
        fclose(entry);
        return ILT(R, reg[0], reg[1], line,PC);
    }
    if(!strcmp(command, "CPY")){
        int reg[2];
        for(int i=0; i<2; i++){
            fscanf(entry, "%s", regc);
            reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        CPY(R, reg[0], reg[1]);
    }
    return PC;
}
