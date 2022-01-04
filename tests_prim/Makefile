CC = gcc
CFLAGS = -I . -g -Wall -O3

.SUFFIXES: .c .o

PRGS = test_prim_test

all:\
	$(PRGS)

test_prim_test:\
	test_prim_test.o test_prim.o
	$(CC) test_prim_test.o test_prim.o -o $@

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
