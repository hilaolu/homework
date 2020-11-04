SOURCE=.
OBJ_DIR=$(SOURCE)/obj
BIN_DIR=$(SOURCE)/bin
CC=gcc
CFLAG=-Wall -c
LFLAG=-Wall
TARGET=$(patsubst %.c, %, $(wildcard *.c))
OBJECT=$(patsubst %.c, $(OBJ_DIR)/%.o, $(wildcard *.c))
all:exp

exp:$(TARGET)

$(TARGET):%:$(OBJ_DIR)/%.o
	$(CC) $(LFLAG) $^ -o $(BIN_DIR)/$@.exe

$(OBJECT):$(OBJ_DIR)/%.o:%.c
	$(CC) $(CFLAG) $^ -o $@
