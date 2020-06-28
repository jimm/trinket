#include "fan.h"

Fan::Fan(sqlite3_int64 id)
  : Pipe(id, "Fan")
{
}

void Fan::process(byte status, byte data1, byte data2, byte data3) {
  for (auto &downstream : downstreams)
    downstream->process(status, data1, data2, data3);
}

void Fan::insert_between(Pipe *up, Pipe *down) {
  if (up != nullptr)
    up->downstream = this;
  if (down != nullptr)
    down->upstream = this;
  upstream = up;
  downstreams.push_back(down);
}

// Connects upstream to our first downstream (if any) and disconnects this
// pipe from its upstream and downstream pipes.
void Fan::remove() {
  Pipe *first_downstream = downstreams.empty() ? nullptr : downstreams[0];
  if (upstream != nullptr)
    upstream->downstream = first_downstream;
  if (first_downstream != nullptr)
    first_downstream->upstream = upstream;

  upstream = nullptr;
  downstreams.clear();
}
