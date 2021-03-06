#ifndef MIDI_MONITOR_H
#define MIDI_MONITOR_H

#include <portmidi.h>

class InputInstrument;
class OutputInstrument;

// An abstract class that defines two public methods for monitoring input
// and output MIDI messages.
class MIDIMonitor {
public:
  virtual ~MIDIMonitor() {}

  virtual void monitor_input(InputInstrument *input, PmMessage msg) {}
  virtual void monitor_output(OutputInstrument *output, PmMessage msg) {}
};

#endif /* MIDI_MONITOR_H */
