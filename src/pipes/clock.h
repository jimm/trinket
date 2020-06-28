#ifndef CLOCK_H
#define CLOCK_H

#include <pthread.h>
#include "../pipe.h"

class Clock : public Pipe {
public:
  long nanosecs_per_tick;

  Clock(sqlite3_int64 id = UNDEFINED_ID);
  ~Clock();

  float bpm() { return _bpm; }
  void set_bpm(float bpm);

  void start();
  void stop();
  long tick();
  bool is_running() { return thread != nullptr; }

  void process(byte status, byte data1, byte data2, byte data3);

protected:
  float _bpm;
  pthread_t thread;
};

#endif /* CLOCK_H */
