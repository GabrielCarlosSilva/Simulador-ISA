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

void SET(regs, float);
void HOP(FILE*, int, char[26]);
void MEM(FILE*, float);

float SUM(float, float);
float SUB(float, float);
float MOD(float, float);
float EXP(float, float);

int IET(float, float);
int ILT(float, float);

void limpeza(char[3]);
int tamanhoArquivo(FILE*);
float binToFloat(char*);
float charToBin(FILE*);

#endif