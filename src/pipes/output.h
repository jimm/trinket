#ifndef OUTPUT_PIPE_H
#define OUTPUT_PIPE_H

#include "../pipe.h"
#include "../output_instrument.h"

class Output : public Pipe {
public:
  OutputInstrument *output_instrument;

  Output(sqlite3_int64 id = UNDEFINED_ID);
  virtual ~Output();

  void set_output_instrument(OutputInstrument *instrument);
  void remove_from_output_instrument();

  // We send output to an InputInstrument, not a downstream pipe.
  bool can_have_output() { return false; }

  void process(byte status, byte data1, byte data2, byte data3);
};

#endif /* OUTPUT_PIPE_H */
