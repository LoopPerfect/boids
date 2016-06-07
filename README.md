# C++ Boids simulation - Jyt - hot-module-reload playground

This is a flocking demo based on Allegro.

# Run

with clang:
```
clang++ -std=c++14 -I. -lallegro -lallegro_image main.cpp -o main && ./main
```
or with jyt:
```
jyt -x main.cpp --hot -i
```

# Requirements

- c++-14 compiant compiler
- [liballegro](http://allegro.cc)
- [jyt (optional)](http://jyt.io)
