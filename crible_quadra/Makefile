CC = gcc
CFLAGS = -I . -g -Wall #-O3
LDFLAGS = -lgmp

.SUFFIXES: .c .o

PRGS = crible

all:\
	$(PRGS)

crible:\
	crible.o
	$(CC) crible.o -o $@ $(LDFLAGS)

.c.o: \
	$*.h $*.c
	@echo $*
	$(CC) $(CFLAGS) -c $< 

clean:
	find . -name '*.o' -exec rm -f {} ';'
	find . -name '*~' -exec rm -f {} ';'
	find . -name '#*#' -exec rm -f {} ';'
	find . -name '.#*' -exec rm -f {} ';'
	find . -name 'core' -exec rm -f {} ';'
	find . -name '*.core' -exec rm -f {} ';'
	-rm -rf $(PRGS)
