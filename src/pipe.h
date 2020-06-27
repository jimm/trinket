#ifndef PIPE_H
#define PIPE_H

#include <portmidi.h>
#include "consts.h"
#include "db_obj.h"
#include "named.h"

typedef unsigned char byte;

class Pipe : public DBObj, public Named {
public:
  Pipe *upstream;
  Pipe *downstream;

  Pipe(sqlite3_int64 id = UNDEFINED_ID, string name = "Pipe");

  virtual void process(byte status, byte data1, byte data2, byte data3);

  // Return true if this Pipe can accept messages from upstream.
  virtual bool can_have_input() { return true; }

  // Return true if this Pipe passes messages downstream.
  virtual bool can_have_output() { return true; }

  virtual void insert_between(Pipe *upstream, Pipe *downstream);
  void insert_before(Pipe *downstream);
  void insert_after(Pipe *upstream);

  // Reconnects upstream and downstream pipes and disconnects this pipe from
  // them.
  virtual void remove();
};

#endif /* PIPE_H */
