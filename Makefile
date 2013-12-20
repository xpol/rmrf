RM=rm -f

CPPFLAG += -Isrc

all: librmrf.a

librmrf.a: src/rmrf.o

test: test/test.o librmrf.a
	$(CXX) -o $@ $^ $(LDFLAGS)

src/rmrf.o: src/rmrf.cpp src/rmrf.hpp

test/test.o: test/test.cpp src/rmrf.hpp

clean:
	$(RM) src/rmrf.o test/test.o

dist-clean: clean
	$(RM) librmrf.a test
