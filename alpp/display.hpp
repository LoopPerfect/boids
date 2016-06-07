#ifndef ALPP_DISPLAY_HPP
#define ALPP_DISPLAY_HPP

#include "optional.hpp"
#include <allegro5/allegro.h>
#include <memory>
namespace alpp {

struct Display {
  Display()
    : width{0}
    , height{0}
  {}

  ~Display()=default;

  Display(const char* title, size_t width, size_t height)
    : width{width}
    , height{height} {
    display.reset( al_create_display(width, height), al_destroy_display );
    queue.reset( al_create_event_queue(), al_destroy_event_queue );
    al_set_window_title(display.get(), title);

    al_register_event_source(
      queue.get(),
      al_get_display_event_source(display.get())
    );

    al_register_event_source(
      queue.get(),
      al_get_mouse_event_source()
    );
  }

  Optional<ALLEGRO_EVENT> getEvent() {
    ALLEGRO_EVENT e;
    bool hasValue = al_get_next_event(queue.get(), &e);
    return {e, hasValue};
  }

  void clear( Color c = Color{0,0,0} ) {
    al_clear_to_color(al_map_rgb(c.r, c.g, c.b));
  }

  void draw() {
    al_flip_display();
  }

  size_t getWidth()const {
    return width;
  }

  size_t getHeight()const {
    return height;
  }

  std::shared_ptr<ALLEGRO_DISPLAY> display;
  std::shared_ptr<ALLEGRO_EVENT_QUEUE> queue;
  size_t width;
  size_t height;
};


}


#endif
