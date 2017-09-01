#ifndef _OUTPUT_ITEM_LIST_H_
#define _OUTPUT_ITEM_LIST_H_

#include <vector>

class OutputItemList {
 private:
  std::vector<char *> comments;
  std::vector<OutputItem *> items;
  Labels *labs;

 public:
  OutputItemList(Labels *l);

  void clear();
  void render();

  void addItem(OutputItem *item);

  void addComment(const char *fmt, ...);
};

#endif
