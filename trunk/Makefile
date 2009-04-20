CC = gcc
CFLAGS = -ansi -W -Wall -pedantic -g -ggdb
LIBS = -lm

OBJS = main.o capturas.o consultas.o especies.o funcoes.o individuos.o listas.o
FILES = individuos.txt especies.txt capturas.dat
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
