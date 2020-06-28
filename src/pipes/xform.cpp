#include "xform.h"

Xform::Xform(sqlite3_int64 id)
  : Pipe(id, "Transform"), from(XFF_FROM_NOTE_ON_VALUE), to(XFF_TO_CC), to_controller_num(CC_VOLUME_MSB)
{
}

void Xform::process(byte status, byte data1, byte data2, byte data3) {
  byte high_nibble = status & 0xf0;
  byte chan = status & 0x0f;

  if (high_nibble == NOTE_ON) {
    if (from == XFF_FROM_NOTE_ON_VALUE) {
      switch (to) {
      case XFF_TO_CC:
        status = CONTROLLER + chan;
        data2 = data1;          // cc num is note num
        data1 = to_controller_num;
        break;
      case XFF_TO_PC:
        status = PROGRAM_CHANGE + chan;
        data2 = 0;
        break;
      case XFF_TO_CHAN_PRESS:
        status = CHANNEL_PRESSURE + chan;
        data2 = 0;
        break;
      case XFF_TO_START:
        status = START;
        data1 = data2 = 0;
        break;
      case XFF_TO_CONTINUE:
        status = CONTINUE;
        data1 = data2 = 0;
        break;
      case XFF_TO_STOP:
        status = STOP;
        data1 = data2 = 0;
        break;
      }
    }
    else if (from == XFF_FROM_NOTE_ON_VELOCITY) {
      switch (to) {
      case XFF_TO_CC:
        status = CONTROLLER + chan;
        data1 = to_controller_num;
        break;
      case XFF_TO_PC:
        status = PROGRAM_CHANGE + chan;
        data1 = data2;
        data2 = 0;
        break;
      case XFF_TO_CHAN_PRESS:
        status = CHANNEL_PRESSURE + chan;
        data1 = data2;
        data2 = 0;
        break;
      case XFF_TO_START:
        status = START;
        data1 = data2 = 0;
        break;
      case XFF_TO_CONTINUE:
        status = CONTINUE;
        data1 = data2 = 0;
        break;
      case XFF_TO_STOP:
        status = STOP;
        data1 = data2 = 0;
        break;
      }
    }
  }
  else if (high_nibble == CONTROLLER) {
    if (from == XFF_FROM_CC) {
      switch (to) {
      case XFF_TO_CC:
        data1 = to_controller_num;
        break;
      case XFF_TO_PC:
        status = PROGRAM_CHANGE + chan;
        data1 = data2;
        data2 = 0;
        break;
      case XFF_TO_CHAN_PRESS:
        status = CHANNEL_PRESSURE;
        data1 = data2;
        data2 = 0;
        break;
      case XFF_TO_START:
        status = START;
        data1 = data2 = 0;
        break;
      case XFF_TO_CONTINUE:
        status = CONTINUE;
        data1 = data2 = 0;
        break;
      case XFF_TO_STOP:
        status = STOP;
        data1 = data2 = 0;
        break;
      }
    }
  }
  else if (high_nibble == PROGRAM_CHANGE) {
    if (from == XFF_FROM_CC) {
      switch (to) {
      case XFF_TO_CC:
        status = CONTROLLER + chan;
        data2 = data1;
        data1 = 0;
        break;
      case XFF_TO_PC:
        break;
      case XFF_TO_CHAN_PRESS:
        status = CHANNEL_PRESSURE + chan;
        break;
      case XFF_TO_START:
        status = START;
        data1 = data2 = 0;
        break;
      case XFF_TO_CONTINUE:
        status = CONTINUE;
        data1 = data2 = 0;
        break;
      case XFF_TO_STOP:
        status = STOP;
        data1 = data2 = 0;
        break;
      }
    }
  }
  else if (high_nibble == CHANNEL_PRESSURE) {
    if (from == XFF_FROM_CC) {
      switch (to) {
      case XFF_TO_CC:
        status = CONTROLLER + chan;
        data2 = data1;
        data1 = 0;
        break;
      case XFF_TO_PC:
        status = PROGRAM_CHANGE;
        break;
      case XFF_TO_CHAN_PRESS:
        break;
      case XFF_TO_START:
        status = START;
        data1 = data2 = 0;
        break;
      case XFF_TO_CONTINUE:
        status = CONTINUE;
        data1 = data2 = 0;
        break;
      case XFF_TO_STOP:
        status = STOP;
        data1 = data2 = 0;
        break;
      }
    }
  }
  else if ((status == START && from == XFF_FROM_START) ||
           (status == CONTINUE && from == XFF_FROM_CONTINUE) ||
           (status == STOP && from == XFF_FROM_STOP))
  {
      switch (to) {
      case XFF_TO_CC:
        status = CONTROLLER;
        data1 = data2 = 0;
        break;
      case XFF_TO_PC:
        status = PROGRAM_CHANGE;
        data1 = data2 = 0;
        break;
      case XFF_TO_CHAN_PRESS:
        status = CHANNEL_PRESSURE;
        data1 = data2 = 0;
        break;
      case XFF_TO_START:
        status = START;
        data1 = data2 = 0;
        break;
      case XFF_TO_CONTINUE:
        status = CONTINUE;
        data1 = data2 = 0;
        break;
      case XFF_TO_STOP:
        status = STOP;
        data1 = data2 = 0;
        break;
      }
  }

  Pipe::process(status, data1, data2, data3);
}
