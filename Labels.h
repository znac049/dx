#ifndef _LABELS_H_
#define _LABELS_H_

#include <vector>

class Labels {
 private:
  vector<Label *> labels;
  long romStart;
  long romEnd;

 protected:
 public:

 private:
  void ProcessLine(char *line);

 protected:
 public:
  Labels(long romStart, long romEnd);

  void createLabel(const char *lab, long addr);
  bool isLabel(long addr);
  bool isLabel(const char *name);
  int labelCount(long addr);
  Label *findLabel(long addr);

  void lookupLabel(long addr, char *labStr, size_t labLen, int nDigits);
  void lookupLabel(long addr, char *labStr);
  void lookupShortLabel(long addr, char *labStr);

  int readFile(const char *fileName);
  void processLine(char *line);

  void exportLabels();
};

#endif
