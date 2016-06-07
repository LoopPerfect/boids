#include "simulation.hpp"

drawBoid = [](
  auto const& boid,
  auto const& dispaly
) {
  auto image = (boid.id%2) ? boidImg : boid2Img;

  image.draw(
    alpp::Position{
      (int)((boid.x+1)/2 * display.width ),
      (int)((boid.y+1)/2 * display.height )
    },
    alpp::Center{0.5, 0.5},
    alpp::Scale{
      0.05f * display.width/(float)image.width,
      0.05f * display.height/(float)image.height
    },
    alpp::Color{ 255, 255, 255},
    alpp::Rad{ (float)std::atan2( boid.vy, boid.vx ) }
  );
};

process = [](auto const& oldWorld, auto const& display, auto dt){
  World newWorld = oldWorld;
  auto interactWithMouse = makeAttractor(mouseX, mouseY, display, -3000, 1);
  auto attractToCenter = makeAttractor(400, 400, display, 10, 2);
  auto follow = seekSibling(world, 20);
  auto repulse = makeRepulser(world, 0.1);
  drawMouse(display, mouseX, mouseY);
  for(auto& boid: newWorld) {
    boid= limitSpeed(boid, 0.5);
    boid= clipToWorld(boid);
    boid= follow(boid, dt);
    boid= interactWithMouse(boid, dt);
    boid= attractToCenter(boid, dt);
    boid= limitForces(boid, 1);
    boid= speedUpBoid(boid, dt);
    boid= moveBoid(boid, dt);
  }

  for(auto& boid: newWorld) {
    drawBoid(boid, display);
  }

  return newWorld;
};

