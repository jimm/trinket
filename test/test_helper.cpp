#include "test_helper.h"

TestSinkPipe::TestSinkPipe()
  : Pipe(UNDEFINED_ID, "TestSinkPipe"), num_io_bytes(0)
{
}

void TestSinkPipe::process(byte status, byte data1, byte data2, byte data3) {
  io_bytes[num_io_bytes++] = status;
  io_bytes[num_io_bytes++] = data1;
  io_bytes[num_io_bytes++] = data2;
  io_bytes[num_io_bytes++] = data3;
}

bool TestSinkPipe::message_equals(int msg_num, byte status, byte data1, byte data2, byte data3) {
  int i = msg_num * 4;
  return io_bytes[i++] == status &&
    io_bytes[i++] == data1 &&
    io_bytes[i++] == data2 &&
    io_bytes[i] == data3;
}

bool TestSinkPipe::message_equals(int msg_num, byte *bytes) {
  return message_equals(msg_num, bytes[0], bytes[1], bytes[2], bytes[3]);
}
