CC = gcc
CFLAGS = -ansi -W -Wall -g -ggdb
LIBS = -lm

OBJS = main.o
ATB =
FILES =
EXEC = run

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(EXEC)

run: all
	./$(EXEC) $(ATB)

$(OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f $(OBJS) $(EXEC) *~

reset: clean
	rm -f $(FILES)
