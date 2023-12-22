#include <stdlib.h>
#include <string.h>
#include <portmidi.h>
#include "error.h"
#include "output_instrument.h"

OutputInstrument::OutputInstrument(sqlite3_int64 id, PmDeviceID device_id, const char *device_name, const char *name)
  : Instrument(id, device_id, device_name, name)
{
}

bool OutputInstrument::start_midi() {
  PmError err = Pm_OpenOutput(&stream, device_id, 0, 128, 0, 0, 0);
  if (err == 0)
    return true;

  char buf[BUFSIZ];
  snprintf(buf, BUFSIZ, "error opening output stream %s: %s\n", name.c_str(),
          Pm_GetErrorText(err));
  error_message(buf);
  return false;
}

void OutputInstrument::write(byte status, byte data1, byte data2, byte data3) {
  PmEvent event = {
    Pm_Message(status, data1, data2) + ((unsigned int)data3 << 24),
    0
  };
  write(&event, 1);
}

void OutputInstrument::write(PmEvent *buf, int len) {
  if (real_port()) {
    if (enabled) {
      PmError err = Pm_Write(stream, buf, len);
      if (err != 0) {
        char err_msg_buf[BUFSIZ];
        snprintf(err_msg_buf, BUFSIZ, "error writing MIDI to %s: %s\n",
                name.c_str(), Pm_GetErrorText(err));
        error_message(err_msg_buf);
        for (int i = 0; i < len; ++i)
          fprintf(stderr, "msg %d\t%08x\n", i,buf[i].message);
      }
    }
  }
  else {
    for (int i = 0; i < len && num_io_messages < MIDI_BUFSIZ-1; ++i)
      io_messages[num_io_messages++] = buf[i].message;
  }

  if (enabled && midi_monitor != nullptr)
    for (int i = 0; i < len && num_io_messages < MIDI_BUFSIZ-1; ++i)
      midi_monitor->monitor_output(this, buf[i].message);
}
