RM=rm -f

INCLUDES = -Isrc
LOADLIBES = -L./
CFLAGS = -g -Wall -static ${INCLUDES}

all: tests/rmrf

librmrf.a: src/rmrf.o
	$(AR) rcs $@ $^

tests/rmrf: tests/test.o librmrf.a
	$(CC) -o $@ $^ -lrmrf $(CFLAGS) $(LOADLIBES)


src/rmrf.o: src/rmrf.c src/rmrf.h

tests/test.o: tests/test.c src/rmrf.h

.PHONY: test

test: all
	@echo "Running tests..."
	bash ./tests/setup.sh
	./tests/rmrf target
	@! [ -d target ]
	@echo "Pass"

clean:
	$(RM) src/rmrf.o tests/test.o

dist-clean: clean
	$(RM) librmrf.a tests/rmrf tests/rmrf.exe
