#ifndef BEHAVIOURS_HPP
#define BEHAVIOURS_HPP

#include "types.hpp"
#include "utils.hpp"

auto moveBoid = [](auto p, double dt) {
  return merge(p, BoidPos{
    p.x + p.vx * dt,
    p.y + p.vy * dt
  });
};

auto speedUpBoid = [](auto p, double dt) {
  return merge(p, BoidSpeed{
    p.vx + p.ax * dt,
    p.vy + p.ay * dt
  });
};

auto deaccelerateBoid = [](auto p, double dt) {
  return merge(p, BoidAcceleration{
    p.ax / dt,
    p.ay / dt
  });
};

auto limitForces = [](auto p, double max) {
  double l = sqrt(p.ax*p.ax+p.ay*p.ay);
  if(l<max) return p;
  return merge(p, BoidAcceleration{
    p.ax*max/l,
    p.ay*max/l
  });
};

auto limitSpeed = [](auto p, double max=1) {
  double l = sqrt(p.vx*p.vx+p.vy*p.vy);
  if(l<=max) return p;
  return merge(p, BoidSpeed{
    p.vx*max/l,
    p.vy*max/l
  });
};

auto makeRepulser = [](auto const& world, double const factor){
  return [&world,factor](auto boid, double dt) {

    double repulsionX = 0;
    double repulsionY = 0;
    int i=0;
    for( auto b : world ) {
      if(b.id == boid.id) continue;
      ++i;
      double dx = b.x-boid.x;
      double dy = b.y-boid.y;
      double l = dx*dx+dy*dy;

      if( l  < 0.1 ) {
        auto p = makeRandomPoint(100)();
        repulsionX = p.x;
        repulsionY = p.y;
        break;
      }

      repulsionX += 1/(dx*dx) * ((dx>0)?+1:-1);
      repulsionY += 1/(dy*dy) * ((dy>0)?+1:-1);
    }

    return merge(boid, BoidAcceleration{
      boid.ax + clip( repulsionX * factor, -2.0, 2.0),
      boid.ay + clip( repulsionY * factor, -2.0, 2.0)
    });
  };
};


auto cancelForces = [](auto p) {
  return clipForces(p,0);
};

auto clipToWorld = [](auto p) {
  return merge(p, BoidPos{
    clip(p.x, -0.9, +0.9),
    clip(p.y, -0.9, +0.9)
  });
};

auto cyclicWorld = [](auto p) {
  return merge(p, BoidPos{
    fmod(p.x+1.0,2.0)-1.0,
    fmod(p.y+1.0,2.0)-1.0,
  });
};

auto makeSimpleBoidDrawer = [](auto path, auto const& display) {
  return [image = alpp::Image(path), &display](auto p) mutable {
    image.draw(
      alpp::Position{
        (int)((p.x+1)/2 * display.width ),
        (int)((p.y+1)/2 * display.height )
      },
      alpp::Center{0.5, 0.5},
      alpp::Scale{
        0.05f * display.width/(float)image.width,
        0.05f * display.height/(float)image.height
      },
      alpp::Color{255, 255, 255},
      alpp::Rad{ (float)std::atan2( p.vy, p.vx ) }
    );
    return p;
  };
};


auto seek = [](auto const& b, double factor=0.03) {
  return [&b, factor](auto const& p) {
    auto dx = b.x-p.x;
    auto dy = b.y-p.y;
    auto l = sqrt(dx*dx + dy*dy);
    if(l<0.01) return p;
    return merge(p, BoidAcceleration{
      p.ax + dx/l * factor,
      p.ay + dy/l * factor
    });
  };
};

auto freeze = [](auto p) {
  return p;
};

auto seekSibling = [](auto const& world, auto const& factor) {
  return [&world, factor](auto p, double dt) {
    return seek( world[ (p.id+1) % world.size() ], dt * factor)(p);
  };
};

auto makeSimpleEventHandler = [](auto& mouseX, auto& mouseY, auto& stop){
  return [&](auto ev) {
    if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ){
       mouseX = ev.mouse.x;
       mouseY = ev.mouse.y;
    } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
       stop=true;
    }
  };
};


auto makeAttractor = [](size_t const& mouseX, size_t const& mouseY, auto const& display, double const factor, double const radius) {
  return [&, factor, radius]( auto p, double dt ) {
    auto x = (mouseX/(float)display.width - 0.5) * 2.0;
    auto y = (mouseY/(float)display.height - 0.5) * 2.0;
    auto dx = x - p.x;
    auto dy = y - p.y ;
    auto l = length(dx,dy);
    if(radius<l) return p;
    return merge(p, BoidAcceleration{
      p.ax + dx * dt * factor,
      p.ay + dy * dt * factor
    });
  };
};


#endif
