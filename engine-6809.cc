#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "bda.h"

#include "inst-6809.inc"

static address_t pc;

static char label[MAXSTR];

extern int verbose;

static byte_t fetch8() {
  if (!valid_address(pc)) {
    abortf("fetch8() - Address out of range: $%x\n", pc);
  }

  return get_byte(pc++);
}

static word_t fetch16() {
  word_t val;

  if (!valid_address(pc)) {
    abortf("fetch16() - Address out of range: $%x\n", pc);
  }
  
  val = get_word(pc);
  pc += 2;

  return val;
}

static dword_t fetch32() {
  word_t val;

  if (!valid_address(pc)) {
    abortf("fetch32() - Address out of range: $%x\n", pc);
  }
  
  val = get_dword(pc);
  pc += 4;

  return val;
}

static address_t fetch8_label() {
  address_t b = (address_t) fetch8();

  lookup_direct_label(b, label, MAXSTR-1);

  return b;
}

static address_t fetch8_rlabel() {
  char offset = (char) fetch8();
  int target = (int)pc + offset;

  //commentf("SHORT REL: PC=$%04x, offset=%d, target=$%04x\n", pc, offset, target);
  lookup_direct_label(target, label, MAXSTR-1);

  return target;
}

static address_t fetch16_label() {
  address_t b = (address_t) fetch16();

  lookup_label(b, label, MAXSTR-1);

  return b;
}

static address_t fetch16_rlabel() {
  short int offset = (short int) fetch16();
  int target = (int)pc + offset;

  //commentf("LONG REL: PC=$%04x, offset=%d, target=$%04x\n", pc, offset, target);
  lookup_label(target, label, MAXSTR-1);

  return target;
}

static int da_reglist(char *buf, const char *mnem, opcode_t *opcode) {
  char regList[MAXSTR];
  byte_t b = fetch8();
  // TODO: reverse order of list for PULL vs PUSH

  regList[0] = '\0';

  if (b & 0x80) {
    strncat(regList, "pc,", MAXSTR-1);
  }

  if (b & 0x40) {
    strncat(regList, (opcode->mode == _usr_post) ? "s," : "u,", MAXSTR-1);
  }

  if (b & 0x20) {
    strncat(regList, "y,", MAXSTR-1);
  }
	
  if (b & 0x10) {
    strncat(regList, "x,", MAXSTR-1);
  }

  if (b & 0x08) {
    strncat(regList, "dp,", MAXSTR-1);
  }

  if ((b & 0x06) == 0x06) {
    strncat(regList, "d,", MAXSTR-1);
  }
  else {
    if (b & 0x04) {
      strncat(regList, "b,", MAXSTR-1);
    }

    if (b & 0x02) {
      strncat(regList, "a,", MAXSTR-1);
    }
  }

  if (b & 0x01) {
    strncat(regList, "cc,", MAXSTR-1);
  }

  regList[strlen(regList) - 1] = '\0';
  snprintf(buf, MAXSTR-1, "%s  %s", mnem, regList);

  // PULU or PULS and what we pull includes the PC, so 
  // stop disassembling.
  if (b & 0x80) {
    return 1;
  }

  return 0;
}

