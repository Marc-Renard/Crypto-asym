CC = gcc
CFLAGS = -I . -g -Wall -O3

.SUFFIXES: .c .o

PRGS = rsa_test

all:\
	$(PRGS)

rsa_test:\
	rsa_test.o rsa.o
	$(CC) rsa_test.o rsa.o -o $@

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
