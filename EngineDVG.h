#ifndef _ENGINE_DVG_H_
#define _ENGINE_DVG_H_

#include "DXEngine.h"

#define NUM_DVG_OPS 16

#define DVG_OP_NONE -1
#define DVG_OP_VLDRAW 0         // VEC  - Draw relative vector
#define DVG_OP_HALT 1           // HALT - Halt
#define DVG_OP_VSDRAW 2         // SVEC - Draw short relative vector
#define DVG_OP_VSCALE 3         //      -New scale
#define DVG_OP_VCENTER 4        //      - Center beam
#define DVG_OP_VJSR 5           // JSR  - Jump to subroutine
#define DVG_OP_VRTS 6           // RTS  - Return from subroutine
#define DVG_OP_VJMP 7           // JMP  - Jump to new address
#define DVG_OP_VMOVETO 8        // MOVE - Beam to absolute position
#define DVG_OP_VSCALED_DRAW 9   // SSV  - Draw relative vector and load scale
#define DVG_OP_VCOLOR 10        //      - New colour/intensity

class EngineDVG : DXEngine {
 private:
  int opMap[NUM_DVG_OPS];
  static char *scales[];

 protected:
 public:

 private:
 protected:
  int decode4(int word);
  int decode12(int word);
  int findRTSOp();
  void backup(long addr);

 public:
 EngineDVG() : DXEngine() {};
 EngineDVG(Args *args, long beg, long end, long mask, const char *file) : DXEngine(args, beg, end, mask, file) {};
  virtual void initialise();
  virtual void usage();

  virtual bool canBranch(long addr);
  virtual long branchAddress(long addr);
  virtual bool validCode(long addr);
  virtual int codeSize(long addr);
  virtual int disassemble(long addr);
  virtual void pass1();
};

#endif
