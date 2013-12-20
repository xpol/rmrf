RM=rm -f

INCLUDES = -I src
CXXFLAGS = -g -Wall ${INCLUDES}

all: librmrf.a

librmrf.a: src/rmrf.o

test: test/test.o
	$(CXX) -o $@ $^ -lrmrf $(CXXFLAGS)

src/rmrf.o: src/rmrf.cpp src/rmrf.hpp

test/test.o: test/test.cpp src/rmrf.hpp

clean:
	$(RM) src/rmrf.o test/test.o

dist-clean: clean
	$(RM) librmrf.a test
