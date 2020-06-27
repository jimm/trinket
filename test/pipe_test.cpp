#include "catch.hpp"
#include "test_helper.h"
#include "../src/pipe.h"
#include "../src/input_instrument.h"
#include "../src/output_instrument.h"
#include "../src/pipes/input.h"
#include "../src/pipes/output.h"

#define CATCH_CATEGORY "[pipe]"

TEST_CASE("process", CATCH_CATEGORY) {
  Pipe *pipe = new Pipe(UNDEFINED_ID, "test");
  ADD_TEST_SINK(pipe);
  PmMessage msg = Pm_Message(NOTE_OFF + 3, 64, 127);
  pipe->process(NOTE_OFF + 3, 64, 127, 0);

  REQUIRE(TEST_SINK(pipe)->has_messages(1));
  REQUIRE(TEST_SINK(pipe)->message_equals(0, NOTE_OFF + 3, 64, 127, 0));

  REMOVE_TEST_SINK(pipe);
  delete pipe;
}

TEST_CASE("insert_after", CATCH_CATEGORY) {
  Pipe *upstream = new Pipe(UNDEFINED_ID, "upstream");
  Pipe *pipe = new Pipe();
  pipe->insert_after(upstream);

  REQUIRE(upstream->downstream == pipe);
  REQUIRE(pipe->upstream == upstream);

  delete upstream;
  delete pipe;
}

TEST_CASE("insert_before", CATCH_CATEGORY) {
  Pipe *downstream = new Pipe();
  Pipe *pipe = new Pipe();
  pipe->insert_before(downstream);

  REQUIRE(downstream->upstream == pipe);
  REQUIRE(pipe->downstream == downstream);

  delete downstream;
  delete pipe;
}

TEST_CASE("insert_between", CATCH_CATEGORY) {
  Pipe *upstream = new Pipe();
  Pipe *downstream = new Pipe();
  Pipe *pipe = new Pipe();
  pipe->insert_between(upstream, downstream);

  REQUIRE(upstream->downstream == pipe);
  REQUIRE(pipe->upstream == upstream);
  REQUIRE(downstream->upstream == pipe);
  REQUIRE(pipe->downstream == downstream);

  delete upstream;
  delete downstream;
  delete pipe;
}

// Disconnects this pipe from its upstream inputs and downstream pipes.
TEST_CASE("remove", CATCH_CATEGORY) {
  Pipe *upstream = new Pipe();
  Pipe *downstream = new Pipe();
  Pipe *pipe = new Pipe();
  upstream->downstream = pipe;
  downstream->upstream = pipe;
  pipe->upstream = upstream;
  pipe->downstream = downstream;

  pipe->remove();

  REQUIRE(pipe->upstream == nullptr);
  REQUIRE(pipe->downstream == nullptr);
  REQUIRE(upstream->downstream == downstream);
  REQUIRE(downstream->upstream == upstream);

  delete upstream;
  delete downstream;
  delete pipe;
}

TEST_CASE("remove if not attached", CATCH_CATEGORY) {
  Pipe *pipe = new Pipe();
  pipe->remove();

  REQUIRE(pipe->upstream == nullptr);
  REQUIRE(pipe->downstream == nullptr);

  delete pipe;
}
