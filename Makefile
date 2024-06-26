# Makefile Projeto da disciplina de Sistemas operacionais 

BIN = ./bin/
BUILD = ./build/
SRC = ./src/
DATA_DIR = ./data/arqA.dat ./data/arqB.dat ./data/arqC.dat ./data/arqD.dat ./data/arqE.dat
OBJS = $(BUILD)main.o $(BUILD)tasks.o $(BUILD)errorSigns.o
CC = gcc
CFLAGS = -O2 -Wall -Wextra
ORD100 = 100
ORD1000 = 1000
1THRD = 1
2THRD = 2
4THRD = 4



compile:	dirCreate $(BIN)programa

dirCreate:
	@mkdir -p build bin
 
$(BIN)programa: $(OBJS)
	@$(CC) -o $@ $^

$(BUILD)%.o: $(SRC)%.c
	@$(CC) $(CFLAGS) -c -o $@ $^

run01:
	@$(BIN)programa $(1THRD) $(ORD100) $(DATA_DIR)

run02:
	@$(BIN)programa $(2THRD) $(ORD100) $(DATA_DIR)

run03:
	@$(BIN)programa $(4THRD) $(ORD100) $(DATA_DIR)

run04:
	@$(BIN)programa $(1THRD) $(ORD1000) $(DATA_DIR)
	
run05:
	@$(BIN)programa $(2THRD) $(ORD1000) $(DATA_DIR)

run06:
	@$(BIN)programa $(4THRD) $(ORD1000) $(DATA_DIR)

clean:
	@rm -rf $(BIN) $(BUILD)