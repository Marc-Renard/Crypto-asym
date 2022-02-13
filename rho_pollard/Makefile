CC = gcc
CFLAGS = -I . -g -Wall #-O3

.SUFFIXES: .c .o

PRGS = rho_test

all:\
	$(PRGS)

rho_test:\
	rho_test.o rho.o
	$(CC) rho_test.o rho.o -o $@

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
