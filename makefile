CC = rcc
CFLAGS =

OBJS =	compare.o interpret.o logical.o math.o mem.o poppush.o retstack.o\
	stack.o stackops.o terminal.o vocabulary.o

VOCOBJS = compare.o interpret.o logical.o math.o mem.o poppush.o retstack.o\
	  stackops.o terminal.o tstvoc.o

stack: $(OBJS)
	$(CC) -o stack $(CFLAGS) $(OBJS) stack.o

tstvoc: $(VOCOBJS)
	$(CC) -o tstvoc $(CFLAGS) $(VOCOBJS)

clean:
	/bin/rm -f *.o *.b core

$(OBJS): extern.h global.h stack.h vocabulary.h
