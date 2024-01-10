#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct REGS regs;

struct REGS{
    double info;
};

void SET(regs,  double);
void HOP(FILE*, int, char[26]);
void MEM(FILE*, double);

double SUM(double, double);
double SUB(double, double);
double MUL(double, double);
double DIV(double, double);
double MOD(double, double);
double EXP(double, double);

int IET(double, double);
int ILT(double, double);

void limpeza(char[3]);
int tamanhoArquivo(FILE*);

#endif