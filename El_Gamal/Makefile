CC = gcc
CFLAGS = -I . -g -Wall #-O3

.SUFFIXES: .c .o

PRGS = elgamal_test

all:\
	$(PRGS)


elgamal_test:\
	elgamal_test.o elgamal.o fp_poly.o
	$(CC) elgamal_test.o elgamal.o fp_poly.o -o $@

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
