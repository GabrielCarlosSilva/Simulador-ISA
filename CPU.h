#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct REGS regs;


typedef struct{
    int RAM;
    int Mem_Instrucao;
    char instrucao[100];
}Memoria;

struct REGS{
    double info;
};

typedef struct{
    regs R[16];
    int Contador_Programa;
}CPU;


int SET(regs*, int, float);
int HOP(int);
int MEMF(regs*, FILE*, int);
int MEMD(regs*, FILE*, int);

void SUM(regs* , int, int, int);
void SUB(regs* , int, int, int);
void MUL(regs* , int, int, int);
void DIV(regs* , int, int, int);
void MOD(regs* , int, int, int);
void EXP(regs* , int, int, int);

int IET(regs*, int, int, int, int);
int ILT(regs*, int, int, int, int);

void CPY(regs*, int, int);

int GastoMemoria(char*);
int EnviaInstrucao(int, char*);
int analise_opcode(char* );

int escolha(regs*, int, FILE*);

int EnderecoToInt(char[4]);
void limpeza(char[4]);
int tamanhoArquivo(FILE*);

#endif