#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

const char *Engine6502::mne[] = {
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

struct Engine6502::Opcode Engine6502::codes[] = {
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

void Engine6502::usage() {
  printf("CPU == '6502'\n");
  printf("  --label-file=<label file>\n");
  printf("\n");
}

void Engine6502::initialise() {
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

  try {
    args->parseArgs(mandatoryArgs, optionalArgs, true);

    if (args->hasArg("label-file")) {
      labels->readFile(labFile);
    }
  }
  catch (CommandLineException e) {
    Utils::abortf("Bad command line.\n");
  }

  // Read the rom image
  mem->setEndian(false);

  readVector(RESETVec, "Reset");
  readVector(NMIVec,   "NMI");
  readVector(IRQVec,   "IRQ");

  mem->setType(IRQVec, Memory::WORD, 3);
}

int Engine6502::disassembleAsBytes(OutputItem *out, long addr, int count) {
  char bytes[MAXSTR];
  char *cp = bytes;
  int max = MAXSTR-1;
  int i;

  bytes[0] = EOS;

  for (i=0; i<count; i++) {
    snprintf(cp, max, "$%02x,", mem->getByte(addr + i));
    max -= 4;
    cp += 4;
  }

  max = strlen(bytes);
  if (max) {
    bytes[max-1] = EOS;
  }

  out->setInstruction("fcb");
  out->setOperand(bytes);
  mem->setType(addr, Memory::BYTE, count);

  return count;
}

int Engine6502::disassemble(long addr, OutputItem *out) {
  int instruction;
  Engine6502::Opcode *opcode;
  int immVal;
  int inst;
  char label[MAXSTR];
  long target;
  char regName;

  //printf("in 6502 disassemble\n");
  pc = addr = mem->maskAddress(addr);

  out->clear();
  out->setAddress(addr);

  if (!mem->isValidAddress(addr)) {
    Utils::abortf("disassemble() - Address $%x out of range.", addr);
  }

#if 0
  if (labels->isLabel(pc)) {
    labels->lookupLabel(pc, label);
  }
#endif

  inst = fetch8();
  opcode = &(codes[inst]);

  instruction = opcode->code;

  if (instruction == _undoc) {
    printf("Illegal!\n");
    return -disassembleAsBytes(out, addr, pc - addr);
  }

  // If we've got this far, we have a valid instruction, yippee!
  out->setInstruction(mne[instruction]);

  switch (opcode->mode) {
  case _immed:
    out->setOperand("#$%02x", fetch8());
    break;

  case _abs:
    target = fetch16Lab(label);
    out->setOperand("%s", label);

    if ((instruction == _jsr) || (instruction == _jmp)) {
      stackAddress(target);
      labels->createLabel(NULL, target);

      if (instruction == _jmp) {
	return -mem->setType(addr, Memory::CODE, pc-addr);
      }
    }
    break;

  case _absx:
    target = fetch16Lab(label);
    out->setOperand("%s,X", label);
    break;

  case _absy:
    target = fetch16Lab(label);
    out->setOperand("%s,Y", label);
    break;

  case _accum:
    out->setOperand("A");
    break;

  case _zpg:
    target = fetch8Lab(label);
    out->setOperand("%s", label);
    break;

  case _zpgx:
    target = fetch8Lab(label);
    out->setOperand("%s,X", label);
    break;

  case _zpgy:
    target = fetch8Lab(label);
    out->setOperand("%s,Y", label);
    break;

  case _rel:
    {
      long offset = fetch8();
      long rel = offset & 0x7f;
      char dir = (offset & 0x80)?'-':'+';

      if (offset & 0x80) {
	rel++;
	target = pc - rel;
      }
      else {
	target = pc + rel;
      }

      //printf("PC=%04x, Offset=%08x (%d), rel=%c%d, target=%04x\n", pc, offset, offset, dir, rel, target);

      if (labels->isLabel(target)) {
	labels->lookupLabel(target, label);
      }
      else {
	snprintf(label, MAXSTR-1, "L_%04x", target);
      }

      out->setOperand("%s", label);
    }
    break;

  case _ind:
    target = fetch16Lab(label);
    out->setOperand("(%s)", label);
    break;

  case _xind:
    printf("NOT IMPLEMENTED!\n");
    break;

  case _indy:
    printf("NOT IMPLEMENTED!\n");
    break;

  case _impl:
    // Special cases: RTS and RTI
    if ((instruction == _rts) || (instruction == _rti)) {
      return -mem->setType(addr, Memory::CODE, pc-addr);
    }
    break;
  }

  out->setType(Memory::CODE);
  //printf("addr=%04x, pc=%04x, delta=%d\n", addr, pc, pc-addr);
  return mem->setType(addr, Memory::CODE, pc-addr);
}

