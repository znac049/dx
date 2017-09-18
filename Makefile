SRC = dx.cc \
	Args.cc \
	DXEngine.cc \
	Engine6502.cc \
	EngineAtari.cc \
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

CFLAGS = -UH6309 -Wno-format -Wno-write-strings -g -O0
LDFLAGS =

BINDIR = $(DESTDIR)/bin
MANDIR = $(DESTDIR)/share/man/man1
DOCDIR = $(DESTDIR)/share/doc

.cc.o: $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY:	all clean test

all: $(EXE)

$(EXE): ${OBJ}
	${LD} -o $(EXE) ${OBJ} ${LDFLAGS}

clean:
	rm -f *.o *~ \#* $(EXE) core

test: all
	./dx --cpu=6502 --rom-start=0x6000 --rom-size=8192 --address-mask=0x7fff --label-file=Roms/ad-v3.lab Roms/ad-v3.bin >Roms/ad-v3.test
	./dx --cpu=atari --rom-start=0x6000 --rom-size=8192 --address-mask=0x7fff --label-file=Roms/ad-v3.lab Roms/ad-v3.bin >Roms/ad-v3.a09
	./dx --cpu=dvg --game=asteroids --rom-start=0x0000 --rom-size=4096 --address-mask=0x7fff Roms/ad-vg-v3.bin >Roms/ad-vg-v3.test
