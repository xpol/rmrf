RM=rm -f

INCLUDES = -Isrc
LOADLIBES = -L./
CXXFLAGS = -g -Wall -static ${INCLUDES}

all: tests/rmrf

librmrf.a: src/rmrf.o
	$(AR) rcs $@ $^

tests/rmrf: tests/test.o librmrf.a
	$(CXX) -o $@ $^ -lrmrf $(CXXFLAGS) $(LOADLIBES)


src/rmrf.o: src/rmrf.cpp src/rmrf.hpp

tests/test.o: tests/test.cpp src/rmrf.hpp

.PHONY: test

test:
	@echo "Running tests..."
	bash ./tests/setup.sh
	./tests/rmrf target
	@! [ -d target ]
	@echo "Pass"

clean:
	$(RM) src/rmrf.o tests/test.o

dist-clean: clean
	$(RM) librmrf.a tests/rmrf tests/rmrf.exe
