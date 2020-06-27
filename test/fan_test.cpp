#include "catch.hpp"
#include "test_helper.h"
#include "../src/pipes/fan.h"

#define CATCH_CATEGORY "[fan]"

TEST_CASE("fan insert between", CATCH_CATEGORY) {
  Pipe *upstream = new Pipe();
  Pipe *downstream = new Pipe();
  upstream->downstream = downstream;
  downstream->upstream = upstream;

  Fan *fan = new Fan();
  fan->insert_between(upstream, downstream);

  REQUIRE(fan->upstream == upstream);
  REQUIRE(upstream->downstream == fan);
  REQUIRE(fan->downstreams.size() == 1);
  REQUIRE(fan->downstreams[0] == downstream);
  REQUIRE(downstream->upstream == fan);

  delete fan;
  delete upstream;
  delete downstream;
}

TEST_CASE("fan remove", CATCH_CATEGORY) {
  Pipe *upstream = new Pipe();
  Pipe *downstream = new Pipe();
  upstream->downstream = downstream;
  downstream->upstream = upstream;

  Fan *fan = new Fan();
  fan->insert_between(upstream, downstream);

  fan->remove();

  REQUIRE(upstream->downstream == downstream);
  REQUIRE(downstream->upstream == upstream);
  REQUIRE(fan->upstream == nullptr);
  REQUIRE(fan->downstreams.empty());

  delete fan;
  delete upstream;
  delete downstream;
}

TEST_CASE("fan note on", CATCH_CATEGORY) {
  Fan *fan = new Fan();
  TestSinkPipe *down1 = new TestSinkPipe();
  TestSinkPipe *down2 = new TestSinkPipe();

  fan->insert_before(down1);
  fan->insert_before(down2);

  fan->process(NOTE_ON + 3, 64, 127, 0);

  REQUIRE(down1->has_messages(1));
  REQUIRE(down2->has_messages(1));
  REQUIRE(down1->message_equals(0, NOTE_ON + 3, 64, 127, 0));
  REQUIRE(down2->message_equals(0, NOTE_ON + 3, 64, 127, 0));

  delete down1;
  delete down2;
  delete fan;
}
