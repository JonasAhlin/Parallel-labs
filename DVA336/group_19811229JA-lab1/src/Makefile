CC=gcc 
CFLAGS= -fopenmp
CLIBS= -pthread
	
	
all:  hellopt globalpt synchpt scalarpt hellomp globalmp privatemp criticalmp synchmp orderedmp sectionsmp scalarmp pipt matmulpt diningpt cliserpt pimp lump 
	
time.o: time.c timer.h
	$(CC) -c time.c
	
%pt: %pt.c time.o
	$(CC) $(CLIBS) -O3 -o $@ $@.c time.o
	
%mp: %mp.c time.o
	$(CC) $(CFLAGS) -O3 -o $@ $@.c time.o
	
clean:
	rm -f *mp *pt *.o

distclean: clean
	rm -f *~
