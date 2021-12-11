#makefile for photomosaic program
#made by Leonardo da Silva Camargo
#GRR 20203903

CFLAGS = -Wall -std=gnu99
LDLIBS = -lm

objs = main.o tiles.o list.o ppm.o

all: mosaico

mosaico: $(objs)
		cc -o mosaico $(objs) $(LDLIBS)
	
main.o:	main.c 
	cc -c main.c $(CFLAGS) $(LDLIBS)
fotomosaico.o: tiles.c
	cc -c tiles.c $(CFLAGS) $(LDLIBS)	
list.o: list.c
	cc -c list.c $(CFLAGS) $(LDLIBS)
ppm.o: ppm.c
	cc -c ppm.c $(CFLAGS) $(LDLIBS)	
clean:
	-rm -f *.o *~ 
	
purge: clean
	-rm -f mosaico
