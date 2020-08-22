#pragma once
#include <iostream>
//#include <GL/glew.h>
#include <GL/glut.h>

class Cube;
class Grid{
  public:
  Grid();
  ~Grid();

  void load_dimensions(int height, int width, int depth);
  void create_grid();
  void render();
  void renderAxis();

  private:
  int height,width,depth;
};

struct Point{
    double x=0,y=0,z = 0;
};

struct Triangle{
  Point p[3];
};

class Cube{
public:
  Cube(){}
  ~Cube(){}

  Point verticies[8];

  double values[8];
    
private:

};