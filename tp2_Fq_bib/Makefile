CC = gcc
CFLAGS = -I . -g -Wall #-O3

.SUFFIXES: .c .o

PRGS = fp_poly_test

all:\
	$(PRGS)

fp_poly_test:\
	fp_poly_test.o fp_poly.o
	$(CC) fp_poly_test.o fp_poly.o -o $@

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
