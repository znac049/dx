#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <getopt.h>

#include "dx.h"

#if 0
int verbose = NO;

char rom_file[MAXSTR];
char label_file[MAXSTR];

address_t rom_start = 0xfff0;
address_t rom_end = 0xffff;

byte_t byteStack[MAX_BYTES_PER_LINE];
int byteSP = 0;
address_t byteAddr = 0;

word_t wordStack[MAX_WORDS_PER_LINE];
int wordSP = 0;
address_t wordAddr = 0;

static struct option long_options[] = {
  
  {"label-file",  required_argument,  NULL,  'l' },
  {"rom-start",   required_argument,  NULL,  'b' },
  {"rom-size",    required_argument,  NULL,  's' },
  {"help",        no_argument,        NULL,  '?' },
  {"verbose",     no_argument,        NULL,  'v' },
  {NULL,          0,                  NULL,  0   }
};

static char *short_options = "l:b:s:hv";

struct UsageMessage {
  char *opt;
  char *help_msg;
};

static struct UsageMessage usage_messages[] = {
  {"l", "Load label file"},
  {"b", "Specify ROM start address"},
  {"s", "Specify ROM size"},
  {"v", "Be verbose"},
  {"?", "Show this help message"},
  {NULL, NULL}
};

static char program_name[MAXSTR];

#define max(a,b) ((a>b)?a:b)

struct option *find_longopt(const char *optName)
{
  struct option *opt = long_options;
  int len = strlen(optName);


  while (opt->name) {
    if (strcmp(optName, opt->name) == 0) {
      return opt;
    }

    if ((len == 1) && (optName[0] == opt->val)) {
      return opt;
    }

    opt++;
  }

  return NULL;
}

void usage() {
  char options[MAXSTR];
  struct UsageMessage *msg = usage_messages;
  struct option *opt;
  int longest = 0;
  char fmt[MAXSTR];

  printf("\nUsage: %s [ <args> ] <rom file>\n\n", program_name);

  while (msg->opt != NULL) {
    opt = find_longopt(msg->opt);
    if (opt != NULL) {
      if ((opt->val > ' ') && (opt->val < 127)) {
	snprintf(options, MAXSTR-1, "--%s | -%c", opt->name, opt->val);
      } 
      else {
	snprintf(options, MAXSTR-1, "--%s", opt->name);
      }  
    }
    else {
      if (strlen(msg->opt) == 1) {
	snprintf(options, MAXSTR-1, "-%s", opt->name);
      }
      else {
	snprintf(options, MAXSTR-1, "--%s", opt->name);
      }
    }

    if (opt) {
      int len = strlen(options);
      char *cp = &options[len];
      
      len = MAXSTR - len;

      switch (opt->has_arg) {
      case no_argument:
	break;

      case required_argument:
	strncpy(cp, " <value>", len-1);
	break;
	
      case optional_argument:
	strncpy(cp, " [ <value> ]", len-1);
	break;

      default:
	strncpy(cp, " ???", len-1);
	break;
      }
    }

    printf("  %-31s %s\n", options, msg->help_msg);

    msg++;
  }

  printf("\n");
}

void parse_args(int argc, char *argv[]) {
  int opt = 0;
  int long_index = 0;
  int rom_size = 2048;

  strncpy(program_name, argv[0], MAXSTR-1);

  strcpy(rom_file, "");
  strcpy(label_file, "");

  while ((opt = getopt_long(argc, argv, short_options, long_options, &long_index )) != -1) {
    switch (opt) {
    case 'b':
      rom_start = parse_address(optarg);
      break;

    case 's':
      rom_size = parse_address(optarg);
      break;

    case 'v':
      verbose = YES;
      break;

    case '?':
    default: 
      usage(); 
      exit(1);
    }
  }

  /* There should be just one arg left, the name of the ROM file */
  if ((optind+1) != argc) {
    fprintf(stderr, "ROM file name missing.\n");
    usage();
    exit(1);
  }

  rom_end = rom_start + rom_size - 1;
  if (rom_end > K64) {
    fprintf(stderr, "Check rom start and size as it appears to go beyond the\n");
    fprintf(stderr, "end of memory: %04x - %04d\n", rom_start, rom_end);
    exit(1);
  }

  if (label_file[0]) {
    /* Make sure the label file specified actually exists */
    if (!is_file(label_file)) {
      fprintf(stderr, "Label file '%s'not found or is not a regular file.\n", label_file);
      exit(1);
    }
  }

  strncpy(rom_file, argv[argc-1], MAXSTR-1);

  if (verbose) {
    printf("; Command line parsed ok:\n");
    printf(";     rom base: %04x\n", rom_start);
    printf(";      rom end: %04x\n", rom_end);
    printf(";  RESET entry: %04x\n", reset_entrypoint);
    printf(";    NMI entry: %04x\n", nmi_entrypoint);
    printf(";    SWI entry: %04x\n", swi_entrypoint);
    printf(";    IRQ entry: %04x\n", irq_entrypoint);
    printf(";   FIRQ entry: %04x\n", firq_entrypoint);
    printf(";   SWI2 entry: %04x\n", swi2_entrypoint);
    printf(";   SWI3 entry: %04x\n", swi3_entrypoint);
    printf(";      verbose: %s\n", (verbose==YES)?"YES":"NO");
    printf(";     ROM file: %s\n", rom_file);
    printf(";   Label file: %s\n", label_file[0]?label_file:"*None*");
    puts(";\n");
  }
}

void clear_output_item(outputItem_t *oi) {
  strcpy(oi->label, "");
  strcpy(oi->inst, "");
  strcpy(oi->comment, "");

  oi->address = 0;
}

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

  args.dump();

  args.pairShortArgs("vf:c::d");
  args.dump();

  return 0;
}
