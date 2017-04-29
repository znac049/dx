#ifndef _ENGINE_DVG_H_
#define _ENGINE_DVG_H_

#include "DXEngine.h"

class EngineDVG : DXEngine {
 private:
 protected:
 public:

 private:
 protected:
 public:
 EngineDVG(Args *args, long beg, long end, const char *file) : DXEngine(args, beg, end, file) {};
  virtual void initialise();

  virtual int disassemble(long addr, OutputItem *out);
};

#endif
