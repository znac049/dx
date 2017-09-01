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
  static const char *fmt = "%-20s %-4s %-32s %c %s\n";
  static const char *addressFmt = "%04x";
  char lab[MAXSTR];
  int nComments;
  char *comment = (char *)"";
  char commentChar;

  if (labs->isLabel(startAddress)) {
    labs->lookupLabel(startAddress, lab);
    printf("\n");
  }
  else {
    //snprintf(lab, MAXSTR, addressFmt, startAddress);
    strcpy(lab, "");
  }

  switch (type) {
  case Memory::BYTE:
    break;

  case Memory::WORD:
    break;

  case Memory::CODE:
    break;

  default:
    strcpy(instruction, "???");
    break;
  }

  commentChar = ' ';
  nComments = comments.size();
  if (nComments) {
    comment = comments.at(0);
    commentChar = ';';
  }

  printf(fmt, lab, instruction, operand, commentChar, comment);

  for (int i=1; i<comments.size(); i++) {
    printf(fmt, "", "", "", commentChar, comments.at(i));
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

