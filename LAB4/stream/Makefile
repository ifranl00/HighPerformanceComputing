# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
OPT =  -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -llapack -lm
LIB = -lm


stream_d: stream_d.o second_wall.o  
	$(LOADER) $(OPT) stream_d.o second_wall.o -o stream_d $(LIB)

stream_d.o: stream_d.c 
	$(CCOMP) -c $(OPT) stream_d.c

second_wall.o: second_wall.c
	$(CCOMP) -c $(OPT) second_wall.c

clean:
	rm -f *.o
