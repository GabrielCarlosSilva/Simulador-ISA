int escolha(CPU cpu, FILE* exit){
    char regc[4];
    limpeza(cpu.controle.opCode);
    limpeza(regc);
    FILE* entry = fopen("instrucao.txt", "r");
    fscanf(entry, "%s", cpu.controle.opCode);
    if(!strcmp(cpu.controle.opCode, "SET")){

        fscanf(entry, "%s", regc);
        cpu.controle.reg[0]=EnderecoToInt(regc);
        fscanf(entry, "%f", &cpu.controle.info);
        fclose(entry);
        SET(cpu.R, cpu.controle.reg[0], cpu.controle.info);
    }
    if(!strcmp(cpu.controle.opCode, "HOP")){

        fscanf(entry, "%d", &cpu.controle.line);
        fclose(entry);
        return HOP(cpu.controle.line) -1;
    }
    if(!strcmp(cpu.controle.opCode, "MEMF")){

        fscanf(entry, "%s", regc);
        cpu.controle.reg[0]=EnderecoToInt(regc);
        fclose(entry);
        MEMF(cpu.R, exit, cpu.controle.reg[0]);
    }
    if(!strcmp(cpu.controle.opCode, "MEMD")){

        fscanf(entry, "%s", regc);
        cpu.controle.reg[0]=EnderecoToInt(regc);
        fclose(entry);
        MEMD(cpu.R, exit, cpu.controle.reg[0]);
    }
    if(!strcmp(cpu.controle.opCode, "SUM")){

        for(int i=0; i<3; i++){
            fscanf(entry, "%s", regc);
            cpu.controle.reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        SUM(cpu.R, cpu.controle.reg[0], cpu.controle.reg[1], cpu.controle.reg[2]);
    }
    if(!strcmp(cpu.controle.opCode, "SUB")){

        for(int i=0; i<3; i++){
            fscanf(entry, "%s", regc);
            cpu.controle.reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        SUB(cpu.R, cpu.controle.reg[0], cpu.controle.reg[1], cpu.controle.reg[2]);

    }
    if(!strcmp(cpu.controle.opCode, "MUL")){

        for(int i=0; i<3; i++){
            fscanf(entry, "%s", regc);
            cpu.controle.reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        MUL(cpu.R, cpu.controle.reg[0], cpu.controle.reg[1], cpu.controle.reg[2]);
    }
    if(!strcmp(cpu.controle.opCode, "DIV")){

        for(int i=0; i<3; i++){
            fscanf(entry, "%s", regc);
            cpu.controle.reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        DIV(cpu.R, cpu.controle.reg[0], cpu.controle.reg[1], cpu.controle.reg[2]);

    }
    if(!strcmp(cpu.controle.opCode, "MOD")){

        for(int i=0; i<3; i++){
            fscanf(entry, "%s", regc);
            cpu.controle.reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        MOD(cpu.R, cpu.controle.reg[0], cpu.controle.reg[1], cpu.controle.reg[2]);
    }
    if(!strcmp(cpu.controle.opCode, "EXP")){

        for(int i=0; i<3; i++){
            fscanf(entry, "%s", regc);
            cpu.controle.reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        EXP(cpu.R, cpu.controle.reg[0], cpu.controle.reg[1], cpu.controle.reg[2]);
    }
    if(!strcmp(cpu.controle.opCode, "IET")){

        for(int i=0; i<2; i++){
            fscanf(entry, "%s", regc);
            cpu.controle.reg[i]= EnderecoToInt(regc);
        }
        fscanf(entry, "%d", &cpu.controle.line);
        fclose(entry);
        return IET(cpu.R, cpu.controle.reg[0], cpu.controle.reg[1], cpu.controle.line, cpu.Contador_Programa);
    }
    if(!strcmp(cpu.controle.opCode, "ILT")){

        for(int i=0; i<2; i++){
            fscanf(entry, "%s", regc);
            cpu.controle.reg[i]= EnderecoToInt(regc);
        }
        fscanf(entry, "%d", &cpu.controle.line);
        fclose(entry);
        return ILT(cpu.R, cpu.controle.reg[0], cpu.controle.reg[1], cpu.controle.line, cpu.Contador_Programa);
    }
    if(!strcmp(cpu.controle.opCode, "CPY")){

        for(int i=0; i<2; i++){
            fscanf(entry, "%s", regc);
            cpu.controle.reg[i]= EnderecoToInt(regc);
        }
        fclose(entry);
        CPY(cpu.R, cpu.controle.reg[0], cpu.controle.reg[1]);
    }
    return cpu.Contador_Programa;
}
