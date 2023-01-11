NOME_PROJETO=trab1

CC=gcc
CFLAGS=-c

# arquivos .c
C_SOURCE = cliente.c $(wildcard ./src/c/*.c)

# arquivos .h
H_SOURCE = $(wildcard ./src/h/*.h)

# arquivos objeto
OBJ = $(C_SOURCE:.c=.o)

all: $(NOME_PROJETO)

$(NOME_PROJETO): $(OBJ)
	@ $(CC) -o $@ $^

%.o: %.c %.h
	@ $(CC) $(CFLAGS) $<

cliente.o: cliente.c $(H_SOURCE)
	@ $(CC) $(CFLAGS) $<

run:
	./$(NOME_PROJETO) ./entrada.txt

clean:
	rm -rf ./cliente.o ./src/c/*.o $(NOME_PROJETO)