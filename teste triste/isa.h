#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct REGS regs;

struct REGS{
    float info;
};

int SET(regs*, int, int);
int HOP(FILE*, int, char[26], int);
int MEM(regs* R, FILE*, int);
void SUM(regs*, int, int, int);
void SUB(regs*, int, int, int);
void MOD(regs*, int, int, int);
void EXP(regs*, int, int, int);
void IET(FILE*, regs*, int, int, int, char[26], int);
void ILT(FILE*, regs*, int, int, int, char[26], int);
void limpeza(char[3]);
int tamanhoArquivo(FILE* arq);
float binToFloat(char*);
int charToBin(FILE*);

#endif