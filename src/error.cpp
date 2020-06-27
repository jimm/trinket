#include "error.h"
#include "wx/app.h"

void error_message(const char * const msg) {
  fprintf(stderr, "%s\n", msg);
}
