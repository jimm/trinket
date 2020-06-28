#include <sys/time.h>
#include "clock.h"

void *clock_send_thread(void *clock_ptr) {
  struct timespec rqtp = {0, 0L};
  Clock *clock = (Clock *)clock_ptr;

  while (clock->is_running()) {
    rqtp.tv_nsec = clock->tick();
    if (nanosleep(&rqtp, nullptr) == -1)
      return nullptr;
  }
  return nullptr;
}

Clock::Clock(sqlite3_int64 id)
  : Pipe(id, "Transpose"), thread(nullptr)
{
  set_bpm(120);
}

Clock::~Clock() {
  if (is_running())
    stop();
}

void Clock::set_bpm(float new_val) {
  _bpm = new_val;
  nanosecs_per_tick = (long)(2.5e9 / _bpm);
}

void Clock::start() {
  if (is_running())
    return;
  int status = pthread_create(&thread, 0, clock_send_thread, this);
}

void Clock::stop() {
  thread = nullptr;
}

// Sends CLOCK message downstream and returns the amount of time to wait
// until the next tick, in nanoseconds.
long Clock::tick() {
  struct timeval tp;
  struct timezone tzp;

  gettimeofday(&tp, &tzp);
  long start_msecs = (tp.tv_sec * 1000L) + tp.tv_usec;

  downstream->process(CLOCK, 0, 0, 0);

  gettimeofday(&tp, &tzp);
  long end_msecs = (tp.tv_sec * 1000L) + tp.tv_usec;

  return nanosecs_per_tick - (end_msecs - start_msecs);
}

void Clock::process(byte status, byte data1, byte data2, byte data3) {
  if (status == START || status == CONTINUE)
    start();
  if (status == STOP)
    stop();
  Pipe::process(status, data1, data2, data3);
}
