#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

#if 0
static parseopt_t mandatoryArgs[] = {
  {"cpu",        Args::requires_argument,                 cpuStr, 'c'},
  {"rom-start",  Args::requires_argument | Args::numeric_argument, &romStart, 'b'}, 
  {"rom-size",   Args::requires_argument | Args::numeric_argument, &romSize, 's'},
  {NULL,         0,                                       NULL, 0}
}; 
 
static parseopt_t optionalArgs[] = {
  {"help",        0,                                      NULL,  '?' },
  {"verbose",     0,                                      NULL,  'v' },
  {NULL,          0,                                      NULL,  0   }
};
#endif

DXEngine::DXEngine(Args *arguments, long beg, long end) {
  args = arguments;

  romStart = beg;
  romEnd = end;

  mem = new Memory(0x10000);
  labels = new Labels(romStart, romEnd);
}

void DXEngine::initialise() {
  printf("DXEngine initialised\n");
}

void DXEngine::stackAddress(long addr) {
  if ((addr >= romStart) && (addr <= romEnd)) {
    addressStack.push_back(addr);
  }
}

void DXEngine::readVector(long addr, const char *vecName) {
  long vector = mem->getWord(addr);
  char name[MAXSTR];

  if ((vector >= romStart) && (vector <= romEnd)) {
    stackAddress(vector);
    snprintf(name, MAXSTR-1, "%s_Handler", vecName);
    labels->createLabel(name, vector);
  }

  snprintf(name, MAXSTR-1, "%s_Vec", vecName);
  labels->createLabel(name, addr);
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
    long nBytes;

    printf("Disassemble from $%04x\n", addr);
    nBytes = disassemble(addr);
    while (nBytes > 0) {
      addr += nBytes;
      nBytes = disassemble(addr);
    }
  }
}

