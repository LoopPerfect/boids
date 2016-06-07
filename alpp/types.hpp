#ifndef ALPP_TYPES_HPP
#define ALPP_TYPES_HPP

namespace alpp {

struct Color {
  int r;
  int g;
  int b;
};

struct Position {
  int px;
  int py;
};

struct Region {
  int rx;
  int ry;
  int rw;
  int rh;
};

struct Scale {
  float sx;
  float sy;
};


struct Center {
  float cx;
  float cy;
};

struct Rad {
  float rad;
};

}

#endif
