#include "grid.h"
#include <cstring>
#include <fstream>
#include <GL/glut.h>
Grid::Grid(){

}

Grid::~Grid(){
  
}

void Grid::load_dimensions(int height, int width, int depth){
    this->height = (height);
    this->width = (width);
    this->depth = (depth);
}

void Grid::create_grid(){

}

void Grid::render(){

  glColor3f(0,0,0);
  glBegin(GL_LINES);
/*
  Render the grid
*/
  for (int x = 0; x < width; x+=1){ 
    for(int y = 0; y < height; y++){  
      for(int z = 0; z < depth; z++){

        // draw x-axis lines
        glVertex3f(0, y, z);
        glVertex3f(width-1, y,z);

        // draw y-axis lines 
        glVertex3f(x, 0, z);
        glVertex3f(x, height-1,z);

        // draw z-axis lines 
        glVertex3f(x, y, 0);
        glVertex3f(x, y,depth-1);
      }
    }
  }
    glEnd();
}

void Grid::renderAxis(){
  //x red
  glBegin(GL_LINES);    
  glColor3f(1 ,0 ,0 );
  for(double i = 0; i < 1;i++){
    glVertex3f(0, i, 0);
    glVertex3f(100, i, 0);
  }

  //y green
    glColor3f(0 ,1 ,0 );
  for(double i = 0; i < 1;i++){
    glVertex3f(i, 0, 0);
    glVertex3f(i, 100, 0);
  }


  //z blue
    glColor3f(0 ,0 ,1 );
  for(double i = 0; i < 1;i++){
    glVertex3f(0, i, 0);
    glVertex3f(0, i, 100);
  }
glEnd();

}
