#ifndef FAN_H
#define FAN_H

#include <vector>
#include "../pipe.h"

class Fan : public Pipe {
public:
  vector<Pipe *>downstreams;

  Fan(sqlite3_int64 id = UNDEFINED_ID);

  void process(byte status, byte data1, byte data2, byte data3);

  void insert_between(Pipe *upstream, Pipe *downstream);
  void remove();
};

#endif /* FAN_H */
