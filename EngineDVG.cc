#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

#define BITCH(n, val) (((1<<n)&val)?'1':'0')

char *EngineDVG::scales[] = {
  "???", "x2", "x4", "x8", 
    "x16", "x32", "x64", "x128",
    "???", "/128", "/64", "/32",
    "/16", "/8", "/4", "/2"
};

void EngineDVG::usage() {
  printf("CPU == 'dvg'\n");
  printf("  --game=<game name> (mandatory)\n");
  printf("  --label-file=<label file>\n");
  printf("\n");
}

void EngineDVG::initialise() {
  int numArgs = args->getArgC(Args::argument);
  const int req = Args::requires_argument;
  const int reqNum = Args::requires_argument | Args::numeric_argument;
  char labFile[MAXSTR];
  char gameName[MAXSTR];
  char cpuStr[MAXSTR];

  if (numArgs != 1) {
    Utils::abortf("Just one rom file expected\n");
  }

  parseopt_t mandatoryArgs[] = {
    {"cpu",        req,    cpuStr,   'c'},
    {"rom-start",  reqNum, NULL,     'b'}, 
    {"rom-size",   reqNum, NULL,     's'},
    {"game",       req,    gameName, 'g'},
    {NULL,         0,      NULL,     0}
  }; 
 
  parseopt_t optionalArgs[] = {
    {"label-file", req, labFile,     'l'},
    {"help",       0,   NULL,        '?'},
    {"verbose",    0,   &verbose,    'v'},
    {NULL,         0,   NULL,        0}
  };

  try {
    args->parseArgs(mandatoryArgs, optionalArgs, true);

    if (args->hasArg("label-file")) {
      labels->readFile(labFile);
    }

    printf("Game: %s\n", gameName);
  }
  catch (CommandLineException e) {
    Utils::abortf("Bad command line.\n");
  }

  for (int i=0; i < NUM_DVG_OPS; i++) {
    opMap[i] = DVG_OP_NONE;
  }

  if (strcasecmp(gameName, "asteroids") == 0) {
    opMap[0x8] = DVG_OP_VLDRAW;
    opMap[0x9] = DVG_OP_VSCALED_DRAW;
    opMap[0xa] = DVG_OP_VMOVETO;
    opMap[0xb] = DVG_OP_HALT;
    opMap[0xc] = DVG_OP_VJSR;
    opMap[0xd] = DVG_OP_VRTS;
    opMap[0xe] = DVG_OP_VJMP;
    opMap[0xf] = DVG_OP_VSDRAW;
  }
  else {
    Utils::abortf("Unknown game '%s'", gameName);
  }

  mem->setLittleEndian();

  stackAddress(0);
}

int EngineDVG::decode4(int word) {
  int res = word & 0x000f;

  if (res & 0x0008) {
    res = -(res & 0x0003);
  }

  return res;
}

int EngineDVG::decode12(int word) {
  int res = word & 0x0fff;

  if (res & 0x0800) {
    res = -(res & 0x07ff);
  }

  return res;
}

int EngineDVG::findRTSOp() {
  for (int i=0; i<NUM_DVG_OPS; i++) {
    if (opMap[i] == DVG_OP_VRTS) {
      return i<<12;
    }
  }

  return -1;
}

void EngineDVG::backup(long addr) {
  long nBytes;

  if (addr < romStart) {
    return;
  }

  nBytes = disassemble(addr);
  if (nBytes > 0) {
    // Ok so try and find instructions immediately before this one
    if (validCode(addr-2)) {
      backup(addr-2);
    }
    else if (validCode(addr-4)) {
      backup(addr-4);
    }
    else {
      return;
    }
  }
}

bool EngineDVG::canBranch(long addr) {
  int op = mem->getWord(addr);

  op = op>>12;
  if ((opMap[op] == DVG_OP_VJSR) || (opMap[op] == DVG_OP_VJMP)) {
    return true;
  }

  return false;
}

long EngineDVG::branchAddress(long addr) {
  int inst = mem->getWord(addr);

  return (inst & 0x0fff) * 2;
}

bool EngineDVG::validCode(long addr) {
  int op = mem->getWord(addr);

  op = op>>12;
  if (opMap[op] == DVG_OP_NONE) {
    return false;
  }

  return true;
}

int EngineDVG::codeSize(long addr) {
  int op = mem->getWord(addr);

  op = op>>12;
  switch (opMap[op]) {
  case DVG_OP_VCOLOR:
  case DVG_OP_VSCALE:
  case DVG_OP_VCENTER:
  case DVG_OP_VJSR:
  case DVG_OP_VRTS:
  case DVG_OP_VJMP:
  case DVG_OP_HALT:
  case DVG_OP_VSDRAW:
    return 2;

  case DVG_OP_VSCALED_DRAW:
  case DVG_OP_VMOVETO:
  case DVG_OP_VLDRAW:
    return 4;

  case DVG_OP_NONE:
    return -2;
  }
}

