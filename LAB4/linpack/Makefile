CCOMP = gcc

LOADER = gcc

OPT = -DSP -DROLL -O3

LIB = -lm -lrt

linpack: linpackc.o  
	$(LOADER) $(OPT) linpackc.o -o linpack $(LIB)

linpackc.o: linpackc.c
	$(CCOMP) -c $(OPT) linpackc.c

clean:
	rm -f *.o
