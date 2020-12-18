exers.o: headers.h main.h users.h exers.h exers.c
	gcc -c exers.c
users.o: headers.h users.h exers.h users.c
	gcc -c users.c
main.o: headers.h users.h exers.h main.h main.c
	gcc -c main.c
mathtrain.out: exers.o users.o main.o
	gcc exers.o users.o main.o -o mathtrain.out

clear:
	rm -f mathtrain.out
	rm -f *.o
	

