#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

Memory::Memory(long mSize) {
  memorySize = mSize;
  memory.clear();
  memory.reserve(memorySize);

  //printf("Memory size=%d\n", memorySize);

  for (int i=0; i<memorySize; i++) {
    memory[i] = new MemoryCell();
  }

  bigEndian = true;
}

void Memory::dump() {
  printf("Memory dump:\n");

  for (int bank=0; bank < memorySize; bank += 16) {
    bool empty = true;
    int i;

    for (i=0; i<16; i++) {
      if (memory[bank+i]->getType() != UNSET) {
	empty = false;
      }
    }

    if (!empty) {
      printf("%08x: ", bank);

      for (i=0; i<16; i++) {
	int val = memory[bank+i]->get();
	int type = memory[bank+i]->getType();

	if (type == UNSET) {
	  printf(" --");
	}
	else {
	  printf(" %02x", val);
	}
      }

      putchar('\n');
    }
  }
}

void Memory::setEndian(bool big) {
  bigEndian = big;
}

void Memory::setAddressMask(long mask) {
  addressMask = mask;
}

long Memory::maskAddress(long addr) {
  return addr & addressMask;
}

bool Memory::isValidAddress(long addr) {
  return ((addr >= 0) && (addr < memorySize));
}

void Memory::assertAddressValid(long addr) {
  if (!isValidAddress(addr)) {
    throw RangeException();
  }
}

long Memory::readFile(const char *fileName, long addr) {
  FILE *fd = fopen(fileName, "rb");
  int nBytes = 0;
  long start = addr;

  //printf("Read file '%s' into memory at $%04x\n", fileName, addr);

  if (!fd) {
    return NO;
  }

  while(!feof(fd)) {
    int c = fgetc(fd);

    if (c != EOF) {
      if (isValidAddress(addr)) {
	memory[maskAddress(addr)]->set(c);
	memory[maskAddress(addr)]->setType(UNKNOWN);
	addr++;
      }

      nBytes++;
    }
  }

  fclose(fd);

  //printf("%d bytes read into $%04x-$%04x\n", nBytes, start, addr-1);
  //printf("         masked to $%04x-$%04x\n", maskAddress(start), maskAddress(addr-1));

  return nBytes;
}

int Memory::getByte(long addr) {
  assertAddressValid(addr);

  return memory[maskAddress(addr)]->get();
}

void Memory::setByte(long addr, int b) {
  assertAddressValid(addr);

  memory[maskAddress(addr)]->set(b);
}

int Memory::getWord(long addr) {
  int b1, b2;

  b1 = memory[maskAddress(addr)]->get();
  b2 = memory[maskAddress(addr+1)]->get();

  return bigEndian ? ((b1<<8) | b2) : ((b2<<8) | b1);
}

int Memory::getDword(long addr) {
  dword_t low, lowish, highish, high;

  low     = memory[maskAddress(addr+3)]->get();
  lowish  = memory[maskAddress(addr+2)]->get();
  highish = memory[maskAddress(addr+1)]->get();
  high    = memory[maskAddress(addr)]->get();

  return low | (lowish << 8) | (highish << 16) | (high << 24);
}

void Memory::setDword(long addr, int val) {
  throw exception();
}

int Memory::setType(long addr, int type, int count) {
  int size = (type == WORD)?2:1;

  count = count * size;
  for (int i=0; i<count; i++) {
    if (isValidAddress(addr+i)) {
      memory[maskAddress(addr+i)]->setType(type);
    }
  }

  return count;
}
