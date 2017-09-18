#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

const char *EngineAtari::mne[] = {
  "???", "adc", "and", "asl", "bcc", "bcs", "beq", 
  "bit", "bmi", "bne", "bpl", "brk", "bvc", "bvs", 
  "clc", "cld", "cli", "clv", "cmp", "cpx", "cpy",
  "dec", "dex", "dey", "eor", "inc", "inx", "iny", 
  "jmp", "jsr", "lda", "ldx", "ldy", "lsr", "nop", 
  "ora", "pha", "php", "pla", "plp", "rol", "ror",
  "rti", "rts", "sbc", "sec", "sed", "sei", "sta",
  "stx", "sty", "tax", "tay", "tsx", "txa", "txs", 
  "tya"
};

struct EngineAtari::Opcode EngineAtari::codes[] = {
  // 00
  {_brk, _impl},
  {_ora, _xind},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_ora, _zpg},
  {_asl, _zpg},
  {_undoc, _illegal},
  {_php, _impl},
  {_ora, _immed},
  {_asl, _accum},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_ora, _abs},
  {_asl, _abs},
  {_undoc, _illegal},

  // 10
  {_bpl, _rel},
  {_ora, _xind},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_ora, _zpgx},
  {_asl, _zpgx},
  {_undoc, _illegal},
  {_clc, _impl},
  {_ora, _absy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_ora, _absx},
  {_asl, _absx},
  {_undoc, _illegal},

  // 20
  {_jsr, _abs},
  {_and, _xind},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_bit, _zpg},
  {_and, _zpg},
  {_rol, _zpg},
  {_undoc, _illegal},
  {_plp, _impl},
  {_and, _immed},
  {_rol, _accum},
  {_undoc, _illegal},
  {_bit, _abs},
  {_and, _abs}, 
  {_rol, _abs},
  {_undoc, _illegal},

  // 30
  {_bmi, _rel},
  {_and, _indy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_and, _zpgx},
  {_rol, _zpgx},
  {_undoc, _illegal},
  {_sec, _impl},
  {_and, _absy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_and, _absx},
  {_rol, _absx},
  {_undoc, _illegal},

  // 40
  {_rti, _impl},
  {_eor, _xind},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_eor, _zpg},
  {_lsr, _zpg},
  {_undoc, _illegal},
  {_pha, _impl},
  {_eor, _immed},
  {_lsr, _accum},
  {_undoc, _illegal},
  {_jmp, _abs},
  {_eor, _abs},
  {_lsr, _abs},
  {_undoc, _illegal},

  // 50
  {_bvc, _rel},
  {_eor, _indy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_eor, _zpgx},
  {_lsr, _zpgx},
  {_undoc, _illegal},
  {_cli, _impl},
  {_eor, _absy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_eor, _absx},
  {_lsr, _absx},
  {_undoc, _illegal},

  // 60
  {_rts, _impl},
  {_adc, _xind},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_adc, _zpg},
  {_ror, _zpg},
  {_undoc, _illegal},
  {_pla, _impl},
  {_adc, _immed},
  {_ror, _accum},
  {_undoc, _illegal},
  {_jmp, _ind},
  {_adc, _abs},
  {_ror, _abs},
  {_undoc, _illegal},

  // 70
  {_bvs, _rel},
  {_adc, _indy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_adc, _zpgx},
  {_ror, _zpgx},
  {_undoc, _illegal},
  {_sei, _impl},
  {_adc, _absy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_adc, _absx},
  {_ror, _absx},
  {_undoc, _illegal},

  // 80
  {_undoc, _illegal},
  {_sta, _xind},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_sty, _zpg},
  {_sta, _zpg},
  {_stx, _zpg}, 
  {_undoc, _illegal},
  {_dey, _impl},
  {_undoc, _illegal},
  {_txa, _impl},
  {_undoc, _illegal},
  {_sty, _abs},
  {_sta, _abs},
  {_stx, _abs},
  {_undoc, _illegal},

  // 90
  {_bcc, _rel},
  {_sta, _indy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_sty, _zpgx},
  {_sta, _zpgx},
  {_stx, _zpgy},
  {_undoc, _illegal},
  {_tya, _impl},
  {_sta, _absy},
  {_txs, _impl},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_sta, _absx},
  {_undoc, _illegal},
  {_undoc, _illegal},

  // A0
  {_ldy, _immed},
  {_lda, _xind},
  {_ldx, _immed},
  {_undoc, _illegal},
  {_ldy, _zpg},
  {_lda, _zpg},
  {_ldx, _zpg},
  {_undoc, _illegal},
  {_tay, _impl},
  {_lda, _immed},
  {_tax, _impl},
  {_undoc, _illegal},
  {_ldy, _abs},
  {_lda, _abs},
  {_ldx, _abs},
  {_undoc, _illegal},

  // B0
  {_bcs, _rel},
  {_lda, _indy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_ldy, _zpgx},
  {_lda, _zpgx},
  {_ldx, _zpgy},
  {_undoc, _illegal},
  {_clv, _impl},
  {_lda, _absy},
  {_tsx, _impl},
  {_undoc, _illegal},
  {_ldy, _absx},
  {_lda, _absx},
  {_ldx, _absy},
  {_undoc, _illegal},

  // C0
  {_cpy, _immed},
  {_cmp, _xind},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_cpy, _zpg},
  {_cmp, _zpg},
  {_dec, _zpg},
  {_undoc, _illegal},
  {_iny, _impl},
  {_cmp, _immed},
  {_dex, _impl},
  {_undoc, _illegal},
  {_cpy, _abs},
  {_cmp, _abs},
  {_dec, _abs},
  {_undoc, _illegal},

  // D0
  {_bne, _rel},
  {_cmp, _indy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_cmp, _zpgx},
  {_dec, _zpgx},
  {_undoc, _illegal},
  {_cld, _impl},
  {_cmp, _absy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_cmp, _absx},
  {_dec, _absx},
  {_undoc, _illegal},

  // E0
  {_cpx, _immed},
  {_sbc, _xind},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_cpx, _zpg},
  {_sbc, _zpg},
  {_inc, _zpg},
  {_undoc, _illegal},
  {_inx, _impl},
  {_sbc, _immed},
  {_nop, _impl},
  {_undoc, _illegal},
  {_cpx, _abs},
  {_sbc, _abs},
  {_inc, _abs},
  {_undoc, _illegal},

  // F0
  {_beq, _rel},
  {_sbc, _indy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_sbc, _zpgx},
  {_inc, _zpgx},
  {_undoc, _illegal},
  {_sed, _impl},
  {_sbc, _absy},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_undoc, _illegal},
  {_sbc, _absx},
  {_inc, _absx},
  {_undoc, _illegal}
};

