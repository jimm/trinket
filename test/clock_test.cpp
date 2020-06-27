#include "catch.hpp"
#include "test_helper.h"
#include "../src/pipes/clock.h"

#define CATCH_CATEGORY "[clock]"

TEST_CASE("clock bpm math", CATCH_CATEGORY) {
  Clock *clock = new Clock();

  REQUIRE(clock->bpm() == 120);
  REQUIRE(clock->microsecs_per_tick == (500000L / 24L));

  clock->set_bpm(60);
  REQUIRE(clock->bpm() == 60);
  REQUIRE(clock->microsecs_per_tick == (1000000 / 24L));

  clock->set_bpm(240);
  REQUIRE(clock->bpm() == 240);
  REQUIRE(clock->microsecs_per_tick == (250000L / 24L));

  delete clock;
}
