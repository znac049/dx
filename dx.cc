#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

#if 0
#define max(a,b) ((a>b)?a:b)

void pass1() {
  address_t addr;
  int nBytes;
  outputItem_t inst;
  int i;

  set_starting_point();

  for (i = 0; i < get_address_stack_size(); i++) {
    addr = get_address_stack_at(i);

    if ((addr >= rom_start) && (addr <= rom_end)) {
      /* Disassemble each chunk until we hit an unknown instruction */
    }
  }
}

void push_byte(byte_t b, address_t addr) {
  if ( (byteSP >= MAX_BYTES_PER_LINE) || 
       (byteSP && ((addr % MAX_BYTES_PER_LINE) == 0)) ||
       (is_label(addr) && byteSP) ) {
    emit_bytes(&byteAddr, byteStack, &byteSP);
    byteAddr = addr;
  }

  if (byteSP == 0) {
    byteAddr = addr;
  }

  byteStack[byteSP++] = b;
}

void push_word(word_t w, address_t addr) {
  if ( (wordSP >= MAX_WORDS_PER_LINE) || 
       (wordSP && ((addr % MAX_WORDS_PER_LINE) == 0)) ||
       (is_label(addr) && wordSP) ) {
    emit_words(&wordAddr, wordStack, &wordSP);
    wordAddr = addr;
  }

  if (wordSP == 0) {
    wordAddr = addr;
  }

  wordStack[byteSP++] = w;
}

void emit_bytes(address_t *addr, byte_t *stack, int *sp) {
  char lab[MAXSTR];
  int i;
  int numBytes = *sp;

  if (is_label(*addr)) {
    lookup_label(*addr, lab, MAXSTR-1);
  }
  else {
    lab[0] = EOS;
  }

  printf("%-23s %-4s ", lab, "fcb");
  for (i=0; i<numBytes; i++) {
    printf("$%02x", stack[i]);

    if ((i+1) < numBytes) {
      putchar(',');
    }
  }

  for (i=numBytes; i<MAX_BYTES_PER_LINE; i++) {
    printf("    ");
  }

  printf(" ; %04x  ", *addr);
  for (i=0; i<numBytes; i++) {
    putchar(printable_char(stack[i]));
  }
  putchar('\n');

  *addr = -1;
  *sp = 0;
}

void emit_words(address_t *addr, word_t *stack, int *sp) {
  char lab[MAXSTR];
  int i;
  int numWords = *sp;

  if (is_label(*addr)) {
    lookup_label(*addr, lab, MAXSTR-1);
  }
  else {
    lab[0] = EOS;
  }

  printf("%-23s %-4s ", lab, "fdb");
  for (i=0; i<numWords; i++) {
    printf("$%04x", stack[i]);

    if ((i+1) < numWords) {
      putchar(',');
    }
  }

  for (i=numWords; i<MAX_BYTES_PER_LINE; i++) {
    printf("      ");
  }

  printf(" ; %04x\n", *addr);

  *addr = -1;
  *sp = 0;
}

