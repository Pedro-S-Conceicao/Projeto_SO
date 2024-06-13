# Makefile Projeto da disciplina de Sistemas operacionais 
#
DEP = Main_projeto.c tarefas.c 


Teste01:    projetoSO run01 clean

Teste02:	projetoSO run02 clean

Teste03:    projetoSO run03 clean

Teste04:    projetoSO run04 clean

Teste05:    projetoSO run05 clean

Teste06:    projetoSO run06 clean
	
projetoSO:
	@gcc -Wall -Wextra $(DEP) -o $@

run01:
	@./projetoSO 1 100 arq100A.dat arq100B.dat arq100C.dat arq100D.dat arq100E.dat

run02:
	@./projetoSO 1 1000 arq1000A.dat arq1000B.dat arq1000C.dat arq1000D.dat arq1000E.dat

run03:
	@./projetoSO 2 100 arq100A.dat arq100B.dat arq100C.dat arq100D.dat arq100E.dat

run04:
	@./projetoSO 2 1000 arq1000A.dat arq1000B.dat arq1000C.dat arq1000D.dat arq1000E.dat

run05:
	@./projetoSO 4 100 arq100A.dat arq100B.dat arq100C.dat arq100D.dat arq100E.dat

run06:
	@./projetoSO 4 1000 arq1000A.dat arq1000B.dat arq1000C.dat arq1000D.dat arq1000E.dat

clean:
	@rm projetoSO