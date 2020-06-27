#ifndef FILTER_H
#define FILTER_H

#include "../pipe.h"

enum FilterStatus {
  FS_NOTE_OFF,
  FS_NOTE_ON,
  FS_POLY_PRESSURE,
  FS_CONTROLLER,
  FS_PROGRAM_CHANGE,
  FS_CHANNEL_PRESSURE,
  FS_PITCH_BEND,
  FS_SYSEX,
  FS_DUMMY_1,
  FS_SONG_POINTER,
  FS_SONG_SELECT,
  FS_DUMMY_4,
  FS_DUMMY_5,
  FS_TUNE_REQUEST,
  FS_DUMMY_6,
  FS_CLOCK,
  FS_DUMMY_7,
  FS_START,
  FS_CONTINUE,
  FS_STOP,
  FS_DUMMY_8,
  FS_ACTIVE_SENSE,
  FS_SYSTEM_RESET
};

class Filter : public Pipe {
public:
  bool filters[FS_SYSTEM_RESET+1];

  Filter(sqlite3_int64 id = UNDEFINED_ID);

  void process(byte status, byte data1, byte data2, byte data3);
};

#endif /* FILTER_H */
