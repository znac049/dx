#ifndef _MEMORY_H_
#define _MEMORY_H_

class Memory {
 private:
  MemoryCell **memory;
  unsigned char *cellTypes;
  long memorySize;

 protected:
 public:
  enum MemoryType {UNKNOWN, BYTE, WORD, CODE};

 private:
  void assertAddressValid(long addr);

 protected:
 public:
  Memory(long mSize);

  long readFile(const char *file_name, long addr);

  bool isValidAddress(long addr);
  int getByte(long addr);
  void setByte(long addr, int val);
  int getWord(long addr);
  void setWord(long addr, int val);
  int getDword(long addr);
  void setDword(long addr, int val);

  int setType(long addr, int type, int count);
};

#endif
