# C++ Boids simulation - Jyt - hot-module-reload playground

This is a flocking demo based on Allegro. 

# Run

with Clang:
```
clang++ -std=c++14 -I. -lallegro -lallegro_image -lallegro_main main.cpp -o main && ./main
```
or with Jyt:
```
jyt -x main.cpp --hot -i
```

# Requirements

- C++-14 compliant compiler
- [liballegro](http://allegro.cc)
- [Yyt (optional)](http://jyt.io)
