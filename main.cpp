#include "simulation.hpp"

#ifdef JYTTER
#include <jyt/runtime.hpp>

void simulation() {
  jyt.async(run);
}

#else

int main(int argc, char** argv) {
  run();
  return 0;
}

#endif