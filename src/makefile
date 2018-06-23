CC=gcc
CFLAGS=-Wall

EXEC=Puissance4

SRC=puissance4.c logger.c openFile.c expertSystem.c rule.c hypothesis.c ia.c menu.c enter.c
INC=$(SRC:.c=.h)

OBJ=$(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^

$(EXEC).o: $(INC)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf $(EXEC)
