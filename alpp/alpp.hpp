#ifndef ALPP_ALPP_HPP
#define ALPP_ALPP_HPP

#include "types.hpp"
#include "display.hpp"
#include "image.hpp"

namespace alpp {

auto allegroInit() {
  al_init();
  al_init_image_addon();
  al_install_mouse();
  return 1;
}

}

#endif
