#include "../predicates.h"
#include "range.h"

Range::Range(sqlite3_int64 id)
  : Pipe(id, "Range"), low(0), high(127)
{
}

void Range::process(byte status, byte data1, byte data2, byte data3) {
  if (is_note(status)) {
    if (data1 < low || data1 > high)
      return;
  }

  Pipe::process(status, data1, data2, data3);
}
