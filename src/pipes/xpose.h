#ifndef XPOSE_H
#define XPOSE_H

#include "../pipe.h"

class Xpose : public Pipe {
public:
  int xpose;

  Xpose(sqlite3_int64 id = UNDEFINED_ID);

  void process(byte status, byte data1, byte data2, byte data3);
};

#endif /* XPOSE_H */
