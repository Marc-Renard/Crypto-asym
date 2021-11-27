CC = gcc
CFLAGS = -I . -g -Wall -O3

.SUFFIXES: .c .o

PRGS = quadra_test

all:\
	$(PRGS)

quadra_test:\
	quadra_test.o quadra.o
	$(CC) quadra_test.o quadra.o -o $@

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
