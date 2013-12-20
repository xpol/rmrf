RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)


all: librmrf.a

librmrf.a: src/rmrf.o

src/rmrf.o: src/rmrf.cpp src/rmrf.hpp


clean:
    $(RM) src/rmrf.o

dist-clean: clean
    $(RM) librmrf.a
