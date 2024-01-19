#list of files 
C_SRCS = Pipe. Child.c 
C_OBJS = Pipe.o Child.o 

#C_HEADERS 
OBJS = ${C_OBJS} 
EXE1 = Pipe 
EXE2 = Child 

#compiler and loader commands and flags 
GCC = gcc 
GCC_FLAGS = -std=c11 -g -Wall -c -I. 
LD_FLAGS = -std=c11 -g -Wall -I. 

#compile .c files to .o files 
.c.o: 
	$(GCC) $(GCC_FLAGS) $< 

#target is the executable 
all: Pipe Child 
fork: Pipe.o 
	$(GCC) $(LD_FLAGS) Pipe.o -o $(EXE1) 
ChildTask: Child.o 
	$(GCC) $(LD_FLAGS) Child.o -o $(EXE2) 
	
#recomplile c objects if headers change 
$(C_OBJS): ${C_HEADERS} 

#clean up directory
clean: 
	rm -f *.o *- $(EXE1) $(EXE2) 
package: 
	zip -r Blocker-Ryan.zip Pipe.c Child.c Makefile README.txt