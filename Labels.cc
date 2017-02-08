#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "bda.h"

extern int verbose;
extern address_t rom_start;
extern address_t rom_end;

label_t *LabelList = NULL;

void export_labels() {
  label_t *lab = LabelList;

  printf("; Labels:\n;\n");

  while (lab != NULL) {
    if ((lab->address < rom_start) || (lab->address > rom_end)) {
      if (lab->name == NULL) {
	char l[MAXSTR];
	snprintf(l, MAXSTR-1, "L%04x", lab->address);
	printf("%-21s = $%04x\n", l, lab->address);
      }
      else {
	printf("%-21s = $%04x\n", lab->name, lab->address);
      }
    }

    lab = lab->next;
  }

  printf("\n");
}

void dump_labels() {
  label_t *lab = LabelList;

  if (LabelList == NULL) {
    if (verbose) {
      printf("; No labels\n\n");
    }

    return;
  }

  printf("; Labels:\n;\n");

  while (lab != NULL) {
    if ((lab->address < 0x6000) || (lab->address > 0x7fff)) {
      if (lab->name == NULL) {
	char l[MAXSTR];
	snprintf(l, MAXSTR-1, "L%04x", lab->address);
	printf("; %-21s = $%04x\n", l, lab->address);
      }
      else {
	printf("; %-21s = $%04x\n", lab->name, lab->address);
      }
    }

    lab = lab->next;
  }

  printf("\n");
}

int is_label(word_t addr) {
  label_t *lab = LabelList;

  while (lab != NULL) {
    if (lab->address == addr) {
      return 1;
    }

    lab = lab->next;
  }

  return 0;
}

void lookup_label_fmt(address_t addr, char *lab_str, size_t lab_len, const char *fmt) {
  label_t *lab = LabelList;

  while (lab != NULL) {
    if (lab->address == addr) {
      if (lab->name != NULL) {
	snprintf(lab_str, lab_len, "%s", lab->name);
      }
      else {
	snprintf(lab_str, lab_len, fmt, lab->address);
      }

      return;
    }

    lab = lab->next;
  }

  snprintf(lab_str, lab_len, "$%04X", addr);  
}

void lookup_label(address_t addr, char *lab_str, size_t lab_len) {
  return lookup_label_fmt(addr, lab_str, lab_len, "L%04x");
}

void lookup_direct_label(address_t addr, char *lab_str, size_t lab_len) {
  return lookup_label_fmt(addr, lab_str, lab_len, "L%02x");
}

void create_label(char *label, address_t addr) {
  label_t *lab = LabelList;

  if (verbose) {
    printf("; Add label: '%s' = $%04x\n", label, addr);
  }

  while (lab != NULL) {
    if (lab->address == addr) {
      if (label != NULL) {
	if (lab->name != NULL) {
	  free(lab->name);
	  lab->name = strdup(label);
	}
      }

      return;
    }

    lab = lab->next;
  }

  lab = malloc(sizeof(label_t));
  lab->address = addr;
  lab->name = label;
  if (label != NULL) {
    lab->name = strdup(label);
  }

  lab->next = LabelList;
  LabelList = lab;
}

void process_line(char *line) {
  char *eq = strchr(line, '=');
  char *lab = line;
  char *val;

  if (eq != NULL) {
    word_t addr;

    *eq++ = EOS;
    val = eq;
    trim(lab);
    trim(val);

    if (strncmp(lab, "Symbol: ", 8) == 0) {
      // lwasm map file
      lab += 8;

      eq = strchr(lab, ' ');
      if (eq != NULL) {
	*eq = EOS;
      }
      trim(lab);

      sprintf(val, "$%04x", hex2int(val, 0));
    }

    addr = parse_address(val);
    create_label(lab, addr);
  }
  else {
    if (strcmp(line, "") != 0) {
      printf("; Crappy line in label file: '%s'\n", line);
    }
  }
}

int read_label_file(const char *file_name) {
  int num_labels = 0;
  FILE *fd = fopen(file_name, "r");
  char line[MAXSTR + 2]; // This is horrible, but necessary!

  if (!fd) {
    return -1;
  }

  while (fgets(line, MAXSTR-1, fd) != NULL) {
    char *semi = strchr(line, ';');

    trunc_str(line, '\n');
    trunc_str(line, ';');

    process_line(line);
  }

  fclose(fd);

  return num_labels;
}
