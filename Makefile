TARGET=trab2
CC = gcc
CFLAGS = -Wall -Wextra -g

# Regra padrão
all: trab2

# Regra para o programa principal
trab2: client.o PQ.o algoritmo.o lista.o
	$(CC) $(CFLAGS) -o trab2 client.o PQ.o algoritmo.o lista.o

# Regra para o arquivo client.c
client.o: client.c item.h PQ.h algoritmo.h lista.h
	$(CC) $(CFLAGS) -c client.c

# Regra para o arquivo funcoes.c
PQ.o: PQ.c PQ.h item.h 
	$(CC) $(CFLAGS) -c PQ.c 

algoritmo.o: algoritmo.c algoritmo.h item.h
	$(CC) $(CFLAGS) -c algoritmo.c 
	
lista.o: lista.c lista.h item.h
	$(CC) $(CFLAGS) -c lista.c 

# Regra para limpar os arquivos objeto e o programa
clean:
	rm -f *.o trab2