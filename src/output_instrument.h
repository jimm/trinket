#ifndef OUTPUT_INSTRUMENT_H
#define OUTPUT_INSTRUMENT_H

#include "instrument.h"

class OutputInstrument : public Instrument {
public:
  OutputInstrument(sqlite3_int64 id, PmDeviceID device_id, const char *device_name, const char *name = nullptr);

  void write(byte status, byte data1, byte data2, byte data3);
  void write(PmEvent *buf, int len);

protected:
  virtual bool start_midi();
};

#endif /* OUTPUT_INSTRUMENT_H */
