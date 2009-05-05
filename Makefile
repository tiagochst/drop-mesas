CC = gcc
CFLAGS = -ansi -W -Wall -pedantic -g -ggdb
LIBS = -lm

OBJS = main.o capturas.o consultas.o especies.o funcoes.o individuos.o listas.o lista_inv.o conjunto.o
FILES = individuos.txt especies.txt capturas.dat inv_primario.dat inv_secundario.dat
EXEC = run

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(EXEC)

run: all
	./$(EXEC)

$(OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(EXEC) *~

reset: clean
	rm -f $(FILES)
