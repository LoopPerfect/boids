#ifndef ALPP_IMAGE_HPP
#define ALPP_IMAGE_HPP

#include "defaults.hpp"
#include <allegro5/allegro_image.h>
#include <memory>

namespace alpp {

template<class I, class D, class...O>
void al_draw(I& i, D defaults, O...options) {
  auto o = merge(defaults, options...);
  al_draw_tinted_scaled_rotated_bitmap_region(
    i.img.get(),
    o.rx * i.width, o.ry * i.height, o.rw * i.width , o.rh * i.height,
    al_map_rgb(o.r, o.g, o.b),
    o.cx * i.width, o.cy * i.height,
    o.px, o.py,
    o.sx, o.sy,
    o.rad,
    0
  );
}

struct Image {
  Image()=default;
  ~Image()=default;

  Image(const char* path) {
    auto image = al_load_bitmap(path);
    img.reset( image , al_destroy_bitmap );
    width = al_get_bitmap_width(img.get());
    height = al_get_bitmap_height(img.get());
  }

  template<class...X>
  void draw(X const&...x) {
    if(img.get())
      al_draw(*this, bitmap_defaults, x...);
  }

  ALLEGRO_BITMAP* getImage() {
    return img.get();
  }

  std::shared_ptr<ALLEGRO_BITMAP> img;
  size_t width;
  size_t height;
};



}

#endif

