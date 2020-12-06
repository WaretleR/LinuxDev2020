bin_PROGRAMS = prog
prog_SOURCES = prog.c fun.c const.c

CC = cc
CFLAGS = -fPIC
OBJFILES = prog.o fun.o const.o
OUTLIB = outlib.h
ONEARG = one
THREEARG = one two three
GENERATES = prog prog-a prog-so README *.so
TRASH = *.o *~ o.* *.a *.txt

all:    README prog

head:
	head -2 $(prog_SOURCES) $(OUTLIB)

update_comment:
	sh insver.sh

README: prog
	./$< 2> $@

liboutput_static.a: fun.o const.o
	ar rcs $@ $^

liboutput.so: fun.o const.o
	$(CC) -shared $^ -o $@

prog-a: prog.o liboutput_static.a
	$(CC) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	$(CC) -L. $< -loutput -o $@

out-%-0.txt: %
	LD_LIBRARY_PATH=`pwd` ./$^ 2>/dev/null >$@

out-%-1.txt: %
	LD_LIBRARY_PATH=`pwd` ./$^ $(ONEARG) 2>/dev/null >$@

out-%-3.txt: %
	LD_LIBRARY_PATH=`pwd` ./$^ $(THREEARG) 2>/dev/null >$@

test: out-prog-0.txt out-prog-a-0.txt out-prog-so-0.txt out-prog-1.txt out-prog-a-1.txt out-prog-so-1.txt out-prog-3.txt out-prog-a-3.txt out-prog-so-3.txt
	cmp out-prog-0.txt out-prog-a-0.txt
	cmp out-prog-0.txt out-prog-so-0.txt
	cmp out-prog-a-0.txt out-prog-so-0.txt
	cmp out-prog-1.txt out-prog-a-1.txt
	cmp out-prog-1.txt out-prog-so-1.txt
	cmp out-prog-a-1.txt out-prog-so-1.txt
	cmp out-prog-3.txt out-prog-a-3.txt
	cmp out-prog-3.txt out-prog-so-3.txt
	cmp out-prog-a-3.txt out-prog-so-3.txt

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)

