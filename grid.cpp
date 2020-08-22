#include "grid.h"
#include <cstring>
#include <fstream>
#include <GL/glut.h>
Grid::Grid(){

}

Grid::~Grid(){
  for (int x = 0; x < width; x+=1){
    for (int y = 0; y < height; y+=1){
      delete[] cubes[x][y];
    }
    delete[] cubes[x];    
  }
  delete[] cubes;
  
}

void Grid::load_dimensions(int height, int width, int depth){
    this->height = (height/2)+1;
    this->width = (width/2)+1;
    this->depth = (depth/2)+1;
}

void Grid::create_grid(){

  cubes = new Cube**[width];
  for (int x = 0; x < width; x+=1){
      cubes[x] = new Cube*[height];
      for (int y = 0; y < height; y+=1){
        cubes[x][y] = new Cube[depth];
          for (int z = 0; z < depth; z+=1){
             // cubes[x][y][z] = new Cube*[depth];
              //Cube* c = new Cube();
             cubes[x][y][z].verticies[0] = Point{x,y,z};
             cubes[x][y][z].verticies[1] = Point{x+1,y,z};
             cubes[x][y][z].verticies[2] = Point{x+1,y+1,z};
             cubes[x][y][z].verticies[3] = Point{x, y+1,z};
             cubes[x][y][z].verticies[4] = Point{x ,y,z+1};
             cubes[x][y][z].verticies[5] = Point{x+1,y,z+1};
             cubes[x][y][z].verticies[6] = Point{x+1,y+1,z+1};
             cubes[x][y][z].verticies[7] = Point{x,y+1,z+1};
   
          }
      }
  }
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
        glColor3f(0 ,0 ,0 );

        // draw x-axis lines
        glVertex3f(0, y, z);
        glVertex3f(width, y,z);

        // draw y-axis lines 
        glVertex3f(x, 0, z);
        glVertex3f(x, height,z);

        // draw z-axis lines 
        glVertex3f(x, y, 0);
        glVertex3f(x, y,depth);
      }
    }
  }
    glEnd();
  

}

void Grid::renderAxis(){
  Point xyz[3];
  //x
  glBegin(GL_LINES);    
  glColor3f(1 ,0 ,0 );
  for(double i = 0; i < 1;i+=0.2){
    glVertex3f(0, i, 0);
    glVertex3f(100, i, 0);
  }

  //y
    glColor3f(0 ,1 ,0 );
  for(double i = 0; i < 1;i+=0.2){
    glVertex3f(i, 0, 0);
    glVertex3f(i, 100, 0);
  }


  //z
    glColor3f(0 ,0 ,1 );
  for(double i = 0; i < 1;i+=0.2){
    glVertex3f(0, i, 0);
    glVertex3f(0, i, 100);
  }
glEnd();

}
