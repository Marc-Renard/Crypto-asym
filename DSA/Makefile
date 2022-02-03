CC = gcc
CFLAGS = -I . -g -Wall #-O3
LDFLAGS = -lgmp

.SUFFIXES: .c .o

PRGS = dsa_test

all:\
	$(PRGS)

dsa_test:\
	dsa_test.o dsa.o
	$(CC) dsa_test.o dsa.o -o $@ $(LDFLAGS)

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
