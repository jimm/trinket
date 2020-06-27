#ifndef RANGE_H
#define RANGE_H

#include "../pipe.h"

class Range : public Pipe {
public:
  int low;
  int high;

  Range(sqlite3_int64 id = UNDEFINED_ID);

  void process(byte status, byte data1, byte data2, byte data3);
};

#endif /* RANGE_H */
