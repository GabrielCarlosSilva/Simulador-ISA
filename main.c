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

    char command[3];


    int reg, reg1, reg2, reg3, line;
    float info;

    printf("%d\n\n", max_linhas);
    while (linha_atual <= max_linhas){
        printf("linha %d: ", linha_atual);
        limpeza(command);
        fscanf(entry, "%s", command);
            if(!strcmp(command, "ST")){
                reg = (int) charToBin(entry);
                info = charToBin(entry);
                if(reg > 15 || reg < 2)
                    break;  
                R[reg].info = info;
                printf("SET resgistrador %d %.1f\n", reg, info);
            }

            if(!strcmp(command, "HP")){
                line = (int) charToBin(entry);
                if(line < 0 || line > max_linhas)
                    break;
                HP(entry, line, Nome_arquivo);
                linha_atual = line - 1;
                printf("Linha atual:  %d", line);
            }

            if(!strcmp(command, "MM")){
                reg = (int) charToBin(entry);
                MM(result, R[reg].info);
                printf("Memória armazenada %d  '%.1f'\n", reg, R[reg].info);
            }

            if(!strcmp(command, "SM")){
                reg1 = (int) charToBin(entry);
                reg2 = (int) charToBin(entry);
                reg3 = (int) charToBin(entry);
                if(checker(reg1, reg2, reg3))
                    break;
                R[reg3].info = SM(R[reg1].info, R[reg2].info);
                printf("SOMA R%d + R%d\n", reg1, reg2);
            }
    
            if(!strcmp(command, "SB")){
                reg1 = (int) charToBin(entry);
                reg2 = (int) charToBin(entry);
                reg3 = (int) charToBin(entry);
                if(checker(reg1, reg2, reg3))
                    break;
                R[reg3].info = SB(R[reg1].info, R[reg2].info);
                printf("SUBTRAÇÂO: R%d - R%d\n", reg1, reg2);
            }
    
            if(!strcmp(command, "MD")){
                reg1 = (int) charToBin(entry);
                reg2 = (int) charToBin(entry);
                reg3 = (int) charToBin(entry);
                if(checker(reg1, reg2, reg3))
                    break;
                R[reg3].info = MD(R[reg1].info, R[reg2].info);
                printf("MODULO: R%d %% R%d %.1f\n", reg1, reg2, R[reg3].info);
            }
    
            if(!strcmp(command, "EX")){
                reg1 = (int) charToBin(entry);
                reg2 = (int) charToBin(entry);
                reg3 = (int) charToBin(entry);
                if(checker(reg1, reg2, reg3))
                    break;
                R[reg3].info = EX(R[reg1].info, R[reg2].info);
                printf("EXPONENCIAÇÃO: R%d ^ R%d\n", reg1, reg2);
            }

            if(!strcmp(command, "IE")){
                reg1 = (int) charToBin(entry);
                reg2 = (int) charToBin(entry);
                line = (int) charToBin(entry); 
                if(checker(reg1, reg2, 5) || (line > max_linhas || line < 0))
                    break;
                if(R[reg1].info == R[reg2].info){
                    HP(entry, line, Nome_arquivo);
                    linha_atual = line - 1;
                }
                printf("Comparação...\n");
            }

            if(!strcmp(command, "IL")){
                reg1 = (int) charToBin(entry);
                reg2 = (int) charToBin(entry);
                line = (int) charToBin(entry);
                if(checker(reg1, reg2, 5) || (line > max_linhas || line < 0))
                    break;
                if(R[reg1].info < R[reg2].info){
                    HP(entry, line, Nome_arquivo);
                    linha_atual = line - 1;
                }
                printf("Comparação... %d %d\n", reg1, reg2);
            }

        linha_atual++;
    }

    fclose(entry);
    fclose(result);
    return 0;
}