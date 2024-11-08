prog:fonction_bassilekin.c fonction_bassilekin.h main_bassilekin.c
	gcc -o prog fonction_bassilekin.c main_bassilekin.c -g -O0 -lm -lpthread -fopenmp 

run:prog
	./prog 

run_valgrind:prog
	valgrind  --tool=memcheck --leak-check=yes --leak-resolution=low --show-reachable=yes  ./prog
	
clean:
	rm  prog

profile:
	gcc -Wall -pg fonction_bassilekin.c main_bassilekin.c -lm -lpthread -o prog