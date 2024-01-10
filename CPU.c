#include <stdio.h>
#include "CPU.h"

int main(){

    CPU cpu;
    char Nome_arquivo[26];
    cpu.R[0].info=0.0;
    cpu.R[1].info=1.0;

    int saida = 1;

    printf("Nome do arquivo de entrada: ");
    scanf("%s", Nome_arquivo);
    FILE* result = fopen("saida.txt", "w");

    if(!GastoMemoria(Nome_arquivo))
            return 0;

    cpu.Contador_Programa=1;
    while (saida == 1){
        saida=EnviaInstrucao(cpu.Contador_Programa, Nome_arquivo);
        if(!saida)
            return 0;
        cpu.Contador_Programa = escolha(cpu.R, cpu.Contador_Programa,result);
        cpu.Contador_Programa++;
        
    }

    getchar(); // Limpa o buffer de entrada
    fclose(result);
    return 0;
}