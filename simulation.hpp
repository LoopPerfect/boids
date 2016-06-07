#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <ctime>
#include <chrono>
#include <thread>

#include <random>
#include <algorithm>
#include <functional>
#include <iostream>

#include <alpp/alpp.hpp>
#include <simulation/types.hpp>
#include <simulation/utils.hpp>
#include <simulation/behaviours.hpp>

using World = std::vector<BoidState>;

static World world;

static bool s = alpp::allegroInit();
static size_t mouseX = -1000;
static size_t mouseY = -1000;
static bool stop = false;
static alpp::Display display;
static double speed = 5;
static auto boidImg = alpp::Image("boid.png");
static auto boid2Img = alpp::Image("boid2.png");
static auto mouseImg = alpp::Image("mouse.png");

/// \brief draws the mouse
static void drawMouse(alpp::Display const& display, int mouseX, int mouseY) {
    auto image = mouseImg;

    image.draw(
      alpp::Position{
        mouseX,
        mouseY
      },
      alpp::Center{0.5, 0.5},
      alpp::Color{ 255, 255, 255}
    );
}

std::function< void(BoidState, alpp::Display const&) > drawBoid;
std::function< World ( World const&, alpp::Display const&, double ) > process;
std::function< void(ALLEGRO_EVENT) > eventHandler;

void spawnBoid() {
  world.push_back(makeRandomBoid());
}

void run() {
  #include "simulation.cpp"

  eventHandler = makeSimpleEventHandler(mouseX, mouseY, stop);

  for(int i=0; i< 10; ++i)
    spawnBoid();

  display = alpp::Display("LoopPerfect.com - Hot Reload Demo", 800, 800);

  std::srand(std::time(0));

  stop=false;
  double dt=0.016;
  while(!stop) {
    using namespace std::chrono;

    auto start = std::chrono::system_clock::now();
    size_t initialSize = world.size();
    while(1) {
      auto e = display.getEvent();
      e.then(eventHandler);
      if(!e) break;
    }

    display.clear(alpp::Color{200,200,255});
    auto newWorld = process(world, display, dt*speed);
    if(initialSize == world.size() ){
      world = newWorld;
    }
    display.draw();

    auto end = system_clock::now();

    long deltaT = duration_cast<microseconds>(end-start).count()/1000;
    dt = 0.0016*speed;

    std::this_thread::sleep_for(
      milliseconds( clip(16-deltaT,0l,16l) )
    );
  }
  display = alpp::Display();
}


#endif
