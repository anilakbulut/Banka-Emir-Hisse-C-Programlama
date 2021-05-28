derlecalistir:program calistir

program:main.o read.o struct_banka.o struct_emirler.o struct_hisseler.o struct_portfoy.o
	gcc ./lib/main.o ./lib/read.o ./lib/struct_banka.o ./lib/struct_emirler.o ./lib/struct_hisseler.o ./lib/struct_portfoy.o -o ./bin/program
main.o:
	gcc -I "./include" -c ./src/main.c -o ./lib/main.o
read.o:
	gcc -I "./include" -c ./src/read.c -o ./lib/read.o
struct_banka.o:
	gcc -I "./include" -c ./src/struct_banka.c -o ./lib/struct_banka.o
struct_emirler.o:
	gcc -I "./include" -c ./src/struct_emirler.c -o ./lib/struct_emirler.o
struct_hisseler.o:
	gcc -I "./include" -c ./src/struct_hisseler.c -o ./lib/struct_hisseler.o
struct_portfoy.o:
	gcc -I "./include" -c ./src/struct_portfoy.c -o ./lib/struct_portfoy.o
calistir:
	./bin/program.exe