CC = gcc
CFLAGS = -I . -g -Wall -lgmp #-O3

.SUFFIXES: .c .o

PRGS = rho_facto_test

all:\
	$(PRGS)

rho_facto_test:\
	rho_facto_test.o rho_facto.o
	$(CC) rho_facto_test.o rho_facto.o -o $@ -lgmp

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
