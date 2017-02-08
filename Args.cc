#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dx.h"

Args::Args(int argc, char **argv) {
  int i = 1;
  option_t *opt;

  printf("ArgC=%d, Args:\n", argc);

  while (i < argc) {
    if (strncmp(argv[i], "--", 2) == 0) {
      char arg[MAXSTR];
      char *eq;
      int flags = 0;
      
      opt = new option_t();
      strcpy(arg, argv[i]);

      eq = strchr(arg, '=');
      
      if (eq) {
	*eq++ = EOS;
	opt->valStr = strdup(eq);
      }
      else {
	opt->valStr = NULL;
      }

      if (strncmp(arg, "--no-", 5) == 0) {
	opt->option = strdup(&arg[5]);
	flags |= inverted;
      }
      else {
	opt->option = strdup(&arg[2]);
      }
      opt->optType = long_switch;
      opt->flags = flags;

      options.push_back(opt);
    }
    else if (argv[i][0] == '-') {
      int len = strlen(argv[i]);
      char tmp[2];

      tmp[1] = EOS;

      for (int j=1; j<len; j++) {
	tmp[0] = argv[i][j];

	opt = new option_t();

	opt->option = strdup(tmp);
	opt->valStr = NULL;
	opt->optType = short_switch;
	opt->flags = 0;

	options.push_back(opt);
      }
    }
    else {
      opt = new option_t();

      opt->option = strdup(argv[i]);
      opt->valStr = NULL;
      opt->optType = argument;
      opt->flags = 0;

      options.push_back(opt);
    }

    i++;
  }
}

const char *Args::getFlagStr(option_t *opt) {
  static char flags[MAXSTR];
  char typeCh = '?';
  char iFlag = '-';

  switch (opt->optType) {
  case short_switch:
    typeCh = 'S';
    break;

  case long_switch:
    typeCh = 'L';
    break;

  case argument:
    typeCh = 'A';
    break;
  }

  if (opt->flags & inverted) {
    iFlag = 'i';
  }

  snprintf(flags, MAXSTR-1, "%c%c", typeCh, iFlag);

  return flags;
}

void Args::dump() {
  printf("Args:\n");

  for (int i=0; i<options.size(); i++) {
    option_t *opt = options.at(i);

    printf("  %2d: %s '%s'", i, getFlagStr(opt), opt->option);
    if (opt->valStr != NULL) {
      printf(" = '%s'", opt->valStr);
    }
    printf("\n");
  }
}

void Args::pairShortArg(char argCh, bool required) {
  option_t *opt;
  int optInd = argIndex(argCh);

  printf("Short arg '%c' %s have an argument\n", argCh, required?"must":"may");
  printf("  index=%d\n", optInd);

  if (optInd == -1) {
    return;
  }

  opt = options.at(optInd);
  if (opt->valStr != NULL) {
    // already has one
    return;
  }

  for (int i=optInd+1; i<options.size(); i++) {
    option_t *arg = options.at(i);

    printf("  does '%s' belong to it?\n", arg->option);

    if (arg->optType == long_switch) {
      if (required) {
	throw CommandLineException().reasonf("Missing required argument.");
      }

      return;
    }

    if (arg->optType == argument) {
      // We're in business
      opt->valStr = arg->option;
      options.erase(options.begin()+i);

      return;
    }
  }
}

void Args::pairShortArgs(const char *shortArgStr) {
  const char *cp = shortArgStr;

  while (*cp) {
    bool required;

    if (cp[1] == ':') {
      required = (cp[2] != ':');

      pairShortArg(*cp, required);

      if (!required) {
	cp++;
      }
      cp++;
    }
    
    cp++;
  }
}

int Args::argIndex(const char *arg, int argType) {
  option_t *opt;

  //printf("argIndex('%s', %d)\n", arg, argType);

  for (int i=0; i<options.size(); i++) {
    opt = options.at(i);

    if ((opt->optType == argType) && (strcmp(opt->option, arg) == 0)) {
      return i;
    }
  }

  return -1;
}

int Args::argIndex(const char *longArg) {
  return argIndex(longArg, long_switch);
}

int Args::argIndex(const char shortArg) {
  char longArg[2];

  longArg[0] = shortArg;
  longArg[1] = EOS;

  return argIndex(longArg, short_switch);
}