void generate_listing() {
  outputItem_t inst;
  address_t addr;
  int nBytes;
  int prevType = MEM_EMPTY;

  if (verbose) {
    dump_memory_info();
  }

  byteAddr = wordAddr = rom_start;

  export_labels();

  printf("\n%-23s org  $%04x\n\n", "", rom_start);

  for (addr = rom_start; addr <= rom_end;) {
    int memType = get_memory_type(addr);

    if (memType == MEM_UNKNOWN) {
      memType = MEM_BYTE;
    }

    /* We may have previous items (bytes/words) that haven't been emitted yet */
    if (prevType != memType) {
      switch (prevType) {
      case MEM_BYTE:
	emit_bytes(&byteAddr, byteStack, &byteSP);
	break;

      case MEM_WORD:
	emit_words(&wordAddr, wordStack, &wordSP);
	break;
      }

      printf("\n");
    }

    switch (memType) {
    case MEM_BYTE:
      //printf("byte @ $%04x\n", addr);
      push_byte(get_byte(addr), addr);
      nBytes = 1;
      break;

    case MEM_CODE:
      //printf("code @ $%04x\n", addr);
      if (is_entry_point(addr)) {
	printf("\n");
      }

      nBytes = disassemble(addr, &inst, NO);

      printf("%-23s %-20s                 ; %04X %s\n", inst.label, inst.inst, inst.address, inst.comment);
      break;

    case MEM_WORD:
      //printf("word @ $%04x\n", addr);
      push_word(get_word(addr), addr);
      nBytes = 2;
      break;

    case MEM_EMPTY:
      //printf("nowt @ $%04x\n", addr);
      nBytes = 1;
      break;
    }

    if (nBytes < 0) {
      nBytes = -nBytes;
    }

    if (is_label(addr)) {
      lookup_label(addr, inst.label, MAXSTR-1);
    }

    addr += nBytes;

    prevType = memType;
  }

  if (byteSP) {
    emit_bytes(&byteAddr, byteStack, &byteSP);
  }
  else if (wordSP) {
    emit_words(&wordAddr, wordStack, &wordSP);
  }

  if (verbose) {
    dump_labels();
  }
}
#endif 

int main(int argc, char *argv[]) {
  Args args(argc, argv);

  char cpuStr[MAXSTR];

  long romStart = 0xfff0;
  long romSize = 0;
  long romEnd = 0xffff;
  bool verbose = false;
  long addressMask = 0xffff;

  parseopt_t mandatoryArgs[] = {
    {"cpu",        Args::requires_argument,                          cpuStr, 'c'},
    {"rom-start",  Args::requires_argument | Args::numeric_argument, &romStart, 'b'}, 
    {"rom-size",   Args::requires_argument | Args::numeric_argument, &romSize, 's'},
    {NULL,         0,                                                NULL, 0}
  }; 
 
  parseopt_t optionalArgs[] = {
    {"address-mask",  Args::requires_argument | Args::numeric_argument, &addressMask, 'm'}, 
    {"help",          0, NULL,     0 },
    {"verbose",       0, &verbose, 'v' },
    {NULL,            0, NULL,     0   }
  };

  try {
    DXEngine *engine = NULL;
    int numArgs;
    option_t *arg;

    args.parseArgs(mandatoryArgs, optionalArgs, false);
    numArgs = args.getArgC(Args::argument);

    if (numArgs != 1) {
      Utils::abortf("Only one filename expected.\n");
    }

    romEnd = romStart + romSize;

    arg = args.getArg(0, Args::argument);

    if ((strcmp(cpuStr, "6809") == 0) || (strcmp(cpuStr, "6309") == 0) || (strcasecmp(cpuStr, "6x09") == 0)) {
      engine = (DXEngine *)new EngineX09(&args, romStart, romEnd, addressMask, arg->option);
    }
    else if (strcmp(cpuStr, "6502") == 0) {
      engine = (DXEngine *)new Engine6502(&args, romStart, romEnd, addressMask, arg->option);
    }
    else if (strcmp(cpuStr, "dvg") == 0) {
      engine = (DXEngine *)new EngineDVG(&args, romStart, romEnd, addressMask, arg->option);
    }
    else {
      printf("????????\n");
    }

    if (engine != NULL) {
      engine->initialise();
      engine->disassemble();
      //engine->dump();
    }
  }
  catch (exception e) {
    printf("Usage: dx <options> <file>\n\n");
    printf("Required options:\n");
    printf("  --cpu=<CPU string>\n");
    printf("  --rom-start=<address>\n");
    printf("  --rom-size=<size in bytes>\n");
    printf("  --address-mask=<mask>\n");

    printf("\nOptional options:\n");
    printf("  --verbose\n");
    printf("  --help\n");

    printf("\nCPU specific options:\n");

    EngineX09 *x09 = new EngineX09();
    x09->usage();

    Engine6502 *eng  = new Engine6502();
    eng->usage();

    EngineDVG *dvg = new EngineDVG();
    dvg->usage();
  }

  return 0;
}
