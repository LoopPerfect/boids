#ifndef UTILS_HPP
#define UTILS_HPP


#include <random>
#include <ctime>
#include <algorithm>
#include "types.hpp"

auto makeRandomPoint(float length = 1, BoidPos  O = {0.0,0.0} ) {
  return [=](...){
    auto r = length * std::rand() / (float)RAND_MAX;
    auto phi = (std::rand() / (float)RAND_MAX) * M_PI * 2 ;
    return BoidPos{
      sin(phi) * r + O.x,
      cos(phi) * r + O.y
    };
  };
}

static size_t boidId = 0;
auto makeRandomBoid(double length = 1, double velocity = 1, BoidPos O = {0.0,0.0}) {
  auto p = makeRandomPoint(length,O)();
  auto v = makeRandomPoint(velocity)();
    return mix(
      BoidPos{
        p.x,
        p.y,
      },

      BoidSpeed{
        v.x,
        v.y,
      },

      BoidAcceleration {
        0.0,
        0.0,
      },

      BoidID{boidId++}
    );
}

auto clip= [](auto x, auto min, auto max) {
  return std::min( std::max(x,min), max);
};

auto compose() {
  return [=](auto x) {
    return x;
  };
}

template<class F, class...Fs>
auto compose(F f, Fs...fs) {
  return [=](auto x) {
    return compose(fs...)( f(x) );
  };
}

template<class F>
auto map(F&&f) {
  return [f](auto const& v) {
    std::vector<decltype( f(v[0]) )> next(v.size());
    std::transform(v.begin(), v.end(), next.begin(), f);
    return next;
  };
}

template<class T>
struct Enumerated {
  size_t index;
  T value;
};


struct Range {
  size_t b;
  size_t e;

  auto begin() const {
    return Range{0,e};
  }

  size_t size() const { return e-b; }

  auto operator[](size_t i) const {
    return b+i;
  }

  auto operator++() {
    ++b;
    return *this;
  }

  auto operator*() const {
    return b;
  }

  auto operator!=(Range end) const {
    return (b != end.e);
  }

  auto end() const {
    return Range{e,e};
  }
};

auto enumerate = [](size_t i=0) {
  return map([i](auto const& x) mutable {
    return Enumerated<decltype(x)>{
      i++, x
    };
  });
};

template<class T>
auto lin(T x, T a, T b) {
  return a*(1-x) + b*x;
}

auto distance = [](BoidPos a , BoidPos b) {
  auto dx = a.x-b.x;
  auto dy = a.y-b.y;
  return sqrt(dx*dx+dy*dy);
};

auto length = [](auto x, auto y) {
  return sqrt(x*x+y*y);
};


template<class P>
size_t bucketHash(
  P const p,
  size_t buckets,
  double min=-1.0,
  double max=1.0 ) {
  size_t x = (size_t) (buckets-1) * ((p.x-min) / max);
  size_t y = (size_t) (buckets-1) * ((p.x-min) / max);
  return x + y*buckets;
}


#endif
