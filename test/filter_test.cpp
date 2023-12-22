#include <catch2/catch_all.hpp>
#include "test_helper.h"
#include "../src/pipes/filter.h"

#define CATCH_CATEGORY "[filter]"

struct FilterTestCase {
  FilterStatus what_to_filter;
  byte input[4];
  byte output[4];               // if first byte is 0, expect no bytes
};

FilterTestCase FILTER_TEST_INPUT[] = {
  {FS_NOTE_ON, {NOTE_ON, 64, 127, 0}, {0, 0, 0, 0}},
  {FS_NOTE_ON, {CONTROLLER, 64, 127, 0}, {CONTROLLER, 64, 127, 0}},
  {FS_NOTE_ON, {START, 0, 0, 0}, {START, 0, 0, 0}},
  {FS_START, {START, 0, 0, 0}, {0, 0, 0, 0}},
  {FS_START, {CONTINUE, 0, 0, 0}, {CONTINUE, 0, 0, 0}}
};

TEST_CASE("all filter test cases", CATCH_CATEGORY) {
  Filter *filter = new Filter();
  ADD_TEST_SINK(filter);

  for (int i = 0; i < sizeof(FILTER_TEST_INPUT) / sizeof(FilterTestCase); ++i) {
    FilterTestCase tcase = FILTER_TEST_INPUT[i];
    for (int i = 0; i <= FS_SYSTEM_RESET; ++i)
      filter->filters[i] = false;
    filter->filters[tcase.what_to_filter] = true;
    CLEAR_TEST_SINK(filter);
    filter->process(tcase.input[0], tcase.input[1], tcase.input[2], tcase.input[3]);
    if (tcase.output[0] == 0) {
      REQUIRE(TEST_SINK(filter)->empty());
    }
    else {
      REQUIRE(TEST_SINK(filter)->has_messages(1));
      REQUIRE(TEST_SINK(filter)->message_equals(0, tcase.output));
    }
  }
  REMOVE_TEST_SINK(filter);
  delete filter;
}
