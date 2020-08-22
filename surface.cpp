#include "surface.h"
#include <fstream>
#include <iostream>
#include <climits>
#include <string>
#include <cstring>

Surface::Surface(){

}

Surface::~Surface(){
    
}

void Surface::load_dimensions(int height, int width,int depth){
    this->height = height;
    this->width = width;
    this->depth = depth;


}

void Surface::load_surface_data(char *fileName){

    std::fstream file;
    file.open(fileName);
    std::string s;
    
  do{

    std::getline(file, s);

  }
  while(s[0] == '#');
    int xIN, yIN, zIN;
/*
  for (int z = 0; z < depth; z+=1){
    for (int y = 0; y < height; y+=1){
      for (int x = 0; x < width; x+=1){
        file >> s;// std::cout << s << " ";
        xIN = std::stoi(s);
        file >> s; //std::cout << s << " ";
        yIN = std::stoi(s);
        file >> s; //std::cout << s << " ";
        zIN = std::stoi(s);
        file >> s; //std::cout << s << " ";
        points[xIN][yIN][zIN] = std::stod(s);
      }
      //std::cout << std::endl;
    }
  }
  */

  file.close();

  generate_triangles();
}

int Surface::get_index(double *vertValues){
  int index = 0;
  for(int i = 7; i >= 0; i--){
      vertValues[i] > 0 ? index = index << 1 : index = (index<<1)+1;
  }
 
  return index;
}

void Surface::generate_triangles(){

    int index;
    Cube cube;

    /*
    Iterate over the 3d matrix that holds the weight at each point
    */
    for(int i = 0; i < width-1; i++){
        for(int j = 0; j < height-1; j++){
            for(int k = 0; k < depth-1; k++){
                /*
                    Make a sample cube to analyze
                */
                cube.values[0] = points[i  ][j  ][k];     cube.verticies[0] = Point{i,  j , k};
                cube.values[1] = points[i+1][j  ][k];     cube.verticies[1] = Point{i+1,j,  k};
                cube.values[2] = points[i+1][j  ][k+1];   cube.verticies[2] = Point{i+1,j,  k+1};
                cube.values[3] = points[i  ][j  ][k+1];   cube.verticies[3] = Point{i,  j,  k+1};
                cube.values[4] = points[i  ][j+1][k];     cube.verticies[4] = Point{i , j+1,k};
                cube.values[5] = points[i+1][j+1][k];     cube.verticies[5] = Point{i+1,j+1,k};
                cube.values[6] = points[i+1][j+1][k+1];   cube.verticies[6] = Point{i+1,j+1,k+1};
                cube.values[7] = points[i  ][j+1][k+1];   cube.verticies[7] = Point{i,  j+1,k+1};   

                // get the index of of the cube from a look up table
                index = get_index(cube.values);
                if(index > 127){
                    index = 255-index;
                }
                if(index == 0) 
                    continue;
                    
                Point xyz[3];

            }
        }

    }
}
void Surface::render_surface(){
  for(int i = 0; i < triangles.size(); i++){
    glColor3f(0.560784   ,0.560784   ,0.737255);
    glBegin(GL_TRIANGLES);
    glVertex3f(triangles[i].p[0].x,triangles[i].p[0].y,triangles[i].p[0].z);
    glVertex3f(triangles[i].p[1].x,triangles[i].p[1].y,triangles[i].p[1].z);
    glVertex3f(triangles[i].p[2].x,triangles[i].p[2].y,triangles[i].p[2].z);
    glEnd();

    glColor3f(1, 0, 0.25);
    glBegin(GL_LINES);
    glVertex3f(triangles[i].p[0].x,triangles[i].p[0].y,triangles[i].p[0].z);
    glVertex3f(triangles[i].p[1].x,triangles[i].p[1].y,triangles[i].p[1].z);

    glVertex3f(triangles[i].p[1].x,triangles[i].p[1].y,triangles[i].p[1].z);
    glVertex3f(triangles[i].p[2].x,triangles[i].p[2].y,triangles[i].p[2].z);

    glVertex3f(triangles[i].p[0].x,triangles[i].p[0].y,triangles[i].p[0].z);
    glVertex3f(triangles[i].p[2].x,triangles[i].p[2].y,triangles[i].p[2].z);
    glEnd();

  }
}