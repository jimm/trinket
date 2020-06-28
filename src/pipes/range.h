#ifndef RANGE_H
#define RANGE_H

#include "../pipe.h"

class Range : public Pipe {
public:
  int low;
  int high;
  bool keep_in_range;           // if true, keep b/w low high; if false, reject

  Range(sqlite3_int64 id = UNDEFINED_ID);

  void process(byte status, byte data1, byte data2, byte data3);
};

#endif /* RANGE_H */
