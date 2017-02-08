#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

Memory::Memory(long mSize) {
  memorySize = mSize;
  memory = new MemoryCell*[memorySize];

  for (int i=0; i<memorySize; i++) {
    memory[i] = new MemoryCell();
  }
}

bool Memory::isValidAddress(long addr) {
  return ((addr >= 0) && (addr < memorySize));
}

void Memory::assertAddressValid(long addr) {
  if (!isValidAddress(addr)) {
    throw RangeException();
  }
}

long Memory::readFile(const char *file_name, long addr) {
  FILE *fd = fopen(file_name, "rb");
  int nBytes = 0;

  if (!fd) {
    return NO;
  }

  while(!feof(fd)) {
    memory[addr+nBytes]->set(fgetc(fd));
    nBytes++;
  }

  fclose(fd);

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
  int lsb, msb;

  lsb = memory[addr+1]->get();
  msb = memory[addr]->get();

  return lsb | (msb << 8);
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

#if 0
memoryType_t get_memory_type(address_t addr) {
  return MemoryType[addr];
}
#endif
