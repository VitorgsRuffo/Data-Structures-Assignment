CC = gcc

flags = -std=c99 -fstack-protector-all -g -Wall -Werror

obj = main.o parameters.o geo.o qry.o svg.o

siguel: $(obj)
	$(CC) $(obj) -o siguel -lm

main.o: main.c main.h parameters.h geo.h qry.h svg.h
	$(CC) $(flags) -c main.c

parameters.o: parameters.c parameters.h
	$(CC) $(flags) -c parameters.c

geo.o: geo.c parameters.h svg.h
	$(CC) $(flags) -c geo.c

qry.o: qry.c parameters.h geo.h qry.h svg.h
	$(CC) $(flags) -c qry.c

svg.o: svg.c parameters.h
	$(CC) $(flags) -c svg.c 
	
clean: 
	rm $(obj) siguel