void EngineDVG::pass1() {
  long addr;
  int rts = findRTSOp();

  // Pass 1 - disassemble everything you can
  for (addr = romStart; addr < romEnd; addr += 2) {
    int op = mem->getWord(addr);

    if (op == rts) {
      backup(addr);
    }
  }
}

int EngineDVG::disassemble(long addr) {
  int instruction;
  int *opcode;
  int immVal;
  int inst;
  int op;
  char label[MAXSTR];
  long target;
  char regName;
  OutputItem out(labels);

  pc = addr = mem->maskAddress(addr);

  out.clear();
  out.setAddress(addr);

  inst = fetch16();

  op = (inst>>12) & 0x0f;
  op = opMap[op];

  switch (op) {
  case DVG_OP_VLDRAW:
    {
      int inst2 = fetch16();
      int y = decode12(inst);
      int x = decode12(inst2);
      int intensity = (inst2>>12) & 0x0f;

      out.addComment("%04X: %02X %02X %02X %02X", addr, inst>>8, inst & 0xff, inst2>>8, inst2 & 0xff);

      out.setInstruction("VEC");
      out.setOperand("x=%d,y=%d,i=%d", x, y, intensity);
    }
    break;

  case DVG_OP_VSCALED_DRAW:
    {
      int inst2 = fetch16();
      int y = decode12(inst);
      int x = decode12(inst2);
      int scale = (inst2>>12) & 0x0f;

      out.addComment("%04X: %02X %02X %02X %02X %s", addr, inst>>8, inst & 0xff, inst2>>8, inst2 & 0xff, scales[scale]);
      out.setInstruction("SSV");
      out.setOperand("x=%d,y=%d,s=%d", x, y, scale);
    }
    break;

  case DVG_OP_HALT:
    out.addComment("%04X: %02X %02X", addr, inst>>8, inst & 0xff);
    out.setInstruction("HALT");
    break;

  case DVG_OP_VSDRAW:
    {
      int y = decode4(inst>>8);
      int x = decode4(inst);
      int intensity = (inst >> 4) & 0x0f;

      out.addComment("%04X: %02X %02X", addr, inst>>8, inst & 0xff);
      out.setInstruction("SVEC");
      out.setOperand("x=%d,y=%d,i=%d", x, y, intensity);
    }
    break;

  case DVG_OP_VSCALE:
    {
      int scale = (inst & 0x0fff);

      out.addComment("%04X: %02X %02X", addr, inst>>8, inst & 0xff);
      out.setInstruction("SSC");
      out.setOperand("%d", scale);
    }
    break;

  case DVG_OP_VCOLOR:
    {
      int intensity = (inst & 0x00ff);
      int rgb = (inst>>8) & 0x03;

      out.addComment("%04X: %02X %02X", addr, inst>>8, inst & 0xff);
      out.setInstruction("SCOL");
      out.setOperand("%d,%d", rgb, intensity);
    }
    break;

  case DVG_OP_VCENTER:
    out.addComment("%02X %02X", addr, inst>>8, inst & 0xff);
      out.setInstruction("CNTR");
    break;

  case DVG_OP_VJSR:
    {
      int dest = inst & 0x0fff;

      out.addComment("%04X: %02X %02X", addr, inst>>8, inst & 0xff);
      out.setInstruction("JSR");
      out.setOperand("$%04x", dest);
      stackAddress(dest*2);
    }
    break;

  case DVG_OP_VRTS:
    out.addComment("%04X: %02X %02X", addr, inst>>8, inst & 0xff);
    out.setInstruction("RTS");
    break;

  case DVG_OP_VJMP:
    {
      int dest = inst & 0x0fff;

      out.addComment("%04X: %02X %02X", addr, inst>>8, inst & 0xff);
      out.setInstruction("JMP");
      out.setOperand("$%04x", dest);
      stackAddress(dest*2);
    }
    break;

  case DVG_OP_VMOVETO:
    {
      int inst2 = fetch16();
      int y = (inst & 0x0fff);
      int x = (inst2 & 0x0fff);

      out.addComment("%04X: %02X %02X", addr, inst>>8, inst & 0xff);
      out.setInstruction("MOVE");
      out.setOperand("%d,%d", x, y);
    }
    break;

  case DVG_OP_NONE:
  default:
    out.addComment("%04X: %02X %02X", addr, inst>>8, inst & 0xff);
    out.setInstruction("???");

    // Unlike many disassemblers, we assume that all of the
    // ROM image contains code
    stackAddress(pc);
    return -mem->setType(addr, Memory::BYTE, 2);
    break;
  }

  return mem->setType(addr, Memory::CODE, pc-addr);
}

