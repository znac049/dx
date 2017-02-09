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

 public:

 private:
 protected:
 public:
  DXEngine(Args *args, long beg, long end);

  virtual void initialise();

  int fetch8();
  int fetch16();
  int fetch32();

  void stackAddress(long addr);
  void readVector(long addr, const char *vecName);

  void disassemble();
  virtual int disassemble(long addr);
};

#endif
