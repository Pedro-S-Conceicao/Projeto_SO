# Makefile Projeto da disciplina de Sistemas operacionais 
#
BIN = ./bin/
BUILD = ./build/
SRC = ./src/
DATA_DIR = ./data/arqA.dat ./data/arqB.dat ./data/arqC.dat ./data/arqD.dat ./data/arqE.dat
OBJS = $(BUILD)Main_projeto.o $(BUILD)tasks.o $(BUILD)errorSigns.o
CC = gcc
CFLAGS = -O2 -Wall -Wextra
ORD100 = 100
ORD1000 = 1000
1THRD = 1
2THRD = 2
4THRD = 4

criarDir:
	@mkdir build bin

compilar:	$(BIN)projetoSO.exe

teste01:    run01 

teste02:    run02 

teste03:    run03 

teste04:    run04 

teste05:    run05 

teste06:    run06 
	
$(BIN)projetoSO.exe: $(OBJS)
	@$(CC) -o $@ $^

$(BUILD)%.o: $(SRC)%.c
	@$(CC) $(CFLAGS) -c -o $@ $^

run01:
	@$(BIN)projetoSO.exe $(1THRD) $(ORD100) $(DATA_DIR)

run02:
	@$(BIN)projetoSO.exe $(2THRD) $(ORD100) $(DATA_DIR)

run03:
	@$(BIN)projetoSO.exe $(4THRD) $(ORD100) $(DATA_DIR)

run04:
	@$(BIN)projetoSO.exe $(1THRD) $(ORD1000) $(DATA_DIR)
	
run05:
	@$(BIN)projetoSO.exe $(2THRD) $(ORD1000) $(DATA_DIR)

run06:
	@$(BIN)projetoSO.exe $(4THRD) $(ORD1000) $(DATA_DIR)

clean:
	@rm -rf $(BIN)*.exe $(BUILD)*.o

cleanDir:
	@rm -r $(BIN) $(BUILD)
