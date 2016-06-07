#ifndef ALPP_OPTIONAL_HPP
#define ALPP_OPTIONAL_HPP

namespace alpp {

template<class T>
struct Optional {
  T data;
  bool empty;

  Optional()
    :empty{true}
  {}

  Optional(T data, bool hasValue=true)
    : data{data}
    , empty{!hasValue}
  {}


  T const& get() const {
    return data;
  }

  template<class F>
  auto then(F f) const {
    if(empty) {
      return;
    }
    f(data);
  }

  operator bool()const { return !empty; }

};

template<>
struct Optional<void> {
  template<class F>
  auto then(F) const
  {}

  template<class T>
  operator Optional<T> () const {
    return {};
  }
};

template<class T>
auto optional(T data) -> Optional<T> {
  return {data};
}

auto optional() -> Optional<void> {
  return {};
}


}

#endif
