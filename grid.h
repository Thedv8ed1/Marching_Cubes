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
  Cube*** cubes;
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
    void draw(){
        glBegin(GL_LINES);
          glColor3f(0 ,0 ,0 );

        //glColor3f(1.0f, 0.0f, 0.0f); 
       glVertex3f(verticies[0].x, verticies[0].y, verticies[0].z);
        glVertex3f(verticies[1].x, verticies[1].y, verticies[1].z);

        glVertex3f(verticies[0].x, verticies[0].y, verticies[0].z);
        glVertex3f(verticies[3].x, verticies[3].y, verticies[3].z);

        glVertex3f(verticies[0].x, verticies[0].y, verticies[0].z);
        glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);

        glVertex3f(verticies[3].x, verticies[3].y, verticies[3].z);
        glVertex3f(verticies[2].x, verticies[2].y, verticies[2].z);

        glVertex3f(verticies[3].x, verticies[3].y, verticies[3].z);
        glVertex3f(verticies[7].x, verticies[7].y, verticies[7].z);

        glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
        glVertex3f(verticies[7].x, verticies[7].y, verticies[7].z);

        glVertex3f(verticies[4].x, verticies[4].y, verticies[4].z);
        glVertex3f(verticies[5].x, verticies[5].y, verticies[5].z);

        glVertex3f(verticies[7].x, verticies[7].y, verticies[7].z);
        glVertex3f(verticies[6].x, verticies[6].y, verticies[6].z);

        glVertex3f(verticies[5].x, verticies[5].y, verticies[5].z);
        glVertex3f(verticies[1].x, verticies[1].y, verticies[1].z);

        glVertex3f(verticies[2].x, verticies[2].y, verticies[2].z);
        glVertex3f(verticies[1].x, verticies[1].y, verticies[1].z);

        glVertex3f(verticies[2].x, verticies[2].y, verticies[2].z);
        glVertex3f(verticies[3].x, verticies[3].y, verticies[3].z);

        glVertex3f(verticies[2].x, verticies[2].y, verticies[2].z);
        glVertex3f(verticies[6].x, verticies[6].y, verticies[6].z);

        glEnd();
    };

    Point verticies[8];

      
     double values[8];
    
private:


};

