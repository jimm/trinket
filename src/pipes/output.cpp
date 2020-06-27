#include "output.h"

Output::Output(sqlite3_int64 id)
  : Pipe(id, "Output"), output_instrument(nullptr)
{
}

Output::~Output() {
  remove_from_output_instrument();
}

void Output::process(byte status, byte data1, byte data2, byte data3) {
  if (output_instrument != nullptr)
    output_instrument->write(status, data1, data2, data3);
}

void Output::set_output_instrument(OutputInstrument *instrument) {
  remove_from_output_instrument();
  output_instrument = instrument;
  instrument->pipe = this;
}

void Output::remove_from_output_instrument() {
  if (output_instrument != nullptr) {
    output_instrument->pipe = nullptr;
    output_instrument = nullptr;
  }
}
