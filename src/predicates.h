#ifndef PREDICATES_H
#define PREDICATES_H

#include "consts.h"

// These macros assume that `status` is really a status byte (that is, the
// high bit is set).

#define is_channel(status) ((status) < SYSEX)
#define is_note(status) (((status) & 0xf0) < CONTROLLER)
#define is_note_on(status) (((status) & 0xf0) == NOTE_ON)
#define is_note_off(status, data2)               \
  ((((status) & 0xf0) == NOTE_OFF)) ||           \
  ((((status) & 0xf0) == NOTE_ON) && data2 == 0)
#define is_system_common(status) ((status) >= SYSEX)
#define is_realtime(status) ((status) >= CLOCK)

#endif /* PREDICATES_H */
