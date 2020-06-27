#include "input.h"

Input::Input(sqlite3_int64 id)
  : Pipe(id, "Input"), input_instrument(nullptr)
{
}

Input::~Input() {
  remove_from_input_instrument();
}

void Input::set_input_instrument(InputInstrument *instrument) {
  remove_from_input_instrument();
  input_instrument = instrument;
  instrument->pipe = this;
}

void Input::remove_from_input_instrument() {
  if (input_instrument != nullptr) {
    input_instrument->pipe = nullptr;
    input_instrument = nullptr;
  }
}
