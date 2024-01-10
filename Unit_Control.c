#include <stdio.h>
#include "CPU.h"

void limpeza(char s[4]){
    for (int i = 0; i < 4; i++){
        s[i] = ' ';
    }
}

int escolha(regs* R, int PC, FILE* exit){
    char command[4];
    limpeza(command);
    FILE* entry = fopen("instrucao.txt", "r");
    fscanf(entry, "%s", command);
    if(!strcmp(command, "SET")){
        int reg;
        float info;
        fscanf(entry, "%d", &reg);
        fscanf(entry, "%f", &info);
        fclose(entry);
        SET(R, reg, info);
        return PC;
    }
    if(!strcmp(command, "HOP")){
        int line;
        fscanf(entry, "%d", &line);
        fclose(entry);
        return HOP(line);
    }
    if(!strcmp(command, "MEM")){
        int reg;
        fscanf(entry, "%d", &reg);
        fclose(entry);
        MEM(R, exit, reg);
        return PC;
    }
    if(!strcmp(command, "SUM")){
        int reg1, reg2, reg3;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
        fclose(entry);
        SUM(R, reg1, reg2, reg3);
        return PC;
    }
    if(!strcmp(command, "SUB")){
        int reg1, reg2, reg3;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
        fclose(entry);
        SUB(R, reg1, reg2, reg3);
        return PC;
    }
    if(!strcmp(command, "MUL")){
        int reg1, reg2, reg3;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
        fclose(entry);
        MUL(R, reg1, reg2, reg3);
        return PC;
    }
    if(!strcmp(command, "DIV")){
        int reg1, reg2, reg3;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
        fclose(entry);
        DIV(R, reg1, reg2, reg3);
        return PC;
    }
    if(!strcmp(command, "MOD")){
        int reg1, reg2, reg3;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
        fclose(entry);
        MOD(R, reg1, reg2, reg3);
        return PC;
    }
    if(!strcmp(command, "EXP")){
        int reg1, reg2, reg3;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
        fclose(entry);
        EXP(R, reg1, reg2, reg3);
        return PC;
    }
    if(!strcmp(command, "IET")){
        int reg1, reg2, line;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &line);
        fclose(entry);
        return IET(R, reg1, reg2, line,PC);
    }
    if(!strcmp(command, "ILT")){
        int reg1, reg2, line;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &line);
        fclose(entry);
        return ILT(R, reg1, reg2, line,PC);
    }
    return PC;
}
