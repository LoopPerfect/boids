
#include "simulation.hpp"

#ifdef JYTTER
#include <jyt/runtime.hpp>

void simulation(){
  jyt.async(run);
}

#endif

#ifndef JYTTER
int main(){
  run();
  return 0;
}
#endif
