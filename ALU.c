#include <stdio.h>
#include <math.h>
#include "CPU.h"


//// Funções administrativas
//  Salva a informação recibida em um registrador cuja posição foi recebida (SET)
int SET(regs* R, int reg, float info){
    if(reg > 15 || reg <= 1)
        return 0;
    R[reg].info = info;
    return 1;
}

//  Pula para a linha recebida (HOP)
int HOP(int line){
    if(line < 0)
        return 0;
    return line;
}

//  Guarda a informação do registrador na memoria (MEMORY)
int MEM(regs* R, FILE* exit, int reg){
    if(reg > 15 || reg <= 1)
        return 0;
    fprintf(exit, "%lf \n", R[reg].info);
    return 1;
}

//// Funções matemáticas
// Soma simples, resultado em r3 (r1 + r2 = r3)
void SUM(regs* R, int r1, int r2, int r3){
    R[r3].info = R[r1].info + R[r2].info;
}

//  Subtração simples, resultado em r3 (r1 - r2 = r3)
void SUB(regs* R, int r1, int r2, int r3){
    R[r3].info = R[r1].info - R[r2].info;
}

void MUL(regs* R, int r1, int r2, int r3){
    R[r3].info = R[r1].info * R[r2].info;
}

void DIV(regs* R, int r1, int r2, int r3){
    R[r3].info = R[r1].info / R[r2].info;
}

//  Modulo simples, resultado em r3 (r1 % r2 = r3)
void MOD(regs* R, int r1, int r2, int r3){
    R[r3].info = (int) R[r1].info % (int) R[r2].info;
}

//  Exponeciação simples, resultado em r3 (r²)
void EXP(regs* R, int r1, int r2, int r3){
    R[r3].info = pow(R[r1].info, R[r2].info);
}

////  Funções lógicas
//  Verifica igualdade, caso positivo, pule para linha recebida (r1 == r2 ? line)
int IET(regs* R, int r1, int r2, int line,int PC){
    if(R[r1].info == R[r2].info){
        return HOP(line)-1;
    }
    else{
        return PC;
    }
}

//  Verifica se r1 é menor que r2, caso positivo, pule para linha recebida (r1 < r2 ? line)
int ILT(regs* R, int r1, int r2, int line, int PC){
    if(R[r1].info < R[r2].info){
        return HOP(line)-1;
    }
    else{
        return PC;
    }
}