void EngineAtari::usage() {
  printf("CPU == 'atari'\n");
  printf("  --label-file=<label file>\n");
  printf("\n");
}

void EngineAtari::initialise() {
  int numArgs = args->getArgC(Args::argument);
  const int req = Args::requires_argument;
  const int reqNum = Args::requires_argument | Args::numeric_argument;
  bool verbose;
  char labFile[MAXSTR];
  char cpuStr[MAXSTR];

  if (numArgs != 1) {
    Utils::abortf("Just one rom file expected\n");
  }

  parseopt_t mandatoryArgs[] = {
    {"cpu",        req,    cpuStr, 'c'},
    {"rom-start",  reqNum, NULL,   'b'}, 
    {"rom-size",   reqNum, NULL,   's'},
    {NULL,         0,      NULL,   0}
  }; 
 
  parseopt_t optionalArgs[] = {
    {"label-file", req, labFile,   'l'},
    {"help",       0,   NULL,      '?'},
    {"verbose",    0,   &verbose,  'v'},
    {NULL,         0,   NULL,      0}
  };

  setByteDirective("fcb");
  setWordDirective("fdb");

  try {
    args->parseArgs(mandatoryArgs, optionalArgs, true);

    if (args->hasArg("label-file")) {
      labels->readFile(labFile);
    }
  }
  catch (CommandLineException e) {
    Utils::abortf("Bad command line.\n");
  }

  mem->setLittleEndian();

  readVector(RESETVec, "Reset");
  readVector(NMIVec,   "NMI");
  readVector(IRQVec,   "IRQ");

  mem->setType(IRQVec, Memory::WORD, 3);
}

bool EngineAtari::canBranch(long addr) {
  int inst = mem->getByte(addr);
  EngineAtari::Opcode *op = &(codes[inst]);

  if ((op->mode == _abs) && ((op->code == _jsr) || (op->code == _jmp))) {
    return true;
  }
  else if (op->mode == _rel) {
    return true;
  }

  return false;
}

