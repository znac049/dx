#ifndef _ENGINE_X09_H_
#define _ENGINE_X09_H_

#include "DXEngine.h"

class EngineX09 : DXEngine {
 private:
  enum AddressMode {
    _illegal, _implied, _imm_byte, _imm_word, _direct, _extended,
    _indexed, _rel_byte, _rel_word, _reg_post, _sys_post, _usr_post,
#ifdef H6309
    _imm_direct, _imm_quad, _reg_reg, _single_bit, _blk_move
#endif
  };

  enum InstCode
  {
    _undoc, _abx, _adca, _adcb, _adda, _addb, _addd, _anda, _andb,
    _andcc, _asla, _aslb, _asl, _asra, _asrb, _asr, _bcc, _lbcc,
    _bcs, _lbcs, _beq, _lbeq, _bge, _lbge, _bgt, _lbgt, _bhi,
    _lbhi, _bita, _bitb, _ble, _lble, _bls, _lbls, _blt, _lblt,
    _bmi, _lbmi, _bne, _lbne, _bpl, _lbpl, _bra, _lbra, _brn,
    _lbrn, _bsr, _lbsr, _bvc, _lbvc, _bvs, _lbvs, _clra, _clrb,
    _clr, _cmpa, _cmpb, _cmpd, _cmps, _cmpu, _cmpx, _cmpy, _coma,
    _comb, _com, _cwai, _daa, _deca, _decb, _dec, _eora, _eorb,
    _exg, _inca, _incb, _inc, _jmp, _jsr, _lda, _ldb, _ldd,
    _lds, _ldu, _ldx, _ldy, _leas, _leau, _leax, _leay, _lsra,
    _lsrb, _lsr, _mul, _nega, _negb, _neg, _nop, _ora, _orb,
    _orcc, _pshs, _pshu, _puls, _pulu, _rola, _rolb, _rol, _rora,
    _rorb, _ror, _rti, _rts, _sbca, _sbcb, _sex, _sta, _stb,
    _std, _sts, _stu, _stx, _sty, _suba, _subb, _subd, _swi,
    _swi2, _swi3, _sync, _tfr, _tsta, _tstb, _tst, _reset,
#ifdef H6309
    _negd, _comd, _lsrd, _rord, _asrd, _rold, _decd, _incd, _tstd,
    _clrd, _oim, _aim, _eim, _addr, _lde, _ldf, _ldw, _dece, _ince, 
    _tste, _clre, _decf, _incf, _tstf, _clrf, _come, _comf, 
    _ldq, _stq, _sexw, _tim, _pshsw, _pshuw, _pulsw, _puluw,
    _ste, _stf, _adcr, _subr, _sbcr, _andr, _orr, _eorr, _cmpr,
    _asld, _comw, _lsrw, _rorw, _rolw, _decw, _incw, _tstw, _clrw,
    _subw, _cmpw, _sbcd, _andd, _bitd, _eord, _adcd, _ord, _addw,
    _band, _biand, _bor, _bior, _beor, _bieor, _ldbt, _stbt, _stw,
    _tfm, _bitmd, _ldmd, _sube, _cmpe, _adde, _subf, _cmpf, _addf,
    _divd, _divq, _muld
#endif
  };

  static const char *mne[];

  struct Opcode
  {
    int code;
    int mode;
  };

  static struct Opcode codes[256];
  static struct Opcode codes10[256];
  static struct Opcode codes11[256];

  static const char *reg[];
  static const char index_reg[];
  static const char *off4[];

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
 EngineX09(Args *args, long beg, long end, const char *file) : DXEngine(args, beg, end, file) {};
  virtual void initialise();

  int disassembleAsBytes(OutputItem *out, long addr, int count);
  bool disassembleReglist(OutputItem *out, Opcode *opcode);
  void disassembleIndexed(OutputItem *out, int instruction);

  virtual int disassemble(long addr, OutputItem *out);
};

#endif
