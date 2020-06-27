#ifndef INPUT_PIPE_H
#define INPUT_PIPE_H

#include "../pipe.h"
#include "../input_instrument.h"

class Input : public Pipe {
public:
  InputInstrument *input_instrument;

  Input(sqlite3_int64 id = UNDEFINED_ID);
  virtual ~Input();

  void set_input_instrument(InputInstrument *instrument);
  void remove_from_input_instrument();

  // We get input from an InputInstrument, not an upstream pipe.
  bool can_have_input() { return false; }
};

#endif /* INPUT_PIPE_H */
