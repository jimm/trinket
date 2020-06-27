#ifndef XPOSE_H
#define XPOSE_H

#include "../pipe.h"

#define CHAN_REMAP_FILTER (-1)

class ChanRemap : public Pipe {
public:
  int mappings[16];             // CHAN_REMAP_FILTER means filter out

  ChanRemap(sqlite3_int64 id = UNDEFINED_ID);

  void process(byte status, byte data1, byte data2, byte data3);
};

#endif /* XPOSE_H */
