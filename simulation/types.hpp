#ifndef TYPES_HPP
#define TYPES_HPP


using alpp::mix;
using alpp::merge;

struct BoidPos {
  double x;
  double y;
};

struct BoidSpeed {
  double vx;
  double vy;
};

struct BoidAcceleration {
  double ax;
  double ay;
};


struct BoidID {
  size_t id;
};

using BoidState = decltype(mix( BoidPos{0,0}, BoidSpeed{0,0}, BoidAcceleration{0,0}, BoidID{0} ) );

#endif
