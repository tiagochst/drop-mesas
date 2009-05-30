CC = gcc
CFLAGS = -ansi -W -Wall -g -ggdb
LIBS = -lm

OBJS = main.o capturas.o consultas.o especies.o funcoes.o individuos.o lista_buraco_var.o lista_buraco_fixo.o lista_inv.o indice.o indice_sec.o conjunto.o data.o lab3.o
ATB = dados_especies.txt dados_individuos.txt dados_capturas.txt
FILES = individuos.txt especies.txt capturas.dat inv_primario.dat inv_secundario.dat ind_prim_especie.dat ind_prim_individuo.dat ind_sec_individuo.dat ind_sec_captura.dat
EXEC = run

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(EXEC)

run: all
	./$(EXEC) $(ATB)

load: all
	./$(EXEC) < input_01
	./$(EXEC) < input_02
	./$(EXEC) < input_03

$(OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(EXEC) *~

reset: clean
	rm -f $(FILES)
