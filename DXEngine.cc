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
  {NULL,         0,                                       NULL,    0}
}; 
 
static parseopt_t optionalArgs[] = {
  {"help",        0,                                      NULL,     '?' },
  {"verbose",     Args::requires_argument | Args::boolean_argument, verbose,  'v' },
  {NULL,          0,                                      NULL,     0}
};
#endif

DXEngine::DXEngine(Args *arguments, long beg, long end, const char *romFile) {
  args = arguments;

  romStart = beg;
  romEnd = end;

  mem = new Memory(0x10000);
  mem->readFile(romFile, romStart);

  labels = new Labels(romStart, romEnd);
}

void DXEngine::initialise() {
  printf("DXEngine initialised\n");
}

bool DXEngine::alreadyStacked(long addr) {
  int numAddresses = addressStack.size();

  for (int i=0; i<numAddresses; i++) {
    if (addressStack.at(i) == addr) {
      return true;
    }
  }

  return false;
}

void DXEngine::stackAddress(long addr) {
  if ((addr >= romStart) && (addr <= romEnd)) {
    if (!alreadyStacked(addr)) {
      printf("push $%04x\n", addr);
      addressStack.push_back(addr);
    }
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

int DXEngine::fetch8Rel() {
  int offset = fetch8();

  return pc+offset;
}

int DXEngine::fetch8Lab(char *label) {
  int target = fetch8();

  if (labels->isLabel(target)) {
    labels->lookupLabel(target, label);
  }
  else {
    snprintf(label, MAXSTR-1, "L_%02x", target);
  }

  return target;
}

int DXEngine::fetch8RelLab(char *label) {
  int target = fetch8Rel();

  if (labels->isLabel(target)) {
    labels->lookupLabel(target, label);
  }
  else {
    snprintf(label, MAXSTR-1, "L_%02x", target);
  }

  return target;
}

int DXEngine::fetch16() {
  long val;

  if (!mem->isValidAddress(pc)) {
    Utils::abortf("fetch16() - Address out of range: $%x\n", pc);
  }
  
  val = mem->getWord(pc);

  if (args->hasArg("verbose")) {
    printf("fetch16 @%04x=%02lx\n", pc, val);
  }

  pc += 2;

  return val;
}

int DXEngine::fetch16Rel() {
  int offset = fetch16();

  return pc+offset;
}

int DXEngine::fetch16Lab(char *label) {
  int target = fetch16();

  if (labels->isLabel(target)) {
    labels->lookupLabel(target, label);
  }
  else {
    snprintf(label, MAXSTR-1, "L_%04x", target);
  }

  return target;
}

int DXEngine::fetch16RelLab(char *label) {
  int target = fetch16Rel();

  if (labels->isLabel(target)) {
    labels->lookupLabel(target, label);
  }
  else {
    snprintf(label, MAXSTR-1, "L_%04x", target);
  }

  return target;
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

int DXEngine::disassemble(long addr, OutputItem *out) {
  return -1;
}

void DXEngine::disassemble() {
  while (!addressStack.empty()) {
    long addr = addressStack.at(0);
    long nBytes;
    OutputItem out;

    addressStack.erase(addressStack.begin());

    printf("Disassemble from $%04x\n", addr);
    nBytes = disassemble(addr, &out);
    out.render();
    while (nBytes > 0) {
      addr += nBytes;
      nBytes = disassemble(addr, &out);
      out.render();
    }
  }
}

