#ifndef INPUT_INSTRUMENT_H
#define INPUT_INSTRUMENT_H

#include <vector>
#include <queue>
#include <mutex>
#include <pthread.h>
#include <portmidi.h>
#include "consts.h"
#include "instrument.h"

using namespace std;

class Pipe;

class InputInstrument : public Instrument {
public:
  bool running;

  InputInstrument(sqlite3_int64 id, PmDeviceID device_id, const char *device_name, const char *name = nullptr);

  void start();
  void stop();

  void enqueue(PmEvent *, int);
  void read(PmMessage);
  PmMessage message_from_read_queue();
  void stop_read_thread();

protected:
  virtual bool start_midi();

protected:
  queue<PmMessage> message_queue;
  mutex message_queue_mutex;
  pthread_t read_pthread;
};

#endif /* INPUT_INSTRUMENT_H */
