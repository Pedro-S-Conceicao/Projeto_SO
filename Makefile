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

Compilar:	$(BIN)projetoSO.exe

Teste01:    run01 

Teste02:    run02 

Teste03:    run03 

Teste04:    run04 

Teste05:    run05 

Teste06:    run06 
	
$(BIN)projetoSO.exe: $(OBJS)
	@$(CC) -o $@ $^

$(BUILD)%.o: $(SRC)%.c
	@$(CC) $(CFLAGS) -c -o $@ $^

run01:
	@$(BIN)projetoSO.exe $(1THRD) $(ORD100) arq100A.dat arq100B.dat arq100C.dat arq100D.dat arq100E.dat

run02:
	@$(BIN)projetoSO.exe $(2THRD) $(ORD100) arq100A.dat arq100B.dat arq100C.dat arq100D.dat arq100E.dat

run03:
	@$(BIN)projetoSO.exe $(4THRD) $(ORD100) arq100A.dat arq100B.dat arq100C.dat arq100D.dat arq100E.dat

run04:
	@$(BIN)projetoSO.exe $(1THRD) $(ORD1000) arq1000A.dat arq1000B.dat arq1000C.dat arq1000D.dat arq1000E.dat
	
run05:
	@$(BIN)projetoSO.exe $(2THRD) $(ORD1000) arq1000A.dat arq1000B.dat arq1000C.dat arq1000D.dat arq1000E.dat

run06:
	@$(BIN)projetoSO.exe $(4THRD) $(ORD1000) arq1000A.dat arq1000B.dat arq1000C.dat arq1000D.dat arq1000E.dat

clean:
	@rm -rf $(BIN)*.exe $(BUILD)*.o