#include <stdio.h>
#include "trinket.h"

static Trinket *trinket_instance = nullptr;

Trinket *Trinket_instance() {
  if (trinket_instance == nullptr)
    trinket_instance = new Trinket();
  return trinket_instance;
}

Trinket::Trinket() : testing(true) {}
