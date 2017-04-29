#ifndef _OUTPUTITEM_H_
#define OUTPUTITEM_H_

#include <vector>

class OutputItem {
 private:
  std::vector<char *> comments;
  char instruction[MAXSTR];
  char operand[MAXSTR];
  int type;
  long startAddress;

 public:
  OutputItem();

  void clear();
  void render();

  void setInstruction(const char *fmt, ...);
  void setOperand(const char *fmt, ...);
  void addComment(const char *comment);
  void setType(int newType);
  void setAddress(long addr);
};

#endif