static void da_indexed(char *buf, const char *mnem, instCode_t instruction) {
  byte_t b = fetch8();
  char regName = index_reg[(b >> 5) & 0x3];
  address_t target;

  if ((b & 0x80) == 0) {
    snprintf(buf, MAXSTR-1, "%s  %s,%c", mnem, off4[instruction & 0x1f], regName);
    return;
  }

  switch (b & 0x1f) {
  case 0x00:
    snprintf(buf, MAXSTR-1, "%s  ,%c+", mnem, regName);
    break;

  case 0x01:
    snprintf(buf, MAXSTR-1, "%s  ,%c++", mnem, regName);
    break;

  case 0x02:
    snprintf(buf, MAXSTR-1, "%s  ,-%c", mnem, regName);
    break;

  case 0x03:
    snprintf(buf, MAXSTR-1, "%s  ,--%c", mnem, regName);
    break;

  case 0x04:
    snprintf(buf, MAXSTR-1, "%s  ,%c", mnem, regName);
    break;

  case 0x05:
    snprintf(buf, MAXSTR-1, "%s  b,%c", mnem, regName);
    break;

  case 0x06:
    snprintf(buf, MAXSTR-1, "%s  b,%c", mnem, regName);
    break;

  case 0x08:
    target = fetch8_label();
    snprintf(buf, MAXSTR-1, "%s  <$%s,%c", mnem, label, regName);
    break;

  case 0x09:
    target = fetch16_label();
    snprintf(buf, MAXSTR-1, "%s  $%s,%c", mnem, label, regName);
    break;

  case 0x0b:
    snprintf(buf, MAXSTR-1, "%s  d,%c", mnem, regName);
    break;

  case 0x0c:
    target = fetch8_rlabel();
    snprintf(buf, MAXSTR-1, "%s  %s,pcr", mnem, label);
    break;

  case 0x0d:
    target = fetch16_rlabel();
    snprintf(buf, MAXSTR-1, "%s  %s,pcr", mnem, label);
    break;

  case 0x11:
    snprintf(buf, MAXSTR-1, "%s  [,%c++]", mnem, regName);
    break;

  case 0x13:
    snprintf(buf, MAXSTR-1, "%s  [,--%c]", mnem, regName);
    break;

  case 0x14:
    snprintf(buf, MAXSTR-1, "%s  [,%c]", mnem, regName);
    break;

  case 0x15:
    snprintf(buf, MAXSTR-1, "%s  [b,%c]", mnem, regName);
    break;

  case 0x16:
    snprintf(buf, MAXSTR-1, "%s  [a,%c]", mnem, regName);
    break;

  case 0x18:
    target = fetch8_label();
    snprintf(buf, MAXSTR-1, "%s  [<%s,%c]", mnem, label, regName);
    break;

  case 0x19:
    target = fetch16_label();
    snprintf(buf, MAXSTR-1, "%s  [%s,%c]", mnem, label, regName);
    break;

  case 0x1b:
    snprintf(buf, MAXSTR-1, "%s  [d,%c]", mnem, regName);
    break;

  case 0x1c:
    target = fetch8_rlabel();
    snprintf(buf, MAXSTR-1, "%s  [<%s,pcr]", mnem, label);
    break;

  case 0x1d:
    target = fetch8_rlabel();
    snprintf(buf, MAXSTR-1, "%s  [%s,pcr]", mnem, label);
    break;

  case 0x1f:
    target = fetch16_label();
    snprintf(buf, MAXSTR-1, "%s  [%s]", mnem, label);
    break;

  default:
    snprintf(buf, MAXSTR-1, "%s  ???", mnem);
    break;
  }
}

int da_bytes(outputItem_t *oi, address_t addr, int count) {
  char bytes[MAXSTR];
  char *cp = bytes;
  int max = MAXSTR-1;
  int i;

  bytes[0] = EOS;

  for (i=0; i<count; i++) {
    snprintf(cp, max, "$%02x,", get_byte(addr + i));
    max -= 4;
    cp += 4;
  }

  max = strlen(bytes);
  if (max) {
    bytes[max-1] = EOS;
  }

  snprintf(oi->inst, MAXSTR-1, "fcb  %s", bytes);

  memory_is_byte(addr, count);

  return count;
}

