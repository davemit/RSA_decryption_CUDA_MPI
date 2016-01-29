CFLAGS = -g -Wall -Wstrict-prototypes 
NFLAGS = -arch sm_35 -O 
PROGS = finalrsa pollardCuda pollardMpi
OBJECT1 = pollardSerial.o finalrsa.o
#OBJECT2 = pollardCuda.o
LDFLAGS = -lm 
CC = gcc 
NCC =nvcc
MCC=mpicc

all: $(PROGS) 

pollardSerial.o: pollardSerial.c pollardSerial.h
	$(CC) -c pollardSerial.c

finalrsa.o: finalrsa.c
	$(CC)  -c finalrsa.c

pollardCuda: pollardCuda.cu pollardCuda.h
	$(NCC) $(NFLAGS) pollardCuda.cu -o pollardCuda.out

finalrsa: $(OBJECT1)
	$(CC) $(LDFLAGS) $(OBJECT1) $(LD2) -o finalrsa.out

pollardMpi: pollardMpi.c
	$(MCC) pollardMpi.c -o pollardMpi.out

clean: 
	rm -f $(PROGS) *.o  *.out
