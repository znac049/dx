#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

#define BITCH(n, val) (((1<<n)&val)?'1':'0')

void EngineDVG::initialise() {
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

  printf("\n");

  switch (op) {
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
    {
      int inst2 = fetch16();
      int y = (inst & 0x3f);
      int x = (inst2 & 0x3f);
      int z = (inst2>>12) & 0x0f;
      char ysign = (inst & 0x40)?'+':'-';
      char xsign = (inst & 0x40)?'+':'-';
      int shift = 9 - op;

      printf("%c%c%c%c %c %c %c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));

      printf("%c%c%c%c %c %c %c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst2), BITCH(14, inst2), BITCH(13, inst2), BITCH(12, inst2),
	     BITCH(11, inst2), BITCH(10, inst2), BITCH(9, inst2), BITCH(8, inst2),
	     BITCH(7, inst2), BITCH(6, inst2), BITCH(5, inst2), BITCH(4, inst2),
	     BITCH(3, inst2), BITCH(2, inst2), BITCH(1, inst2), BITCH(0, inst2));

      out->setInstruction("VCTR%d", op);
      out->setOperand("%c%d,%c%d,%d", xsign, x, ysign, y, z);
    }
    break;

  case 0xa:
    {
      int inst2 = fetch16();
      int y = (inst & 0x3f);
      int x = (inst2 & 0x3f);
      int sf = (inst2>>12) & 0x0f;
      char ysign = (inst & 0x40)?'+':'-';
      char xsign = (inst & 0x40)?'+':'-';
      int shift = 9 - op;

      printf("%c%c%c%c %c %c %c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));

      printf("%c%c%c%c %c %c %c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst2), BITCH(14, inst2), BITCH(13, inst2), BITCH(12, inst2),
	     BITCH(11, inst2), BITCH(10, inst2), BITCH(9, inst2), BITCH(8, inst2),
	     BITCH(7, inst2), BITCH(6, inst2), BITCH(5, inst2), BITCH(4, inst2),
	     BITCH(3, inst2), BITCH(2, inst2), BITCH(1, inst2), BITCH(0, inst2));

      out->setInstruction("LABS");
      out->setOperand("%c%d,%c%d,%d", xsign, x, ysign, y, sf);
    }
    break;

  case 0xb:
      printf("%c%c%c%c     %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));

    out->setInstruction("HALT");
    break;

  case 0xc:
    {
      int dest = inst & 0x0fff;

      printf("%c%c%c%c     %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));

      out->setInstruction("JSRL");
      out->setOperand("$%04x", dest);
    }
    break;

  case 0xd:
      printf("%c%c%c%c     %c%c%c%c%c%c%c%c%c%c%c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));

    out->setInstruction("RTSL");
    break;

  case 0xe:
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

  case 0xf:
    {
      int y = (inst & 0x03);
      int x = (inst & 0x30);
      int sf = ((inst>>3) & 1) | ((inst>>10) & 2) ;
      char ysign = (inst & 0x04)?'+':'-';
      char xsign = (inst & 0x40)?'+':'-';

      printf("%c%c%c%c   %c %c %c%c %c%c%c%c %c %c %c%c\n", 
	     BITCH(15, inst), BITCH(14, inst), BITCH(13, inst), BITCH(12, inst),
	     BITCH(11, inst), BITCH(10, inst), BITCH(9, inst), BITCH(8, inst),
	     BITCH(7, inst), BITCH(6, inst), BITCH(5, inst), BITCH(4, inst),
	     BITCH(3, inst), BITCH(2, inst), BITCH(1, inst), BITCH(0, inst));

      out->setInstruction("SVEC");
    }
    break;
  }

  return mem->setType(addr, Memory::CODE, pc-addr);
}