int disassemble(address_t addr, outputItem_t *res, int pass1) {
  instCode_t instruction;
  byte_t immVal;
  byte_t inst;
  opcode_t *opcode;
  char *buf = res->inst;
  char mnem[MAXSTR];
  address_t target;
  char regName;
  memoryType_t mType = get_memory_type(addr);

  pc = addr;

  clear_output_item(res);
  res->address = pc;

  if (!valid_address(pc)) {
    abortf("disassemble() - Address $%x out of range.", pc);
  }

  //printf("da @ $%04x\n", pc);

  if (is_label(pc)) {
    lookup_label(pc, res->label, MAXSTR-1);
  }

  inst = fetch8();

  /* Is it a two byte instruction? All two byte instructions start
   * with 0x10 or 0x11 */

  if (inst == 0x10) {
    inst = fetch8();
    opcode = &codes10[inst];
  }
  else if (inst == 0x11) {
    inst = fetch8();
    opcode = &codes11[inst];
  }
  else {
    opcode = &codes[inst];
  }

  instruction = opcode->code;

  if (instruction == _illegal) {
    return -da_bytes(res, addr, pc - addr);
  }

  // If we've got this far, we have a valid instruction, yippee!
  sprintf(mnem, "%-4s", mne[instruction]);

  // This will likely get overwritten...
  snprintf(buf, MAXSTR-1, "%s", mnem);

  switch (opcode->mode) {
  case _implied:
    // Special cases: RTS and RTI
    if ((instruction == _rts) || (instruction == _rti)) {
      return -memory_is_code(addr, pc-addr);
    }
    break;

  case _imm_byte:
    snprintf(buf, MAXSTR-1, "%s  #$%02x", mnem, fetch8());
    break;

  case _imm_word:
    snprintf(buf, MAXSTR-1, "%s  #$%04x", mnem, fetch16());
    break;

  case _direct:
    target = fetch8_label();

    if ((instruction == _jsr) || (instruction == _jmp)) {
      //commentf("%s at $%04x - stack target address: <$%02x\n", mnem, addr, target);
      stack_address(target);
      create_label(NULL, target);
    }

    snprintf(buf, MAXSTR-1, "%s  <%s", mnem, label);
    break;

  case _extended:
    target = fetch16_label();

    if ((instruction == _jsr) || (instruction == _jmp)) {
      //commentf("%s at $%04x - stack target address: $%04x\n", mnem, addr, target);
      stack_address(target);
      create_label(NULL, target);
    }

    snprintf(buf, MAXSTR-1, "%s  %s", mnem, label);
    break;

  case _indexed:
    da_indexed(buf, mnem, instruction);
    break;

  case _rel_byte:
    target = fetch8_rlabel();
    //commentf("%s at $%04x - stack target PCR address (byte offset): $%04x\n", mnem, addr, target);
    stack_address(target);
    snprintf(buf, MAXSTR-1, "%s  %s", mnem, label);

    if (instruction == _bra) {
      return -memory_is_code(addr, pc-addr);
    }
    break;

  case _rel_word:
    target = fetch16_rlabel();
    //commentf("%s at $%04x - stack target PCR address (word offset): $%04x\n", mnem, addr, target);
    stack_address(target);
    snprintf(buf, MAXSTR-1, "%s  %s", mnem, label);

    if (instruction == _lbra) {
      return -memory_is_code(addr, pc-addr);
    }
    break;

  case _reg_post:
    {
      byte_t b = get_byte(pc++);
      snprintf(buf, MAXSTR-1, "%s  %s,%s", mnem, reg[b >> 4], reg[b & 0x0f]);
    }
    break;

  case _usr_post:
  case _sys_post:
    if (da_reglist(buf, mnem, opcode)) {
      return -memory_is_code(addr, pc-addr);
    }
    break;

#ifdef H6309
  case _imm_direct:
    immVal = fetch8();
    target = fetch8_label();
    snprintf(buf, MAXSTR-1, "%s  #$%02x,<%s", mnem, immVal, label);
    break;

  case _imm_quad:
    {
      dword_t quadVal = fetch32();
      snprintf(buf, MAXSTR-1, "%s  #$%08x", mnem, quadVal);
    }
    break;

  case _reg_reg:
    {
      unsigned regs = fetch8();
      unsigned r1 = (regs & 0xf0) >> 4;
      unsigned r2 = regs & 0x0f;

      snprintf(buf, MAXSTR-1, "%s  %s,%s", mnem, reg[r1], reg[r2]);
    }
    break;

  case _single_bit:
    {
      unsigned bits = fetch8();
      unsigned regbit = bits & 0x07;
      unsigned srcbit = (bits >> 3) & 0x07;
      unsigned regnum = (bits >> 6) & 0x03;
      static char *reg_name[4] = {"CC", "A", "B", "???"};

      target = fetch8_label();
      snprintf(buf, MAXSTR-1, "%s  %s.%d,%s.%d", mnem, reg_name[regnum], regbit, label, srcbit);
    }
    break;

  case _blk_move:
    {
      unsigned regs = fetch8();
      unsigned src_reg = (regs >> 4) & 0x0f;
      unsigned dst_reg = regs & 0x0f;
      char *src_op = "+";
      char *dst_op = "+";

      if (instruction == 0x39) {
	src_op = dst_op = "-";
      }
      else if (instruction == 0x3a) {
	dst_op = "";
      }
      else if (instruction == 0x3b) {
	src_op = "";
      }

      snprintf(buf, MAXSTR-1, "%s  (%s%s,%s%s)", mnem, reg[src_reg], src_op, reg[dst_reg], dst_op);
    }
    break;
#endif
  }

  return memory_is_code(addr, pc-addr);
}

