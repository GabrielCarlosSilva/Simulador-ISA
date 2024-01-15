#include <stdio.h>
#include <string.h>
#include "CPU.h"

#define SAIR_STRING "sair"

int main() {
    CPU cpu;
    char Nome_arquivo[26];
    cpu.R[0].info = 0.0;
    cpu.R[1].info = 1.0;

    int GastoM = 0;
    int saida = 1;

    do {
        saida = 1;
        printf("Nome do arquivo de entrada: ");
        scanf("%s", Nome_arquivo);

        if(!strcmp(Nome_arquivo, SAIR_STRING)){
            printf("Finalizando...\n");
            return 0;
        }
        if (!GastoMemoria(Nome_arquivo, &GastoM))
            return 0;


        FILE* result = fopen("saida.txt", "w");
        if (result == NULL) {
            perror("Erro ao abrir o arquivo de saída");
            return 0;
        }

        cpu.Contador_Programa = 1;
        while (saida == 1) {
            saida = EnviaInstrucao(cpu.Contador_Programa, Nome_arquivo);
            if (saida){
                cpu.Contador_Programa = escolha(cpu.R, cpu.Contador_Programa, result);
                cpu.Contador_Programa++;
            }
        }
        getchar();
        fclose(result);
        printf("Programa Finalizado! \nRAM utilazada: %d bits\n\n", GastoM);
        
    } while (strcmp(Nome_arquivo, SAIR_STRING));

    return 0;
}