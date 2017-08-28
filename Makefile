SRC = dx.cc \
	Args.cc \
	DXEngine.cc \
	Engine6502.cc \
	EngineX09.cc \
	EngineDVG.cc \
	Label.cc \
	Labels.cc \
	Memory.cc \
	MemoryCell.cc \
	OutputItem.cc \
	Utils.cc

OBJ=$(subst .cc,.o,$(SRC))
HDRS=$(wildcard *.h)

EXE = dx

CC = g++
LD = g++

CFLAGS = -UH6309 -Wno-format -g -O0
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

clean:
	rm -f *.o *~ \#* $(EXE) core
