all: main.o isa.o
	@gcc main.o isa.o -o exe
main.o: main.c
	@gcc main.c -c -Wall
isa.o: isa.c
	@gcc isa.c -c -Wall
run:
	@./exe
