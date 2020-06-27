#include "../predicates.h"
#include "filter.h"

Filter::Filter(sqlite3_int64 id)
  : Pipe(id, "Filter")
{
  for (int i = 0; i <= FS_SYSTEM_RESET; ++i)
    filters[i] = false;
}

void Filter::process(byte status, byte data1, byte data2, byte data3) {
  int filter_index = (status >> 4) - 8;
  if (filter_index == 7)
    filter_index = status - 0xf0 + FS_SYSEX;
  if (filters[filter_index])
    return;

  Pipe::process(status, data1, data2, data3);
}
