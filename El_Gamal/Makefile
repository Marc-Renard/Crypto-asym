CC = gcc
CFLAGS = -I ../Fq_lib -g -Wall #-O3

.SUFFIXES: .c .o

PRGS = el_gamal_test

all:\
	$(PRGS)

el_gamal_test:\
	el_gamal_test.o el_gamal.o ../Fq_lib/fp_poly.o
	$(CC) el_gamal_test.o el_gamal.o ../Fq_lib/fp_poly.o -o $@

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
