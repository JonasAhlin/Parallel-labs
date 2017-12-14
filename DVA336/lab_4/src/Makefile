MPICC= mpicc 
CC= gcc 

PRGS=hello maximum matmul communicators

all: $(PRGS)

time.o: time.c 
	$(CC) -O3 -c -o time.o time.c
	
%: %.c time.o
	$(MPICC) -o $@ $@.c time.o
	
clean: 
	rm -f *.o 
	rm -f $(PRGS) 
	
distclean: clean
	rm -f *~ 
