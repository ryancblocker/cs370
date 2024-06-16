#list of files 
C_SRCS = coordinator.c checker.c 
C_OBJS = coordinator.o checker.o 

#C_HEADERS 
OBJS = ${C_OBJS} 
EXE1 = coordinator 
EXE2 = checker 

#compiler and loader commands and flags 
GCC = gcc 
GCC_FLAGS = -std=c11 -g -Wall -c -I. 
LD_FLAGS = -std=c11 -g -Wall -I. 

#compile .c files to .o files 
.c.o: 
	$(GCC) $(GCC_FLAGS) $< 

#target is the executable 
all: coordinator checker 
fork: coordinator.o 
	$(GCC) $(LD_FLAGS) coordinator.o -o $(EXE1) 
childTask: checker.o 
	$(GCC) $(LD_FLAGS) checker.o -o $(EXE2) 
	
#recomplile c objects if headers change 
$(C_OBJS): ${C_HEADERS} 

#clean up directory
clean: 
	rm -f *.o *- $(EXE1) $(EXE2) 
package: 
	zip -r Blocker-Ryan.zip coordinator.c checker.c Makefile README.txt