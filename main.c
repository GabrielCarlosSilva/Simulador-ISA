#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    int info;
}registradores;

int ACC = 0;                // Memoria acessivel
int linha_atual = 0;        // Posição atual do código
int max_linhas = 0;         // Tamanho máximo do arquivo

//// Funções administrativas
// Salva inforação recebida em um registrador (SET)
int SET(registradores* R, int reg, int info){
    if((reg > 15) && (reg < 1))
        return 0;
    R[reg].info = info;
    return 1;
}
// Salva a informação armazenada em ACC para o registrador (SET IN)
int SIN(registradores* R, int reg){
    if((reg > 15) && (reg < 1))
        return 0;
    R[reg].info = ACC;
    ACC = 0;
    return 1;
}
// Pula para linha recebida (HOP)
int HOP(int line){
    if(line > max_linhas)
        return 0;
    linha_atual = line - 1;
    return 1;
}

//// Funções matemáticas
//  Soma simples, resultado em ACC (SUM)
void SUM(registradores* R, int r1, int r2){
    ACC = R[r1].info + R[r2].info;
}
//  Subtração simples, resultado em ACC (SUBTRACTION)
void SUB(registradores* R, int r1, int r2){
    ACC = R[r1].info - R[r2].info;
}
//  Modulo, resultado em ACC 
void MOD(registradores* R, int r1, int r2){
    ACC = R[r1].info % R[r2].info; 
}
//  Calcula o fatorial da entrada, resultado em ACC
void FRC(registradores* R, int rx){
    ACC = frac(R[rx].info);
}
//  Função auxiliar de FRC, resultado em ACC
int frac(int n){
    if(n == 1)
        return 1;
    return n * frac(n - 1);
}
//  Exponecial, resultado em ACC
int EXP(registradores* R, int r1, int r2){
    ACC = (int) pow(R[r1].info, R[r2].info);
}

//// Funções lógicas
// Se igual, pule para linha X (Is Equal)
int IEQ(registradores* R, int r1, int r2, int line){
    if(R[r1].info != R[r2].info)
        return 0;
    linha_atual = line - 1;
    return 1;
}
// Se menor, pule para linha X (Is Less Then)
int ILT(registradores* R, int r1, int r2, int line){
    if(R[r1].info < R[r2].info){
        linha_atual = line - 1;
        return 1;
    }
    return 0;
}


int main(){
    registradores R[16]; 
    R[0].info = 0;
    R[1].info = 1;

    int saida = 0;

    while(saida != 1){
        /*
        Função que decide qual op executar
        Função que verifica se já pode parar (saida = 1)
        */
        linha_atual++;
    }


    return 0;
}