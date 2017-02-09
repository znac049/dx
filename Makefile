SRC = dx.cc Args.cc DXEngine.cc Label.cc Labels.cc Memory.cc MemoryCell.cc Utils.cc
OBJ=$(subst .cc,.o,$(SRC))
HDRS=$(wildcard *.h)

EXE = dx

CC = g++
LD = g++

CFLAGS = -O2 -UH6309 -Wno-format
LDFLAGS =

BINDIR = $(DESTDIR)/bin
MANDIR = $(DESTDIR)/share/man/man1
DOCDIR = $(DESTDIR)/share/doc

.cc.o: $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY:	all clean

all: $(EXE)

$(EXE): ${OBJ}
	${LD} -o $(EXE) ${OBJ} ${LDFLAGS}

proto: clean
	cproto *.c >proto.h

clean:
	rm -f *.o *~ \#* $(EXE)
