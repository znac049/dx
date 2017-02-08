#include "dx.h"

MemoryCell::MemoryCell() {
  set(0);
}

MemoryCell::MemoryCell(int val) {
  set(val);
}

void MemoryCell::set(int val) {
  value = val;
}

int MemoryCell::get() {
  return value;
}
