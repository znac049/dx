#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "dx.h"

Label::Label() {
  name = NULL;
  address = -1;
}

Label::Label(const char *labName) {
  name = NULL;
  setName(labName);
  address = -1;
}

Label::Label(const char *labName, long addr) {
  name = NULL;
  setName(labName);
  address = addr;
}

void Label::setName(const char *labName) {
  if (name != NULL) {
    free(name);
  }

  if (labName == NULL) {
    name = NULL;
  }
  else {
    name = strdup(labName);
  }
}

const char *Label::getName() {
  return name;
}

void Label::setAddress(long addr) {
  address = addr;
}

long Label::getAddress() {
  return address;
}

