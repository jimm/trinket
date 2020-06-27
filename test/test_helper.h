#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include "../src/pipe.h"

#define ADD_TEST_SINK(p) ((p)->downstream = new TestSinkPipe())
#define REMOVE_TEST_SINK(p) { delete (p)->downstream; (p)->downstream = nullptr; }
#define TEST_SINK(p) ((TestSinkPipe *)((p)->downstream))
#define CLEAR_TEST_SINK(p) TEST_SINK(p)->clear()

class TestSinkPipe : public Pipe {
public:
  int num_io_bytes;
  byte io_bytes[MIDI_BUFSIZ];

  TestSinkPipe();

  void process(byte status, byte data1, byte data2, byte data3);

  int num_messages() { return num_io_bytes / 4; }
  bool has_messages(int n) { return n == (num_io_bytes / 4); }
  bool empty() { return num_io_bytes == 0; }
  bool message_equals(int msg_num, byte status, byte data1, byte data2, byte data3);
  bool message_equals(int msg_num, byte *bytes);

  void clear() { num_io_bytes = 0; }
};

#endif /* TEST_HELPER_H */