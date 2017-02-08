#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <exception>

using namespace std;

class DXException: public exception {
 private:
  char reason[MAXSTR];
  
 public:
  DXException() 
    : exception() {
    strcpy(reason, "DXException of some sort");
  };
  
  virtual const DXException *reasonf(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vsnprintf(reason, MAXSTR-1, fmt, args);
    va_end(args);

    return this;
  }

  virtual const char* what() const throw() {
    return reason;
  }
};

class RangeException: public DXException {
 public:
  RangeException() {
    reasonf("Out of range exception");
  }
};

class ConversionException: public DXException {
 public:
  ConversionException() {
    reasonf("Conversion exception");
  }
};

class CommandLineException: public DXException {
 public:
  CommandLineException() {
    reasonf("Bad command line exception");
  }
};



#endif
