#include <sys/time.h>
#include "../predicates.h"
#include "clock.h"

// 10 milliseconds, in nanoseconds
#define SLEEP_NANOSECS 10000000L

void *clock_send_thread(void *clock_ptr) {
  struct timespec rqtp = {0, SLEEP_NANOSECS};
  Clock *clock = (Clock *)clock_ptr;

  while (clock->running) {
    clock->tick();
    if (nanosleep(&rqtp, nullptr) == -1)
      return nullptr;
  }
  return nullptr;
}

Clock::Clock(sqlite3_int64 id)
  : Pipe(id, "Transpose"), running(false), thread(nullptr)
{
  set_bpm(120);
  start();
}

Clock::~Clock() {
  if (running)
    stop();
}

void Clock::set_bpm(int new_val) {
  _bpm = new_val;
  microsecs_per_tick = 2500000L / (long)_bpm;
}

void Clock::start() {
  if (running)
    return;
  prev_beat_sent_at = 0L;
  int status = pthread_create(&thread, 0, clock_send_thread, this);
  running = true;
}

void Clock::stop() {
  running = false;
}

void Clock::tick() {
  if (!running)
    return;

  struct timeval tp;
  struct timezone tzp;
  int status = gettimeofday(&tp, &tzp);
  if (status != 0)
    return;

  long now_msecs = (tp.tv_sec * 1000L) + tp.tv_usec;
  if ((now_msecs - prev_beat_sent_at) >= microsecs_per_tick) {
    downstream->process(CLOCK, 0, 0, 0);
    prev_beat_sent_at = now_msecs;
  }
}

void Clock::process(byte status, byte data1, byte data2, byte data3) {
  if (status == START || status == CONTINUE)
    start();
  if (status == STOP)
    stop();
  Pipe::process(status, data1, data2, data3);
}
