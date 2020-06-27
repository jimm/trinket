#include "consts.h"
#include "trinket.h"
#include "pipe.h"

Pipe::Pipe(sqlite3_int64 id, string name)
  : DBObj(id), Named(name), upstream(nullptr), downstream(nullptr)
{
}

void Pipe::process(byte status, byte data1, byte data2, byte data3) {
  downstream->process(status, data1, data2, data3);
}

void Pipe::insert_between(Pipe *up, Pipe *down) {
  if (up != nullptr)
    up->downstream = this;
  if (down != nullptr)
    down->upstream = this;
  upstream = up;
  downstream = down;
}

void Pipe::insert_before(Pipe *down) {
  insert_between(down->upstream, down);
}

void Pipe::insert_after(Pipe *up) {
  insert_between(up, up->downstream);
}

// Reconnects upstream and downstream pipes and disconnects this pipe from
// them.
void Pipe::remove() {
  if (upstream != nullptr)
    upstream->downstream = downstream;
  if (downstream != nullptr)
    downstream->upstream = upstream;

  upstream = nullptr;
  downstream = nullptr;
}
