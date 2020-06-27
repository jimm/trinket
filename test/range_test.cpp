#include "catch.hpp"
#include "test_helper.h"
#include "../src/pipes/range.h"

#define CATCH_CATEGORY "[range]"

TEST_CASE("process note on in range", CATCH_CATEGORY) {
  Range *range = new Range();
  ADD_TEST_SINK(range);

  range->process(NOTE_ON + 3, 64, 127, 0);

  REQUIRE(TEST_SINK(range)->has_messages(1));
  REQUIRE(TEST_SINK(range)->message_equals(0, NOTE_ON + 3, 64, 127, 0));

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
