#ifndef _OUTPUTITEM_H_
#define OUTPUTITEM_H_

#include <vector>

class OutputItem {
 private:
  Labels *labels;
  char *renderFmt;
  std::vector<char *> comments;
  char instruction[MAXSTR];
  char operand[MAXSTR];
  long startAddress;
  char label[MAXSTR];

 public:
  OutputItem(Labels *l);

  void clear();
  void render();
  void render(char *inst);
  void render(char *inst, char *op);
  void render(char *lab, char *inst, char *op, char *cmnt);
  void flushComments();

  void setLabel(const char *fmt, ...);
  void setInstruction(const char *fmt, ...);
  void setOperand(const char *fmt, ...);
  void addComment(const char *fmt, ...);
  void setType(int newType);
  void setAddress(long addr);
};

#endif
