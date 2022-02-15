CC = gcc
CFLAGS = -I . -g -Wall #-O3
LDFLAGS = -lgmp

.SUFFIXES: .c .o

PRGS = log_test

all:\
	$(PRGS)

log_test:\
	log_test.o log.o
	$(CC) log_test.o log.o -o $@ $(LDFLAGS)

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
