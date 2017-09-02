#ifndef _BDA_H_
#define _BDA_H_

#define MAXSTR 512

#define MAX_BYTES_PER_LINE 8
#define MAX_WORDS_PER_LINE 4

#define YES true
#define NO false

#define CONTINUE_CHAR '\\'
#define EOS '\0'

#include "Exceptions.h"
#include "MemoryCell.h"
#include "Memory.h"
#include "Utils.h"
#include "Args.h"
#include "Label.h"
#include "Labels.h"
#include "OutputItem.h"
#include "DXEngine.h"
#include "Engine6502.h"
#include "EngineX09.h"
#include "EngineDVG.h"

enum memoryType {
  MEM_BYTE, MEM_CODE, MEM_WORD, MEM_EMPTY, MEM_UNKNOWN
};

typedef unsigned char byte_t;
typedef unsigned short word_t;
typedef unsigned int dword_t;
typedef unsigned long address_t;

typedef enum memoryType memoryType_t;

struct LABEL {
  unsigned short address;
  char *name;
  struct LABEL *next;
};

typedef struct LABEL label_t;

struct OUTPUTITEM {
  char inst[MAXSTR];
  char comment[MAXSTR];
  char label[MAXSTR];
  address_t address;
  int nBytes;
};

typedef struct OUTPUTITEM outputItem_t;

#endif
