#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

#define BITCH(n, val) (((1<<n)&val)?'1':'0')

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

  for (int i=0; i < NUM_DVG_OPS; i++) {
    printf("%01x: %02x\n", i, opMap[i]);
  }

  mem->setEndian(true);

  printf("Atari DVG engine ready.\n");
  stackAddress(0);
}

int EngineDVG::disassemble(long addr, OutputItem *out) {
  int instruction;
  int *opcode;
  int immVal;
  int inst;
  int op;
  char label[MAXSTR];
  long target;
  char regName;

  pc = addr;

  out->clear();
  out->setType(Memory::CODE);
  out->setAddress(addr);

  if (!mem->isValidAddress(addr)) {
    Utils::abortf("disassemble() - Address $%x out of range.", addr);
  }

  if (labels->isLabel(pc)) {
    labels->lookupLabel(pc, label);
  }

  inst = fetch16();
  op = (inst>>12) & 0x0f;
  printf("OP=%d\n", op);
  op = opMap[op];
  printf("OP=%d\n", op);

  switch (op) {
  case DVG_OP_VLDRAW:
    {
      int inst2 = fetch16();
      int y = (inst & 0x0fff);
      int x = (inst2 & 0x0fff);
      int intensity = (inst2>>12) & 0x0f;

      printf("%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));

      printf("%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst2), BITCH(14, inst2), BITCH(13, inst2), BITCH(12, inst2),
	     BITCH(11, inst2), BITCH(10, inst2), BITCH(9, inst2), BITCH(8, inst2),
	     BITCH(7, inst2), BITCH(6, inst2), BITCH(5, inst2), BITCH(4, inst2),
	     BITCH(3, inst2), BITCH(2, inst2), BITCH(1, inst2), BITCH(0, inst2));

      out->setInstruction("vldraw");
      out->setOperand("%d,%d,%d", x, y, intensity);
    }
    break;

  case DVG_OP_VSCALED_DRAW:
    {
      int inst2 = fetch16();
      int y = (inst & 0x0fff);
      int x = (inst2 & 0x0fff);
      int scale = (inst2>>12) & 0x0f;

      printf("%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));

      printf("%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst2), BITCH(14, inst2), BITCH(13, inst2), BITCH(12, inst2),
	     BITCH(11, inst2), BITCH(10, inst2), BITCH(9, inst2), BITCH(8, inst2),
	     BITCH(7, inst2), BITCH(6, inst2), BITCH(5, inst2), BITCH(4, inst2),
	     BITCH(3, inst2), BITCH(2, inst2), BITCH(1, inst2), BITCH(0, inst2));

      out->setInstruction("vldraws%d", op);
      out->setOperand("%d,%d,%d", x, y, scale);
    }
    break;

  case DVG_OP_HALT:
    printf("%c%c%c%c     %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	   BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	   BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	   BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	   BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));
    
    out->setInstruction("HALT");
    break;

  case DVG_OP_VSDRAW:
    {
      int y = (inst>>8) & 0x0f;
      int x = (inst & 0x0f);
      int intensity = (inst >> 4) & 0x0f;

      printf("%c%c%c%c   %c%c%c%c %c%c%c%c %c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));

      out->setInstruction("vsdraw");
    }
    break;

  case DVG_OP_VSCALE:
    {
      int scale = (inst & 0x0fff);

      printf("%c%c%c%c   %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));
      out->setInstruction("vscale");
      out->setOperand("%d", scale);
    }
    break;

  case DVG_OP_VCOLOR:
    {
      int intensity = (inst & 0x00ff);
      int rgb = (inst>>8) & 0x03;

      printf("%c%c%c%c   %c %c%c%c %c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));
      out->setInstruction("vcolor");
      out->setOperand("%d,%d", rgb, intensity);
    }
    break;

  case DVG_OP_VCENTER:
      printf("%c%c%c%c   %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));
      out->setInstruction("vcenter");
    break;

  case DVG_OP_VJSR:
    {
      int dest = inst & 0x0fff;

      printf("%c%c%c%c     %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));

      out->setInstruction("vjsr");
      out->setOperand("$%04x", dest);
    }
    break;

  case DVG_OP_VRTS:
    printf("%c%c%c%c     %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	   BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	   BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	   BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	   BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));
    
    out->setInstruction("vrts");
    break;

  case DVG_OP_VJMP:
    {
      int dest = inst & 0x0fff;

      printf("%c%c%c%c     %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));

      out->setInstruction("JMPL");
      out->setOperand("$%04x", dest);
    }
    break;

  case DVG_OP_VMOVETO:
    {
      int inst2 = fetch16();
      int y = (inst & 0x0fff);
      int x = (inst2 & 0x0fff);

      printf("%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));

      printf("%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst2), BITCH(14, inst2), BITCH(13, inst2), BITCH(12, inst2),
	     BITCH(11, inst2), BITCH(10, inst2), BITCH(9, inst2), BITCH(8, inst2),
	     BITCH(7, inst2), BITCH(6, inst2), BITCH(5, inst2), BITCH(4, inst2),
	     BITCH(3, inst2), BITCH(2, inst2), BITCH(1, inst2), BITCH(0, inst2));

      out->setInstruction("vmove");
      out->setOperand("%d,%d", x, y);
    }
    break;

  default:
    out->setInstruction("???");
    break;
  }

  return mem->setType(addr, Memory::CODE, pc-addr);
}

