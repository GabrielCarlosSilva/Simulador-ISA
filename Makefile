all: Unit_Control.o CPU.o ALU.o memoria.o 
	@gcc Unit_Control.o CPU.o ALU.o memoria.o -o exe -lm
CPU.o: CPU.c
	@gcc CPU.c -c -Wall
memoria.o: memoria.c
	@gcc memoria.c -c -Wall
ALU.o: ALU.c
	@gcc ALU.c -c -Wall
Unit_Control.o: Unit_Control.c
	@gcc Unit_Control.c -c -Wall
run:
	@./exe
