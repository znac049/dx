#ifndef _ENGINE_H_
#define _ENGINE_H_

class DXEngine {
 private:
 protected:
  Args *args;
  long romStart;
  long romEnd;

  long pc;
  Memory *mem;
  Labels *labels;
  vector<long> addressStack;
  vector<int> byteStack;

  bool verbose;

  char byteDirective[MAXSTR];
  char wordDirective[MAXSTR];

 public:

 private:
 protected:
  void stackByte(int byte);
  void flushByteStack();

 public:
  DXEngine(Args *args, long beg, long end, long mask, const char *file);
  DXEngine();

  virtual void initialise();
  virtual void usage();

  int fetch8();
  int fetch8Rel();
  int fetch8Lab(char *label);
  int fetch8RelLab(char *label);
  int fetch16();
  int fetch16Rel();
  int fetch16Lab(char *label);
  int fetch16RelLab(char *label);
  int fetch32();

  bool alreadyStacked(long addr);
  void stackAddress(long addr);
  void readVector(long addr, const char *vecName);

  void disassemble();
  virtual int disassemble(long addr, OutputItem *out);

  void dump();

  void setByteDirective(const char *);
  void setWordDirective(const char *);
};

#endif
