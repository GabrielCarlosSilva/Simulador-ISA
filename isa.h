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

void ST(regs, float);
void HP(FILE*, int, char[26]);
void MM(FILE*, float);

float SM(float, float);
float SB(float, float);
float MD(float, float);
float EX(float, float);

int IE(float, float);
int IL(float, float);

void limpeza(char[3]);
int tamanhoArquivo(FILE*);
float binToFloat(char*);
float charToBin(FILE*);

#endif