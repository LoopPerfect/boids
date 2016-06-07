#ifndef ALPP_MIXIN_HPP
#define ALPP_MIXIN_HPP

namespace alpp {

template<class...X>
void evalAll(X...) {};

template<class...Base>
struct Mixin : Base... {
  Mixin(Base...B)
    :Base{B}...
  {}

  Mixin()=default;
  Mixin(Mixin const&)=default;

  template<class...B>
  auto const& merge(B const&...b) {
    evalAll( set(b)... );
    return *this;
  }

private:
  template<class S>
  auto set(S const& s) -> decltype( (S*)this , 1 ) {
    ((S&)*this) = s;
    return true;
  }
};

template<class L, class...R>
auto merge(L l, R const&...r) {
  return l.merge(r...);
}

template<class...X>
auto mix(X const&...x) {
  return Mixin<X...>{x...};
}

}

#endif
