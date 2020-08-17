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

    if(points != nullptr){std::cout << "TODO DELETE ARRAY" << std::endl;}
    points = new Point**[width];
    for (int x = 0; x < width; x+=1){
        points[x] = new Point*[height];
            for (int y = 0; y < height; y+=1){
                points[x][y] = new Point[depth];
                    for (int z = 0; z < depth; z+=1){
                        points[x][y][z].x = x;
                        points[x][y][z].y = y;
                        points[x][y][z].z = z;
                        points[x][y][z].value = INT_MAX;
                    }
            }
    }

}

void Surface::load_surface_data(char *fileName){

    std::fstream file;
    file.open(fileName);
    std::string s;
    
  do{

    std::getline(file, s);

  }
  while(s[0] == '#');

  for (int z = 0; z < depth; z+=1){
    for (int y = 0; y < height; y+=1){
      for (int x = 0; x < width; x+=1){
        file >> s;// std::cout << s << " ";
        points[x][y][z].x = std::stoi(s);
        file >> s; //std::cout << s << " ";
        points[x][y][z].y = std::stoi(s);
        file >> s; //std::cout << s << " ";
        points[x][y][z].z = std::stoi(s);
        file >> s; //std::cout << s << " ";
        points[x][y][z].value = std::stof(s);
      }
      //std::cout << std::endl;
    }
  }

  file.close();

  generate_triangles();
}