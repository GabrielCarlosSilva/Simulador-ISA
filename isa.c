#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct{
    int info;
}regs;

int ACC = 0;                // Memoria acessivel
int linha_atual = 0;        // Posição atual do código
int max_linhas = 0;         // Tamanho máximo do arquivo


//// Funções administrativas
//  Salva a informação recibida em um registrador cuja posição foi recebida (SET)
int ST(regs* R, int reg, int info){
    if(reg > 15 || reg <= 1)
        return 0;
    R[reg].info = info;
    return 1;
}

//  Salva a informação armazenada em ACC para o registrador da posição recebida (SET IN)
int SN(regs* R, int reg){
    if(reg > 15 || reg <= 1)
        return 0;
    R[reg].info = ACC;
    ACC = 0;
    return 1;  
}

//  Pula para a linha recebida (HOP)
int HP(FILE* entry, int line){
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

//  Guarda a informação do registrador na memoria (MEMORY)
int MM(regs* R, FILE* exit, int reg){
    if(reg > 15 || reg <= 1)
        return 0;
    fprintf(exit, "%d \n", R[reg].info);
    return 1;
}

//// Funções matemáticas
// Soma simples, resultado em ACC (r1 + r2)
void SM(regs* R, int r1, int r2){
    ACC = R[r1].info + R[r2].info;
}

//  Subtração simples, resultado em ACC (r1 - r2)
void SB(regs* R, int r1, int r2){
    ACC = R[r1].info - R[r2].info;
}

//  Modulo simples, resultado em ACC (r1 % r2)
void MD(regs* R, int r1, int r2){
    ACC = R[r1].info % R[r2].info;
}

//  Função auxiliar de FR
int fact(int n){
    if(n == 1)
        return 1;
    return n * fact(n - 1);
}

//  Função que realiza a fatoração, resultado em ACC (r1!)
void FR(regs* R, int rx){
    ACC = fact(R[rx].info);
}

//  Exponeciação simples, resultado em ACC (r²)
void EX(regs* R, int r1, int r2){
    ACC = pow(R[r1].info, R[r2].info);
}

////  Funções lógicas
//  Verifica igualdade, caso positivo, pule para linha recebida (r1 == r2 ? line)
void IE(FILE* entry, regs* R, int r1, int r2, int line){
    if(R[r1].info == R[r2].info)
        HP(entry, line);
}

//  Verifica se r1 é menor que r2, caso positivo, pule para linha recebida (r1 < r2 ? line)
void IL(FILE* entry, regs* R, int r1, int r2, int line){
    if(R[r1].info < R[r2].info)
        HP(entry, line);
}


//// Funções de emulação
// Limpa a string de comando
void limpeza(char s[3]){
    for (int i = 0; i < 4; i++){
        s[i] = ' ';
    }
    
}

// Calcula o número total de linhas no arquivo recebido
int tamanhoArquivo(FILE* arq){
    char linha[99];
    int linhas = 0;
    while (fgets(linha, 99, arq) != NULL){
        linhas++;
    }
    fclose(arq);
    return linhas + 1;
}

// Converte binário para inteiro
int binToInt(char *bin){
    int saida = 0;
    int potencia = 1;
    for (int i = 7; i >= 0; i--){
        if(bin[i] == '1')
            saida += potencia;
        potencia *= 2;
    }
    return saida;
}

// Converte charactere para binário
int charToBin(FILE* entry){
    char bin1[8], bin2[8];
    fscanf(entry, "%s", bin1);
    for(int i = 0; i < 8; i++)
        bin2[i] = '0';
    for (int i = 0; i < (int) strlen(bin1); i++)
        bin2[7 - i] = bin1[strlen(bin1) - i - 1];
    return binToInt(bin2);
}

//  Função que escolhe o op code apropriado
int escolha(FILE* entry, FILE* exit, regs* R){
    char command[3];
    limpeza(command);
    fscanf(entry, "%s", command);
    if(!strcmp(command, "ST")){
        int reg, info;
        reg = charToBin(entry);
        info = charToBin(entry);
        return ST(R, reg, info);
    }
    if(!strcmp(command, "SN")){
        int reg = charToBin(entry);
        return SN(R, reg);
    }
    if(!strcmp(command, "HP")){
        int line = charToBin(entry);
        return HP(entry, line);
    }
    if(!strcmp(command, "MM")){
        int reg = charToBin(entry);
        return MM(R, exit, reg);
    }
    if(!strcmp(command, "SM")){
        int reg1, reg2;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        SM(R, reg1, reg2);
        return 1;
    }
    if(!strcmp(command, "SB")){
        int reg1, reg2;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        SB(R, reg1, reg2);
        return 1;
    }
    if(!strcmp(command, "MD")){
        int reg1, reg2;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        MD(R, reg1, reg2);
        return 1;
    }
    if(!strcmp(command, "FR")){
        int reg = charToBin(entry);
        FR(R, reg);
        return 1;
    }
    if(!strcmp(command, "EX")){
        int reg1, reg2;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        EX(R, reg1, reg2);
        return 1;
    }
    if(!strcmp(command, "IE")){
        int reg1, reg2, line;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        line = charToBin(entry);
        IE(entry, R, reg1, reg2, line);
        return 1; 
    }
    if(!strcmp(command, "IL")){
        int reg1, reg2, line;
        reg1 = charToBin(entry);
        reg2 = charToBin(entry);
        line = charToBin(entry);
        IL(entry, R, reg1, reg2, line);
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
    max_linhas = tamanhoArquivo(entry);
    entry = fopen("entrada.txt", "r");
    FILE* result = fopen("saida.txt", "w");

    while (saida == 1){
        saida = escolha(entry, result, R);
        linha_atual++;
    }

    fclose(entry);
    fclose(result);

    return 0;
}