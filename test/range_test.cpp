#include "catch.hpp"
#include "test_helper.h"
#include "../src/pipes/range.h"

#define CATCH_CATEGORY "[range]"
#define NOTE_ON_64 {NOTE_ON, 64, 127}
#define CC {CONTROLLER, 7, 127}
#define FILTERED_OUT {0, 0, 0, 0}

struct RangeTestCase {
  int low;
  int high;
  bool keep_in_range;
  byte input[4];
  byte output[4];               // if first byte 0, expect no bytes
};

RangeTestCase RANGE_TEST_CASES[] = {
  {0, 127, true, NOTE_ON_64, NOTE_ON_64},
  {0, 63, true, NOTE_ON_64, FILTERED_OUT},
  {65, 127, true, NOTE_ON_64, FILTERED_OUT},
  {0, 127, false, NOTE_ON_64, FILTERED_OUT},
  {0, 63, false, NOTE_ON_64, NOTE_ON_64},
  {65, 127, false, NOTE_ON_64, NOTE_ON_64},
  {0, 127, true, CC, CC},
  {0, 0, true, CC, CC},
  {0, 127, false, CC, CC},
  {0, 0, false, CC, CC}
};

TEST_CASE("all range test cases", CATCH_CATEGORY) {
  Range *range = new Range();
  ADD_TEST_SINK(range);

  for (int i = 0; i < sizeof(RANGE_TEST_CASES) / sizeof(RangeTestCase); ++i) {
    RangeTestCase tcase = RANGE_TEST_CASES[i];
    range->low = tcase.low;
    range->high = tcase.high;
    range->keep_in_range = tcase.keep_in_range;
    CLEAR_TEST_SINK(range);
    range->process(tcase.input[0], tcase.input[1], tcase.input[2], tcase.input[3]);
    if (tcase.output[0] == 0) {
      REQUIRE(TEST_SINK(range)->empty());
    }
    else {
      REQUIRE(TEST_SINK(range)->has_messages(1));
      REQUIRE(TEST_SINK(range)->message_equals(0, tcase.output));
    }
  }

  REMOVE_TEST_SINK(range);
  delete range;
}

TEST_CASE("process note out of range", CATCH_CATEGORY) {
  Range *range = new Range();
  ADD_TEST_SINK(range);

  range->high = 60;
  range->process(NOTE_ON + 3, 64, 127, 0);

  REQUIRE(TEST_SINK(range)->empty());

  REMOVE_TEST_SINK(range);
  delete range;
}

TEST_CASE("process note off out of range", CATCH_CATEGORY) {
  Range *range = new Range();
  ADD_TEST_SINK(range);

  range->high = 60;
  range->process(NOTE_OFF + 3, 64, 127, 0);

  REQUIRE(TEST_SINK(range)->empty());

  REMOVE_TEST_SINK(range);
  delete range;
}

TEST_CASE("process poly pressure out of range", CATCH_CATEGORY) {
  Range *range = new Range();
  ADD_TEST_SINK(range);

  range->high = 60;
  range->process(POLY_PRESSURE + 3, 64, 127, 0);

  REQUIRE(TEST_SINK(range)->empty());

  REMOVE_TEST_SINK(range);
  delete range;
}
