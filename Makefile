all: fancy_output.o utils.o main.o 
	gcc main.o fancy_output.o utils.o -o 2D_integral_solver
main.o: main.c utils.h fancy_output.h
	gcc -g -Wall -Wextra -Werror -pedantic -std=c99 -c main.c
utils.o: utils.c utils.h fancy_output.h
	gcc -g -Wall -Wextra -Werror -pedantic -std=c99 -c utils.c
fancy_output.o: fancy_output.c fancy_output.h
	gcc -g -Wall -Wextra -Werror -pedantic -std=c99 -c fancy_output.c

clean:
	rm -f *.o 2D_integral_solver grid.txt