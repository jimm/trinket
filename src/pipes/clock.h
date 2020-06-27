#ifndef CLOCK_H
#define CLOCK_H

#include <pthread.h>
#include "../pipe.h"

class Clock : public Pipe {
public:
  int running;
  long microsecs_per_tick;
  long prev_beat_sent_at;

  Clock(sqlite3_int64 id = UNDEFINED_ID);
  ~Clock();

  int bpm() { return _bpm; }
  void set_bpm(int bpm);

  void start();
  void stop();
  void tick();

  void process(byte status, byte data1, byte data2, byte data3);

protected:
  int _bpm;
  pthread_t thread;
};

#endif /* CLOCK_H */
