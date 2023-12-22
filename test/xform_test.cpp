#include <catch2/catch_all.hpp>
#include "test_helper.h"
#include "../src/pipes/xform.h"

#define CATCH_CATEGORY "[xform]"

struct XformTestCase {
  XformFrom from;
  XformTo to;
  byte to_controller_num;
  byte input[4];
  byte output[4];               // if first byte is 0, expect no bytes
};

XformTestCase XFORM_TEST_INPUT[] = {
  // note on value to CC
  {XFF_FROM_NOTE_ON_VALUE, XFF_TO_CC, 7,
    {NOTE_ON + 3, 64, 127, 0}, {CONTROLLER + 3, 7, 64, 0}},

  // note on value to start
  {XFF_FROM_NOTE_ON_VALUE, XFF_TO_START, 0,
    {NOTE_ON + 3, 64, 127, 0}, {START, 0, 0, 0}},

  // note on velocity to cc
  {XFF_FROM_NOTE_ON_VELOCITY, XFF_TO_CC, 7,
    {NOTE_ON + 3, 64, 127, 0}, {CONTROLLER + 3, 7, 127, 0}},

  // note on velocity to start
  {XFF_FROM_NOTE_ON_VELOCITY, XFF_TO_START, 0,
    {NOTE_ON + 3, 64, 127, 0}, {START, 0, 0, 0}},

  // note off unchanged
  {XFF_FROM_NOTE_ON_VALUE, XFF_TO_CC, 7,
    {NOTE_OFF + 3, 64, 127, 0}, {NOTE_OFF + 3, 64, 127, 0}},

  // pitch bend unchanged
  {XFF_FROM_NOTE_ON_VALUE, XFF_TO_CC, 7,
    {PITCH_BEND + 3, 64, 0, 0}, {PITCH_BEND + 3, 64, 0, 0}},

  // clock unchanged
  {XFF_FROM_NOTE_ON_VALUE, XFF_TO_CC, 7,
    {CLOCK, 0, 0, 0}, {CLOCK, 0, 0, 0}}
};

TEST_CASE("all xform test cases", CATCH_CATEGORY) {
  Xform *xform = new Xform();
  ADD_TEST_SINK(xform);

  for (int i = 0; i < sizeof(XFORM_TEST_INPUT) / sizeof(XformTestCase); ++i) {
    XformTestCase tcase = XFORM_TEST_INPUT[i];

    xform->from = tcase.from;
    xform->to = tcase.to;
    xform->to_controller_num = tcase.to_controller_num;
    TEST_SINK(xform)->clear();
    xform->process(tcase.input[0], tcase.input[1], tcase.input[2], tcase.input[3]);

    if (tcase.output[0] == 0) {
      REQUIRE(TEST_SINK(xform)->empty());
    }
    else {
      REQUIRE(TEST_SINK(xform)->has_messages(1));
      REQUIRE(TEST_SINK(xform)->message_equals(0, tcase.output));
    }
  }

  REMOVE_TEST_SINK(xform);
  delete xform;
}
