#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
    int info;
}regs;

int ACC = 0;                // Memoria acessivel
int linha_atual = 0;        // Posição atual do código
int max_linhas = 17;         // Tamanho máximo do arquivo

//// Funções administrativas
int SET(regs* R, int reg, int info){
    if(reg > 15 || reg <= 1)
        return 0;
    R[reg].info = info;
    return 1;
}

int SIN(regs* R, int reg){
    if(reg > 15 || reg <= 1)
        return 0;
    R[reg].info = ACC;
    ACC = 0;
    return 1;  
}

int HOP(FILE* entry, int line){
    if(line > max_linhas || line < 0)
        return 0;
    char trash[99];
    fclose(entry);
    entry = fopen("entrada.txt", "r");
    for(int i = 0; i < line - 1; i++)
        fgets(trash, 99, entry);
    linha_atual = line - 1;
    return 1;
}

int MEM(regs* R, FILE* exit, int reg){
    if(reg > 15 || reg <= 1)
        return 0;
    fprintf(exit, "%d \n", R[reg].info);
    return 1;
}

//// Funções matemáticas
void SUM(regs* R, int r1, int r2){
    ACC = R[r1].info + R[r2].info;
}

void SUB(regs* R, int r1, int r2){
    ACC = R[r1].info - R[r2].info;
}

void MOD(regs* R, int r1, int r2){
    ACC = R[r1].info % R[r2].info;
}

int fact(int n){
    if(n == 1)
        return 1;
    return n * fact(n - 1);
}

void FRC(regs* R, int rx){
    ACC = fact(R[rx].info);
}

void EXP(regs* R, int r1, int r2){
    ACC = pow(R[r1].info, R[r2].info);
}

////  Funções lógicas
void IEQ(FILE* entry, regs* R, int r1, int r2, int line){
    if(R[r1].info == R[r2].info)
        HOP(entry, line);
}

void ILT(FILE* entry, regs* R, int r1, int r2, int line){
    if(R[r1].info < R[r2].info)
        HOP(entry, line);
}

void limpeza(char s[4]){
    for (int i = 0; i < 4; i++){
        s[i] = ' ';
    }
    
}


int escolha(FILE* entry, FILE* exit, regs* R){
    char command[4];
    limpeza(command);
    fscanf(entry, "%s", command);
    if(!strcmp(command, "SET")){
        int reg, info;
        fscanf(entry, "%d %d", &reg, &info);
        return SET(R, reg, info);
    }
    if(!strcmp(command, "SIN")){
        int reg;
        fscanf(entry, "%d", &reg);
        return SIN(R, reg);
    }
    if(!strcmp(command, "HOP")){
        int line;
        fscanf(entry, "%d", &line);
        return HOP(entry, line);
    }
    if(!strcmp(command, "MEM")){
        int reg;
        fscanf(entry, "%d", &reg);
        return MEM(R, exit, reg);
    }
    if(!strcmp(command, "SUM")){
        int reg1, reg2;
        fscanf(entry, "%d %d", &reg1, &reg2);
        SUM(R, reg1, reg2);
        return 1;
    }
    if(!strcmp(command, "SUB")){
        int reg1, reg2;
        fscanf(entry, "%d %d", &reg1, &reg2);
        SUB(R, reg1, reg2);
        return 1;
    }
    if(!strcmp(command, "MOD")){
        int reg1, reg2;
        fscanf(entry, "%d %d", &reg1, &reg2);
        MOD(R, reg1, reg2);
        return 1;
    }
    if(!strcmp(command, "FRC")){
        int reg;
        fscanf(entry, "%d", &reg);
        FRC(R, reg);
        return 1;
    }
    if(!strcmp(command, "EXP")){
        int reg1, reg2;
        fscanf(entry, "%d %d", &reg1, &reg2);
        EXP(R, reg1, reg2);
        return 1;
    }
    if(!strcmp(command, "IEQ")){
        int reg1, reg2, line;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &line);
        IEQ(entry, R, reg1, reg2, line);
        return 1; 
    }
    if(!strcmp(command, "ILT")){
        int reg1, reg2, line;
        fscanf(entry, "%d %d %d", &reg1, &reg2, &line);
        ILT(entry, R, reg1, reg2, line);
        return 1;
    }
    return 0;
}

int main(){
    regs R[16];
    R[0].info = 0;
    R[1].info = 1;

    int saida = 1;

    FILE* entry = fopen("entrada.txt", "r");
    FILE* result = fopen("saida.txt", "w");

    while (saida == 1){
        saida = escolha(entry, result, R);
        linha_atual++;
    }

    fclose(entry);
    fclose(result);

    return 0;
}