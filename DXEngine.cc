#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

DXEngine::DXEngine() {
}

DXEngine::DXEngine(Args *arguments, long beg, long end, long mask, const char *romFile) {
  args = arguments;

  romStart = beg;
  romEnd = end;

  mem = new Memory(0x10000);
  mem->setAddressMask(mask);
  mem->readFile(romFile, romStart);

  setByteDirective("dc.b");
  setWordDirective("dc.w");

  byteStack.clear();

  labels = new Labels(romStart, romEnd);
}

void DXEngine::initialise() {
  printf("DXEngine initialised\n");
}

bool DXEngine::alreadyStacked(long addr) {
  int numAddresses = addressStack.size();

  addr = mem->maskAddress(addr);
  for (int i=0; i<numAddresses; i++) {
    if (addressStack.at(i) == addr) {
      return true;
    }
  }

  return false;
}

void DXEngine::stackAddress(long addr, const char *lab) {
  addr = mem->maskAddress(addr);

  if (!labels->isLabel(lab)) {
    labels->createLabel(lab, addr);
  }

  if ((addr >= romStart) && (addr <= romEnd)) {
    if (!alreadyStacked(addr)) {
      addressStack.push_back(addr);
    }
  }
}

void DXEngine::stackAddress(long addr) {
  char lab[MAXSTR];

  addr = mem->maskAddress(addr);

  sprintf(lab, "L%04x", addr);
  stackAddress(addr, lab);
}

void DXEngine::stackRelAddress(long addr) {
  char lab[MAXSTR];

  addr = mem->maskAddress(addr);

  if (!labels->isLabel(addr)) {
    sprintf(lab, "R%04x", addr);
    stackAddress(addr, lab);
  }
}

void DXEngine::readVector(long addr, const char *vecName) {
  long vector = mem->getWord(addr);
  char name[MAXSTR];

  if ((vector >= romStart) && (vector <= romEnd)) {
    addressStack.push_back(vector);
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
    snprintf(label, MAXSTR-1, "$%02x", target);
  }

  return target;
}

int DXEngine::fetch8RelLab(char *label) {
  int target = fetch8Rel();

  if (labels->isLabel(target)) {
    labels->lookupLabel(target, label);
  }
  else {
    snprintf(label, MAXSTR-1, "$%02x", target);
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
    snprintf(label, MAXSTR-1, "$%04x", target);
  }

  return target;
}

int DXEngine::fetch16RelLab(char *label) {
  int target = fetch16Rel();

  if (labels->isLabel(target)) {
    labels->lookupLabel(target, label);
  }
  else {
    snprintf(label, MAXSTR-1, "$%04x", target);
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

int DXEngine::disassemble(long addr) {
  printf("Bang!\n");
  return -1;
}

bool DXEngine::canBranch(long addr) {
  return false;
}

long DXEngine::branchAddress(long addr) {
  return -1;
}

bool DXEngine::validCode(long addr) {
  return false;
}

int DXEngine::codeSize(long addr) {
  return -1;
}

void DXEngine::pass1() {
  int i=0;
  long addr;
  long nBytes;
  char label[MAXSTR];

  // Pass 1 - disassemble everything you can
  while (i < addressStack.size()) {
    addr = addressStack.at(i);

    while (validCode(addr)) {
      if (canBranch(addr)) {
	stackAddress(branchAddress(addr));
      }

      nBytes = codeSize(addr);
      mem->setType(addr, Memory::CODE, nBytes);
      addr += nBytes;
    }

    i++;
  }
}

void DXEngine::disassemble() {
  int i=0;
  long addr;
  OutputItem out(labels);
  long nBytes;
  char label[MAXSTR];

  // Pass 1 - disassemble everything you can
  pass1();

  // Pass 2 - move through the rom image emitting assembly code
  labels->exportLabels();

  printf("\n");

  for (addr = romStart; addr < romEnd; ) {
    int type = mem->getType(addr);

    out.clear();

    switch (type) {
    case Memory::CODE:
      flushByteStack();

      nBytes = abs(disassemble(addr));

      addr += nBytes;
      break;

    case Memory::UNKNOWN:
    case Memory::BYTE:
      stackByte(mem->getByte(addr), addr);

      addr++;
      break;

    case Memory::WORD:
      {
	long val = mem->getWord(addr);

	flushByteStack();

	out.setInstruction(wordDirective);
	out.addComment("%04X", addr);
	if (labels->isLabel(val)) {
	  labels->lookupLabel(val, label);
	  out.setOperand(label);
	}
	else {
	  out.setOperand("$%04X", val);
	}

	addr += 2;

	out.render();
      }
      break;

    default:
      flushByteStack();

      out.setInstruction("???");
      out.setOperand("$%02X", mem->getByte(addr));
      out.addComment("Addr=%04X, Data=%02X, Type=%d", addr, mem->getByte(addr), type);

      addr++;

      out.render();
      break;
    }
  }
  
  flushByteStack();

  //labels->dumpLabels();
}

void DXEngine::setByteDirective(const char *mnem) {
  strcpy(byteDirective, mnem);
}

void DXEngine::setWordDirective(const char *mnem) {
  strcpy(wordDirective, mnem);
}

void DXEngine::usage() {
}

void DXEngine::dump() {
  mem->dump();
}

void DXEngine::stackByte(int byte, long addr) {
  // Is there room to stack this?
  if (byteStack.size() >= 4) {
    flushByteStack();
  }

  if (byteStack.size() == 0) {
    byteStackAddr = addr;
  }

  byteStack.push_back(byte);
}

void DXEngine::flushByteStack() {
  OutputItem out(labels);
  char data[MAXSTR];
  char single[8];
  int stackSize = byteStack.size();

  if (byteStack.size() > 0) {
    strcpy(data, "");

    for (int i=0; i<stackSize; i++) {
      if (i != 0) {
	strcat(data, ",");
      }

      sprintf(single, "$%02X", byteStack.at(i));
      strcat(data, single);
    }

    out.setAddress(byteStackAddr);
    out.setInstruction(byteDirective);
    out.setOperand(data);
    out.render();

    byteStack.clear();
  }
}
