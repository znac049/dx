#ifndef _ENGINE_6502_H_
#define _ENGINE_6502_H_

#include "DXEngine.h"

class Engine6502 : DXEngine {
 private:
  enum AddressMode {
    _illegal, _xind, _zpg, _impl, _immed, _accum, _abs, _indy, _zpgx,
    _absy, _absx, _rel, _zpgy, _ind
  };

  enum InstCode
  {
    _undoc, _adc, _and, _asl, _bcc, _bcs, _beq, _bit, _bmi, _bne,
    _bpl, _brk, _bvc, _bvs, _clc, _cld, _cli, _clv, _cmp, _cpx, _cpy,
    _dec, _dex, _dey, _eor, _inc, _inx, _iny, _jmp, _jsr, _lda, 
    _ldx, _ldy, _lsr, _nop, _ora, _pha, _php, _pla, _plp, _rol, _ror,
    _rti, _rts, _sbc, _sec, _sed, _sei, _sta, _stx, _sty, _tax, _tay,
    _tsx, _txa, _txs, _tya
  };

  static const char *mne[];

  struct Opcode
  {
    int code;
    int mode;
  };

  static struct Opcode codes[256];
  static struct Opcode codes11[256];

  static const char *reg[];
  static const char index_reg[];
  static const char *off4[];

  static const long RESETVec = 0xfffc;
  static const long NMIVec = 0xfffe;
  static const long IRQVec = 0xfffa;

 protected:
 public:

 private:
 protected:
 public:
 Engine6502() : DXEngine() {};
 Engine6502(Args *args, long beg, long end, const char *file) : DXEngine(args, beg, end, file) {};
  virtual void initialise();
  virtual void usage();

  int disassembleAsBytes(OutputItem *out, long addr, int count);

  virtual int disassemble(long addr, OutputItem *out);
};

#endif