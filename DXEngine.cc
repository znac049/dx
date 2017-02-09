#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

DXEngine::DXEngine(long beg, long end) {
  romStart = beg;
  romEnd = end;

  initialise();
}

void DXEngine::initialise() {
  mem = new Memory(0x10000);
  labels = new Labels(romStart, romEnd);
}

void DXEngine::stackAddress(long addr) {
  addressStack.push_back(addr);
}

int DXEngine::fetch8() {
  if (!mem->isValidAddress(pc)) {
    Utils::abortf("fetch8() - Address out of range: $%x\n", pc);
  }

  return mem->getByte(pc++);
}

int DXEngine::fetch16() {
  long val;

  if (!mem->isValidAddress(pc)) {
    Utils::abortf("fetch16() - Address out of range: $%x\n", pc);
  }
  
  val = mem->getWord(pc);
  pc += 2;

  return val;
}

int DXEngine::fetch32() {
  long val;

  if (!mem->isValidAddress(pc)) {
    Utils::abortf("fetch32() - Address out of range: $%x\n", pc);
  }
  
  val = mem->getDword(pc);
  pc += 4;

  return val;
}

int DXEngine::disassemble(long addr) {
}

void DXEngine::disassemble() {
  while (!addressStack.empty()) {
    long addr = addressStack.at(0);
  }
}

