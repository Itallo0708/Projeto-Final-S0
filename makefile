# Nome do compilador
CC=gcc

# Flags de compilação, no caso, -pthread para linkar a biblioteca de threads
CFLAGS=-pthread -Wall

# Nome do arquivo executável
TARGET=coleta_recursos

# Nome do arquivo fonte
SRC=coleta_recursos.c

# Regra principal: o que fazer quando 'make' é executado
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Regra para limpar os arquivos gerados
clean:
	rm -f $(TARGET)
