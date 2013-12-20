RM=rm -f

INCLUDES = -Isrc
LOADLIBES = -L./
CXXFLAGS = -g -Wall -static ${INCLUDES}

all: rmrf

librmrf.a: src/rmrf.o
	$(AR) rcs $@ $^

rmrf: test/test.o librmrf.a
	$(CXX) -o $@ $^ -lrmrf $(CXXFLAGS) $(LOADLIBES)


src/rmrf.o: src/rmrf.cpp src/rmrf.hpp

test/test.o: test/test.cpp src/rmrf.hpp

clean:
	$(RM) src/rmrf.o test/test.o

dist-clean: clean
	$(RM) librmrf.a rmrf rmrf.exe
