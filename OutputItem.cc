#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>

#include "dx.h"

OutputItem::OutputItem() {
  clear();
}

void OutputItem::clear() {
  for (int i=0; i<comments.size(); i++) {
    free(comments.at(i));
  }

  comments.clear();

  instruction[0] = EOS;
  operand[0] = EOS;
  type = Memory::BYTE;
  startAddress = 0;
}

void OutputItem::render() {
  switch (type) {
  case Memory::BYTE:
    printf("BYTE!!!!\n");
    break;

  case Memory::WORD:
    printf("WORD!!!!\n");
    break;

  case Memory::CODE:
    printf("%04X     %-8s %s\n", startAddress, instruction, operand); 
    break;
  }
}

void OutputItem::setInstruction(const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  vsprintf(instruction, fmt, args);
  va_end(args);
}

void OutputItem::setOperand(const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  vsprintf(operand, fmt, args);
  va_end(args);
}

void OutputItem::addComment(const char *cmnt) {
  comments.push_back(strdup(cmnt));
}

void OutputItem::setType(int nt) {
  type = nt;
}

void OutputItem::setAddress(long addr) {
  startAddress = addr;
}

