#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dx.h"

Labels::Labels(long start, long end) {
  romStart = start;
  romEnd = end;
}

void Labels::exportLabels() {
  int numLabels = labels.size();

  printf("\n; Labels:\n;\n");

  for (int i=0; i<numLabels; i++) {
    Label *lab = labels.at(i);
    long addr = lab->getAddress();

    if ((addr < romStart) || (addr > romEnd)) {
      if (lab->getName() == NULL) {
	char l[MAXSTR];

	snprintf(l, MAXSTR-1, "L%04x", addr);
	printf("%-21s = $%04x\n", l, addr);
      }
      else {
	printf("%-21s = $%04x\n", lab->getName(), addr);
      }
    }
  }

  printf("\n");
}

void Labels::createLabel(const char *lab, long addr) {
  Label *label = new Label(lab, addr);

  labels.push_back(label);
}

bool Labels::isLabel(long addr) {
  int nLabels = labels.size();

  for (int i=0; i<nLabels; i++) {
    Label *lab = labels.at(i);

    if (lab->getAddress() == addr) {
      return true;
    }
  }

  return false;
}

void Labels::lookupLabel(long addr, char *labStr, size_t labLen, int nDigits) {
  Label *lab = findLabel(addr);
  char fmt[MAXSTR];

  strcpy(fmt, "L%04x");

  if (lab != NULL) {
    if (lab->getName() != NULL) {
      strncpy(labStr, lab->getName(), labLen);
    }
    else {
      snprintf(labStr, labLen, fmt, lab->getAddress());
    }
  }
  else {
    fmt[0] = '$';
    snprintf(labStr, labLen, fmt, addr);  
  }
}

Label *Labels::findLabel(long addr) {
  int numLabels = labels.size();

  for (int i=0; i<numLabels; i++) {
    Label *lab = labels.at(i);

    if (lab->getAddress() == addr) {
      return lab;
    }
  }

  return NULL;
}

void Labels::lookupLabel(long addr, char *labStr) {
  return lookupLabel(addr, labStr, MAXSTR-1, 4);
}

void Labels::lookupShortLabel(long addr, char *labStr) {
  return lookupLabel(addr, labStr, MAXSTR-1, 2);
}

void Labels::processLine(char *line) {
  char *eq = strchr(line, '=');
  char *lab = line;
  char *val;

  if (eq != NULL) {
    long addr;

    *eq++ = EOS;
    val = eq;
    Utils::trim(lab);
    Utils::trim(val);

    if (strncmp(lab, "Symbol: ", 8) == 0) {
      // massage lwasm map entry
      lab += 8;

      eq = strchr(lab, ' ');
      if (eq != NULL) {
	*eq = EOS;
      }
      Utils::trim(lab);

      sprintf(val, "$%04x", Utils::hex2int(val));
    }

    addr = Utils::parseAddress(val);
    createLabel(lab, addr);
  }
  else {
    if (strcmp(line, "") != 0) {
      printf("; Crappy line in label file: '%s'\n", line);
    }
  }
}

int Labels::readFile(const char *fileName) {
  int numLabels = 0;
  FILE *fd = fopen(fileName, "r");
  char line[MAXSTR + 2]; // This is horrible, but necessary!

  if (!fd) {
    return -1;
  }

  while (fgets(line, MAXSTR-1, fd) != NULL) {
    Utils::truncStr(line, '\n');
    Utils::truncStr(line, ';');

    processLine(line);
  }

  fclose(fd);

  return numLabels;
}
