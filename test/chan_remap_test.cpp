#include "catch.hpp"
#include "test_helper.h"
#include "../src/pipes/chan_remap.h"

#define CATCH_CATEGORY "[chan_remap]"

struct ChanRemapTestCase {
  int mappings[16];
  byte input[4];
  byte output[4];               // if first byte is 0, expect no bytes
};

ChanRemapTestCase CHAN_REMAP_TEST_INPUT[] = {
  // chan 0 to 3
  { {3, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
    {NOTE_ON, 64, 127, 0}, {NOTE_ON + 3, 64, 127, 0} },
  // chan unchanged
  { {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
    {NOTE_ON + 3, 64, 127, 0}, {NOTE_ON + 3, 64, 127, 0}},
  // filter out chan 2
  { {0, 1, CHAN_REMAP_FILTER, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
    {NOTE_ON + 2, 64, 127, 0}, {0, 0, 0, 0}},
  // don't affect non-channel status bytes
  { {CHAN_REMAP_FILTER, CHAN_REMAP_FILTER, CHAN_REMAP_FILTER, CHAN_REMAP_FILTER,
     CHAN_REMAP_FILTER, CHAN_REMAP_FILTER, CHAN_REMAP_FILTER, CHAN_REMAP_FILTER,
     CHAN_REMAP_FILTER, CHAN_REMAP_FILTER, CHAN_REMAP_FILTER, CHAN_REMAP_FILTER,
     CHAN_REMAP_FILTER, CHAN_REMAP_FILTER, CHAN_REMAP_FILTER, CHAN_REMAP_FILTER},
    {START, 0, 0, 0}, {START, 0, 0, 0}}
};

TEST_CASE("all chan remap test cases", CATCH_CATEGORY) {
  ChanRemap *remapper = new ChanRemap();
  ADD_TEST_SINK(remapper);

  for (int i = 0; i < sizeof(CHAN_REMAP_TEST_INPUT) / sizeof(ChanRemapTestCase); ++i) {
    ChanRemapTestCase tcase = CHAN_REMAP_TEST_INPUT[i];
    for (int j = 0; j < 16; ++j)
      remapper->mappings[i] = tcase.mappings[i];
    CLEAR_TEST_SINK(remapper);
    remapper->process(tcase.input[0], tcase.input[1], tcase.input[2], tcase.input[3]);
    if (tcase.output[0] == 0) {
      REQUIRE(TEST_SINK(remapper)->empty());
    }
    else {
      REQUIRE(TEST_SINK(remapper)->has_messages(1));
      REQUIRE(TEST_SINK(remapper)->message_equals(0, tcase.output));
    }
  }
  REMOVE_TEST_SINK(remapper);
  delete remapper;
}
