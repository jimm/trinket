#include "../predicates.h"
#include "xpose.h"

Xpose::Xpose(sqlite3_int64 id)
  : Pipe(id, "Transpose"), xpose(0)
{
}

void Xpose::process(byte status, byte data1, byte data2, byte data3) {
  if (is_note(status))
    data1 += xpose;
  Pipe::process(status, data1, data2, data3);
}
