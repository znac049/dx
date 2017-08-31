#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>

#include "dx.h"

OutputItem::OutputItem(Labels *l) {
  labs = l;
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
  char lab[MAXSTR];

  if (!labs->isLabel(startAddress)) {
    labs->lookupLabel(startAddress, lab);
    lab[0] = EOS;
  }
  printf("\n%-20s ", lab);

  switch (type) {
  case Memory::BYTE:
    printf("BYTE!!!!\n");
    break;

  case Memory::WORD:
    printf("WORD!!!!\n");
    break;

  case Memory::CODE:
    printf("%-4s %s ", instruction, operand); 
    break;

  default:
    printf("Wah!\n");
    break;
  }

  if (comments.size()) {
    printf("; %s\n", comments.at(0));

    for (int i=1; i<comments.size(); i++) {
      printf("%30s ; %s\n", "", comments.at(i));
    }
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

void OutputItem::addComment(const char *fmt, ...) {
  va_list args;
  char comment[MAXSTR];

  va_start(args, fmt);
  vsprintf(comment, fmt, args);
  va_end(args);

  comments.push_back(strdup(comment));
}

void OutputItem::setType(int nt) {
  type = nt;
}

void OutputItem::setAddress(long addr) {
  startAddress = addr;
}

