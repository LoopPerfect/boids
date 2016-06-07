#ifndef ALPP_DEFAULTS_HPP
#define ALPP_DEFAULTS_HPP

#include "mixin.hpp"
#include "types.hpp"

namespace alpp {

static const auto bitmap_defaults = mix (
  Position{0,0},
  Region{0,0,1,1},
  Scale{1.0,1.0},
  Center{0,0},
  Rad{0},
  Color{0xFF, 0xFF, 0xFF}
);

using BitmapData = decltype(bitmap_defaults);



}

#endif
