SRC = src
OBJ = obj
INCLUDE = include

CC = gcc
CFLAGS = -Wall -g -lm -I $(INCLUDE) -DDEBUG -lrt

.PHONY: dir

all: dir invmat

clean:
	-rm invmat
	-rm -r $(OBJ)

# ----

invmat: $(OBJ)/encontraMatrizInversa.o $(OBJ)/matriz.o
		$(CC) -o invmat $(OBJ)/*.o $(CFLAGS) 
# ----

$(OBJ)/encontraMatrizInversa.o: $(SRC)/encontraMatrizInversa.c $(INCLUDE)/matriz.h
		$(CC) -c $(SRC)/encontraMatrizInversa.c -o $(OBJ)/encontraMatrizInversa.o $(CFLAGS)

$(OBJ)/matriz.o: $(SRC)/matriz.c
		$(CC) -c $(SRC)/matriz.c -o $(OBJ)/matriz.o $(CFLAGS)

dir:
	mkdir -p $(OBJ)
		
