all: debug.h afl-fuzz.c target.c
	clang -g -Og -o afl-fuzz afl-fuzz.c
	clang -g -Og -o target target.c

clean:
	rm afl-fuzz target