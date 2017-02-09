#ifndef _ENGINE_X09_H_
#define _ENGINE_X09_H_

#include "DXEngine.h"

class EngineX09 : DXEngine {
 private:
  static const long RESETVec = 0xfffe;
  static const long NMIVec = 0xfffc;
  static const long SWIVec = 0xfffa;
  static const long IRQVec = 0xfff8;
  static const long FIRQVec = 0xfff6;
  static const long SWI2Vec = 0xfff4;
  static const long SWI3Vec = 0xfff2;

 protected:
 public:

 private:
 protected:
 public:
  EngineX09(Args *args, long beg, long end) : DXEngine(args, beg, end) {};
  virtual void initialise();
};

#endif
