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

int ST(regs*, int, int);
int HP(FILE*, int, char[26], int);
int MM(regs* R, FILE*, int);
void SM(regs*, int, int, int);
void SB(regs*, int, int, int);
void MD(regs*, int, int, int);
void EX(regs*, int, int, int);
void IE(FILE*, regs*, int, int, int, char[26], int);
void IL(FILE*, regs*, int, int, int, char[26], int);
void limpeza(char[3]);
int tamanhoArquivo(FILE* arq);
float binToFloat(char*);
int charToBin(FILE*);

#endif