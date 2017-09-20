#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>

#include "dx.h"

OutputItem::OutputItem(Labels *l) {
  renderFmt = "%-23s %-7s %-24s %c %s\n";
  labels = l;
  clear();
}

void OutputItem::clear() {
  for (int i=0; i<comments.size(); i++) {
    free(comments.at(i));
  }

  startAddress = -1;

  label[0] = EOS;
  instruction[0] = EOS;
  operand[0] = EOS;

  comments.clear();
}

void OutputItem::set(char *lab, char *inst, char *op, char *cmnt) {
  setLabel(lab);
  setInstruction(inst);
  setOperand(op);
  addComment(cmnt);
}

void OutputItem::render(char *lab, char *inst, char *op, char *cmnt) {
  if ((cmnt != NULL) && (cmnt[0] != EOS)) {
    addComment(cmnt);
  }

  if (lab == NULL) {
    lab = label;
  }

  if (inst == NULL) {
    inst = instruction;
  }

  if (op == NULL) {
    op = operand;
  }

  if (comments.size() == 0) {
    printf(renderFmt, lab, inst, op, ' ', "");
  }
  else {
    printf(renderFmt, lab, inst, op, ';', comments.at(0));
    comments.erase(comments.begin());
  }

  clear();
}

void OutputItem::flushComments() {
  for (int i=0; i<comments.size(); i++) {
    printf(renderFmt, "", "", "", ';', comments.at(i));
  }

  clear();
}

void OutputItem::render(char *inst, char *op) {
  render(NULL, inst, op, NULL);
}

void OutputItem::set(char *inst, char *op) {
  setInstruction(inst);
  setOperand(op);
}

void OutputItem::render(char *inst) {
  render(inst, NULL);
}

void OutputItem::render() {
  if (comments.size() == 0) {
    render(label, instruction, operand, NULL);
  }
  else {
    render(label, instruction, operand, comments.at(0));
  }
}

void OutputItem::setLabel(const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  vsprintf(label, fmt, args);
  va_end(args);
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

  if (fmt != NULL) {
    va_start(args, fmt);
    vsprintf(comment, fmt, args);
    va_end(args);

    comments.push_back(strdup(comment));
  }
}

void OutputItem::setAddress(long addr) {
  startAddress = addr;

  if (labels->isLabel(addr)) {
    labels->lookupLabel(addr, label);
  }
}

