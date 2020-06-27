#ifndef XFORM_H
#define XFORM_H

#include "../pipe.h"

enum XformFrom {
  XFF_FROM_NOTE_ON_VALUE,
  XFF_FROM_NOTE_ON_VELOCITY,
  XFF_FROM_CC,
  XFF_FROM_PC,
  XFF_FROM_CHAN_PRESS,
  XFF_FROM_START,
  XFF_FROM_CONTINUE,
  XFF_FROM_STOP
};

enum XformTo {
  XFF_TO_CC,
  XFF_TO_PC,
  XFF_TO_CHAN_PRESS,
  XFF_TO_START,
  XFF_TO_CONTINUE,
  XFF_TO_STOP
};

class Xform : public Pipe {
public:
  XformFrom from;
  XformTo to;
  byte to_controller_num;

  Xform(sqlite3_int64 id = UNDEFINED_ID);

  void process(byte status, byte data1, byte data2, byte data3);
};

#endif /* XFORM_H */
