#include <math.h>
#include "../predicates.h"
#include "chan_remap.h"

ChanRemap::ChanRemap(sqlite3_int64 id)
  : Pipe(id, "Channel Remap")
{
  for (int i = 0; i < 16; ++i)
    mappings[i] = i;
}

void ChanRemap::process(byte status, byte data1, byte data2, byte data3) {
  if (!is_channel(status)) {
    Pipe::process(status, data1, data2, data3);
    return;
  }

  int new_chan = mappings[status & 0x0f];
  if (new_chan == CHAN_REMAP_FILTER)
    return;
  status = (status & 0xf0) + new_chan;
  Pipe::process(status, data1, data2, data3);
}
