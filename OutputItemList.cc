#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>

#include "dx.h"

OutputItemList::OutputItemList(Labels *l) {
  labs = l;
  clear();
}

void OutputItemList::clear() {
  for (int i=0; i<comments.size(); i++) {
    free(comments.at(i));
  }
  comments.clear();

  for (int i=0; i<items.size(); i++) {
    delete items.at(i);
  }
  items.clear();
}

void OutputItemList::render() {
  int nComments = comments.size();

  if (nComments > 1) {
    printf("\n");
  }

  for (int i=0; i<comments.size(); i++) {
    printf("; %s\n", comments.at(i));
  }

  if (nComments > 1) {
    printf(";\n");
  }
}

void OutputItemList::addItem(OutputItem *item) {
  items.push_back(item);
}

void OutputItemList::addComment(const char *fmt, ...) {
  va_list args;
  char comment[MAXSTR];

  va_start(args, fmt);
  vsprintf(comment, fmt, args);
  va_end(args);

  comments.push_back(strdup(comment));
}
