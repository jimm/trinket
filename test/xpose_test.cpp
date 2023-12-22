#include <catch2/catch_all.hpp>
#include "test_helper.h"
#include "../src/pipes/xpose.h"

#define CATCH_CATEGORY "[xpose]"

TEST_CASE("xpose note on", CATCH_CATEGORY) {
  Xpose *xpose = new Xpose();
  ADD_TEST_SINK(xpose);

  xpose->xpose = 0;
  xpose->process(NOTE_ON + 3, 64, 127, 0);
  xpose->xpose = 12;
  xpose->process(NOTE_ON + 3, 64, 127, 0);
  xpose->xpose = -12;
  xpose->process(NOTE_ON + 3, 64, 127, 0);

  REQUIRE(TEST_SINK(xpose)->has_messages(3));
  REQUIRE(TEST_SINK(xpose)->message_equals(0, NOTE_ON + 3, 64, 127, 0));
  REQUIRE(TEST_SINK(xpose)->message_equals(1, NOTE_ON + 3, 76, 127, 0));
  REQUIRE(TEST_SINK(xpose)->message_equals(2, NOTE_ON + 3, 52, 127, 0));

  REMOVE_TEST_SINK(xpose);
  delete xpose;
}

TEST_CASE("xpose poly pressure", CATCH_CATEGORY) {
  Xpose *xpose = new Xpose();
  ADD_TEST_SINK(xpose);

  xpose->xpose = 12;
  xpose->process(POLY_PRESSURE + 3, 64, 127, 0);


  REQUIRE(TEST_SINK(xpose)->has_messages(1));
  REQUIRE(TEST_SINK(xpose)->message_equals(0, POLY_PRESSURE + 3, 76, 127, 0));

  REMOVE_TEST_SINK(xpose);
  delete xpose;
}
