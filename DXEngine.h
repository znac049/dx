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

  bool verbose;

 public:

 private:
 protected:
 public:
  DXEngine(Args *args, long beg, long end, const char *file);
  DXEngine();

  virtual void initialise();
  virtual void usage();

  void setAddressMask(long mask);
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
};

#endif
