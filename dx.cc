#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

#if 0
#define max(a,b) ((a>b)?a:b)

void set_starting_address(address_t addr, address_t vector, char *lab) {
  char vecLab[MAXSTR];

  if (verbose) {
    printf("set_starting_address($%04x, %d, '%s')\n", addr, vector, lab);
  }

  if (addr == 0xffff) {
    // read the address from the vector (if we have vector table in memory
    if (get_memory_type(vector) == MEM_EMPTY) {
      return;
    }

    addr = get_word(vector);

    snprintf(vecLab, MAXSTR-1, "%sVector", lab);
    create_label(vecLab, vector);
  }

  stack_address(addr);
  create_label(lab, addr);
}

void set_starting_point() {
  set_starting_address(reset_entrypoint, RESET_VEC, "Reset");
  set_starting_address(nmi_entrypoint, NMI_VEC, "NMI");
  set_starting_address(swi_entrypoint, SWI_VEC, "SWI");
  set_starting_address(irq_entrypoint, IRQ_VEC, "IRQ");
  set_starting_address(firq_entrypoint, FIRQ_VEC, "FIRQ");
  set_starting_address(swi2_entrypoint, SWI2_VEC, "SWI2");
  set_starting_address(swi3_entrypoint, SWI3_VEC, "SWI3");

  memory_is_word(SWI3_VEC, 7);
}

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
      nBytes = disassemble(addr, &inst, YES);
      while (nBytes > 0) {
	addr += nBytes;
	nBytes = disassemble(addr, &inst, YES);
      }
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

  parseopt_t mandatoryArgs[] = {
    {"cpu",        Args::requires_argument,                          cpuStr, 'c'},
    {"rom-start",  Args::requires_argument | Args::numeric_argument, &romStart, 'b'}, 
    {"rom-size",   Args::requires_argument | Args::numeric_argument, &romSize, 's'},
    {NULL,         0,                                                NULL, 0}
  }; 
 
  parseopt_t optionalArgs[] = {
    {"help",     0, &verbose,  '?' },
    {"verbose",  0, NULL,      'v' },
    {NULL,       0, NULL,      0   }
  };


#if 0
  parse_args(argc, argv);
   
  init_memory();
  if (read_file(rom_file, rom_start) == NO) {
    fprintf(stderr, "Problem reading ROM file '%s'\n", rom_file);
    exit(1);
  }

  read_label_file(label_file);

  pass1();
  generate_listing();
#endif

  try {
    DXEngine *engine = NULL;

    args.parseArgs(mandatoryArgs, optionalArgs, false);

    if (strcmp(cpuStr, "6809") == 0) {
      engine = (DXEngine *)new EngineX09(&args, romStart, romEnd);
    }

    engine->initialise();
  }
  catch (exception e) {
    printf("Trouble parsing command line.\n");
  }

  return 0;
}
