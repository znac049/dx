#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

Memory::Memory(long mSize) {
  memorySize = mSize;
  memory.clear();
  memory.reserve(memorySize);

  printf("Memory size=%d\n", memorySize);

  for (int i=0; i<memorySize; i++) {
    memory[i] = new MemoryCell();
  }

  bigEndian = true;
}

void Memory::setEndian(bool big) {
  bigEndian = big;
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

  printf("Read file '%s' into memory at $%04x\n", fileName, addr);

  if (!fd) {
    return NO;
  }

  while(!feof(fd)) {
    int c = fgetc(fd);

    if (c != EOF) {
      if (isValidAddress(addr)) {
	memory[addr++]->set(c);
      }

      nBytes++;
    }
  }

  fclose(fd);

  printf("%d bytes read\n", nBytes);

  return nBytes;
}

int Memory::getByte(long addr) {
  assertAddressValid(addr);

  return memory[addr]->get();
}

void Memory::setByte(long addr, int b) {
  assertAddressValid(addr);

  memory[addr]->set(b);
}

int Memory::getWord(long addr) {
  int b1, b2;

  b1 = memory[addr]->get();
  b2 = memory[addr+1]->get();

  return bigEndian ? ((b1<<8) | b2) : ((b2<<8) | b1);
}

int Memory::getDword(long addr) {
  dword_t low, lowish, highish, high;

  low     = memory[addr+3]->get();
  lowish  = memory[addr+2]->get();
  highish = memory[addr+1]->get();
  high    = memory[addr]->get();

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
      memory[addr+i]->setType(type);
    }
  }

  return count;
}
