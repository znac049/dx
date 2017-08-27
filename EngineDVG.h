#ifndef _ENGINE_DVG_H_
#define _ENGINE_DVG_H_

#include "DXEngine.h"

#define NUM_DVG_OPS 16

#define DVG_OP_NONE -1
#define DVG_OP_VLDRAW 0
#define DVG_OP_HALT 1
#define DVG_OP_VSDRAW 2
#define DVG_OP_VSCALE 3
#define DVG_OP_VCENTER 4
#define DVG_OP_VJSR 5
#define DVG_OP_VRTS 6
#define DVG_OP_VJMP 7
#define DVG_OP_VMOVETO 8
#define DVG_OP_VSCALED_DRAW 9
#define DVG_OP_VCOLOR 10

class EngineDVG : DXEngine {
 private:
  int opMap[NUM_DVG_OPS];

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
