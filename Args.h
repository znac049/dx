#ifndef _ARGS_H_
#define _ARGS_H_

#include <vector>

typedef struct Option {
  char *option;
  char *valStr;
  int optType;
  int flags;
} option_t;

class Args {
 private:
  std::vector<option_t *> options;

 protected:
 public:
  enum argType {short_switch, long_switch, argument};
  enum flags {inverted=1};

 private:
  const char *getFlagStr(option_t *opt);
  int argIndex(const char *arg, int argType);
  int argIndex(const char *longArg);
  int argIndex(const char shortArg);
  void pairShortArg(char argCh, bool required);

 protected:
 public:
  Args(int argc, char **argv);

  void dump();

  void pairShortArgs(const char *shortArgStr);
};

#endif
