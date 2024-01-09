#include "isa.h"

int checker(int r1, int r2, int r3){
    if(r1 > 15 || r2 > 15 || r3 > 15)
        return 1;
    if(r1 < 0 || r2 < 0 || r3 < 0)
        return 1;
    return 0;
}

int main(){
    char Nome_arquivo[26];
    regs R[16];
    R[0].info = 0;
    R[1].info = 1;

    int linha_atual = 1;

    printf("Nome do arquivo de entrada: ");
    scanf("%s", Nome_arquivo);

    FILE* entry = fopen(Nome_arquivo, "r");
    int max_linhas = tamanhoArquivo(entry);
    entry = fopen(Nome_arquivo, "r");
    FILE* result = fopen("saida.txt", "w");

    char command[4];


    int reg, reg1, reg2, reg3, line;
    float info;

    printf("%d\n\n", max_linhas);
    while (linha_atual <= max_linhas){
        limpeza(command);
        fscanf(entry, "%s", command);
        printf("linha %d %s: ", linha_atual, command);
            if(!strcmp(command, "SET")){
                fscanf(entry, "%d %f", &reg, &info);
                if(reg > 15 || reg < 2)
                    break;  
                R[reg].info = info;
                printf("SET resgistrador%d (valor: %.1f)\n", reg, info);
            }

            if(!strcmp(command, "HOP")){
                fscanf(entry, "%d", &line);
                if(line < 0 || line > max_linhas)
                    break;
                HOP(entry, line, Nome_arquivo);
                linha_atual = line - 1;
                printf("Linha atual:  %d\n", line);
            }

            if(!strcmp(command, "MEM")){
                fscanf(entry, "%d", &reg);
                MEM(result, R[reg].info);
                printf("Memória armazenada %d (valor: %.1f)\n", reg, R[reg].info);
            }

            if(!strcmp(command, "SUM")){
                fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
                if(checker(reg1, reg2, reg3))
                    break;
                R[reg3].info = SUM(R[reg1].info, R[reg2].info);
                printf("SOMA R%d + R%d (%.1f)\n", reg1, reg2, R[reg3].info);
            }
    
            if(!strcmp(command, "SUB")){
                fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
                if(checker(reg1, reg2, reg3))
                    break;
                R[reg3].info = SUB(R[reg1].info, R[reg2].info);
                printf("SUBTRAÇÂO: R%d - R%d (%.1f)\n", reg1, reg2, R[reg].info);
            }
            if(!strcmp(command, "DIV")){
                fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
                if(checker(reg1, reg2, reg3))
                    break;
                R[reg3].info = DIV(R[reg1].info, R[reg2].info);
                printf("SUBTRAÇÂO: R%d - R%d (%.1f)\n", reg1, reg2, R[reg].info);
            }
            if(!strcmp(command, "MUL")){
                fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
                if(checker(reg1, reg2, reg3))
                    break;
                R[reg3].info = MUL(R[reg1].info, R[reg2].info);
                printf("SUBTRAÇÂO: R%d - R%d (%.1f)\n", reg1, reg2, R[reg].info);
            }    
            if(!strcmp(command, "MOD")){
                fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
                if(checker(reg1, reg2, reg3))
                    break;
                R[reg3].info = MOD(R[reg1].info, R[reg2].info);
                printf("MODULO: R%d %% R%d (%.1f)\n", reg1, reg2, R[reg3].info);
            }
    
            if(!strcmp(command, "EXP")){
                fscanf(entry, "%d %d %d", &reg1, &reg2, &reg3);
                if(checker(reg1, reg2, reg3))
                    break;
                R[reg3].info = EXP(R[reg1].info, R[reg2].info);
                printf("EXPONENCIAÇÃO: R%d ^ R%d (%.1f)\n", reg1, reg2, R[reg3].info);
            }

            if(!strcmp(command, "IET")){
                fscanf(entry, "%d %d %d", &reg1, &reg2, &line);
                if(checker(reg1, reg2, 5) || (line > max_linhas || line < 0))
                    break;
                printf("Comparação...\n");
                if(R[reg1].info == R[reg2].info){
                    if(line < 0 || line > max_linhas)
                        break;  
                    printf("Pulando para linha %d\n", line);
                    HOP(entry, line, Nome_arquivo);
                    linha_atual = line - 1;
                }
            }

            if(!strcmp(command, "ILT")){
                fscanf(entry, "%d %d %d", &reg1, &reg2, &line);
                if(checker(reg1, reg2, 5) || (line > max_linhas || line < 0))
                    break;
                printf("Comparação... %d %d\n", reg1, reg2);
                if(R[reg1].info < R[reg2].info){
                    if(line < 0 || line > max_linhas)
                        break;
                    printf("Pulando para linha %d\n", line);
                    HOP(entry, line, Nome_arquivo);
                    linha_atual = line - 1;
                }
            }

        linha_atual++;
    }

    fclose(entry);
    fclose(result);
    return 0;
}