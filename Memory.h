#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <vector>

class Memory {
 private:
  std::vector<MemoryCell *> memory;
  long memorySize;
  long addressMask;
  bool bigEndian;

 protected:
 public:
  enum MemoryType {UNKNOWN, BYTE, WORD, CODE};

 private:
  void assertAddressValid(long addr);

 protected:
 public:
  Memory(long mSize);

  long readFile(const char *file_name, long addr);

  void setEndian(bool big);
  void setAddressMask(long mask);
  bool isValidAddress(long addr);
  int getByte(long addr);
  void setByte(long addr, int val);
  int getWord(long addr);
  void setWord(long addr, int val);
  int getDword(long addr);
  void setDword(long addr, int val);
  long maskAddress(long addr);

  int setType(long addr, int type, int count);
};

#endif
