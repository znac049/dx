#ifndef _LABEL_H_
#define _LABEL_H_

class Label {
 private:
  char *name;
  long address;

 protected:
 public:

 private:
 protected:
 public:
  Label();
  Label(const char *labName);
  Label(const char *labName, long addr);

  void setName(const char *labName);
  const char *getName();

  void setAddress(long addr);
  long getAddress();
};

#endif