long EngineAtari::branchAddress(long addr) {
  int inst = mem->getByte(addr);
  long res = -1;
  EngineAtari::Opcode *op = &(codes[inst]);

  if ((op->mode == _abs) && ((op->code == _jsr) || (op->code == _jmp))) {
    res = mem->getWord(addr+1);
  }
  else if (op->mode == _rel) {
    long offset = mem->getByte(addr+1);
    long rel = offset;

    addr += 2;
    if (offset & 0x80) {
      rel = (~rel & 0xff) + 1;
      res = addr - rel;
    }
    else {
      res = addr + rel;
    }
  }

  return res;
}

bool EngineAtari::validCode(long addr) {
  int inst = mem->getByte(addr);

  if (codes[inst].code == _undoc) {
    return false;
  }

  return true;
}

int EngineAtari::codeSize(long addr) {
  int inst = mem->getByte(addr);

  switch (codes[inst].mode) {
  case _immed:
  case _rel:
  case _zpg:
  case _zpgx:
  case _zpgy:
  case _xind:
  case _indy:
    return 2;

  case _abs:
  case _absx:
  case _absy:
  case _ind:
    return 3;

  case _accum:
  case _impl:
    break;

  case _illegal:
    return -1;
  }

  return 1;
}

void EngineAtari::genOperand(Opcode *op, OutputItem *out) {
  long target;
  char label[MAXSTR];

  switch (op->mode) {
  case _zpg:
    target = fetch8Lab(label);
    out->setOperand("<%s", label);
    break;

  case _immed:
    out->setOperand("#$%02x", fetch8());
    break;

  case _abs:
    target = fetch16Lab(label);
    out->setOperand(label);
    break;

  case _absx:
    break;

  case _absy:
    break;

  case _accum:
    break;

  case _zpgx:
    break;

  case _zpgy:
    break;

  case _rel:
    break;

  case _ind:
    break;

  case _xind:
    break;

  case _indy:
    break;

  case _impl:
    break;
  }
}

int EngineAtari::disassemble(long addr) {
  EngineAtari::Opcode *op;
  int inst;
  long target;
  OutputItem out(labels);
  char label[MAXSTR];

  pc = addr = mem->maskAddress(addr);

  out.clear();
  out.setAddress(addr);
  out.addComment("%04X", addr);

  inst = fetch8();
  op = &(codes[inst]);
  out.setInstruction(mne[op->code]);

  switch (op->code) {
  case _adc:
    break;

  case _and:
    genOperand(op, &out);
    break;

  case _asl:
    break;

  case _bcc:
  case _bcs:
  case _beq:
  case _bmi:
  case _bne:
  case _bpl:
  case _bvc:
  case _bvs:
    {
      // All the branch instructions only have a single mode - relative
      long offset = fetch8();
      long rel = offset;

      if (offset & 0x80) {
	rel = (~rel & 0xff) + 1;
	target = pc - rel;
      }
      else {
	target = pc + rel;
      }

      if (labels->isLabel(target)) {
	labels->lookupLabel(target, label);
      }
      else {
	snprintf(label, MAXSTR-1, "L_%04x", target);
      }

      out.setOperand(label);
    }
    break;

  case _brk:
    out.setInstruction("swi");
    break;

  case _clc:
    break;

  case _cld:
    break;

  case _cli:
    break;

  case _clv:
    break;

  case _cmp:
    break;

  case _cpx:
    break;

  case _cpy:
    break;

  case _dec:
    break;

  case _dex:
    break;

  case _dey:
    break;

  case _eor:
    break;

  case _inc:
    break;

  case _inx:
    break;

  case _iny:
    break;

  case _jmp:
    break;

  case _jsr:
    break;

  case _lda:
    out.setInstruction("ldb");
    genOperand(op, &out);
    break;

  case _ldx:
    break;

  case _ldy:
    break;

  case _lsr:
    break;

  case _nop:
    break;

  case _ora:
    break;

  case _pha:
    break;

  case _php:
    break;

  case _pla:
    break;

  case _plp:
    break;

  case _rol:
    break;

  case _ror:
    break;

  case _rti:
    break;

  case _sbc:
    break;

  case _sec:
    break;

  case _sed:
    break;

  case _sei:
    break;

  case _sta:
    break;

  case _stx:
    break;

  case _sty:
    break;

  case _tax:
    break;

  case _tay:
    break;

  case _tsx:
    break;

  case _txa:
    out.render(NULL, "tfr", "x,d", NULL);
    out.setInstruction("tstb");
    break;

  case _txs:
    break;

  case _tya:
    out.setInstruction("tfr");
    out.setOperand("y,d");
    out.render();
    out.setInstruction("tstb");
    break;

  default:
    out.setInstruction("BADOP");
  }

  out.render();
  return pc-addr;
}

