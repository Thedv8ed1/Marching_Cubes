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

int Surface::get_index(double *vertValues){
  int index = 0;
  index += vertValues[0] > 0 ? 0:1;
  index += vertValues[1]> 0 ? 0:2;
  index += vertValues[2]> 0 ? 0:4;
  index += vertValues[3]> 0 ? 0:8;
  index += vertValues[4]> 0 ? 0:16;
  index += vertValues[5]> 0 ? 0:32;
  index += vertValues[6]> 0 ? 0:64;
  index += vertValues[7]> 0 ? 0:128;
  return index;
}

void Surface::generate_triangles(){
  int index;
// the marching bit
 for(int i = 0; i < width-1; i++){
     for(int j = 0; j < height-1; j++){
         for(int k = 0; k<depth-1;k++){
             Cube cube;
             cube.values[0] = points[i  ][j  ][k].value;     cube.verticies[0] = Point{i,  j , k};
             cube.values[1] = points[i+1][j  ][k].value;     cube.verticies[1] = Point{i+1,j,  k};
             cube.values[2] = points[i+1][j  ][k+1].value;   cube.verticies[2] = Point{i+1,j,  k+1};
             cube.values[3] = points[i  ][j  ][k+1].value;   cube.verticies[3] = Point{i,  j,  k+1};
             cube.values[4] = points[i  ][j+1][k].value;     cube.verticies[4] = Point{i , j+1,k};
             cube.values[5] = points[i+1][j+1][k].value;     cube.verticies[5] = Point{i+1,j+1,k};
             cube.values[6] = points[i+1][j+1][k+1].value;   cube.verticies[6] = Point{i+1,j+1,k+1};
             cube.values[7] = points[i  ][j+1][k+1].value;   cube.verticies[7] = Point{i,  j+1,k+1};   

             // get set of edges that cross the surface
             index = get_index(cube.values);
             if(index > 127){
                 index = 255-index;
             }
             if(index == 0) 
                continue;

             
            lookup lookupCube = table[index];
             Point xyz[3];
             if((lookupCube.X.size()> 0) && (lookupCube.Y.size() > 0) && (lookupCube.Z.size() > 0)){
             for (int a = 0; a < lookupCube.X.size(); a++) {
                if (lookupCube.X.at(a).first == 0) {
                    xyz[0] = Point{i+0.5, j+0, k+0}; 
                    xyz[0]=interpolate(cube.verticies[0],cube.verticies[1],cube.values[0],cube.values[1]); 
                }
                else if (lookupCube.X.at(a).first == 3) {
                    xyz[0] = Point{i+0.5, j+0, k+1};
                    xyz[0]=interpolate(cube.verticies[3],cube.verticies[2],cube.values[3],cube.values[2]);
                }
                else if (lookupCube.X.at(a).first == 4) {
                    xyz[0] = Point{i+0.5, j+1, k+0};
                   xyz[0]=interpolate(cube.verticies[4],cube.verticies[5],cube.values[4],cube.values[5]);
                }
                else {
                    xyz[0] = Point{i+0.5, j+1, k+1};  
                   xyz[0]=interpolate(cube.verticies[6],cube.verticies[7],cube.values[6],cube.values[7]);
                }
                for (int b = 0; b < lookupCube.Y.size(); b++) {
                    if (lookupCube.Y.at(b).first == 0) {
                        xyz[1] = Point{i+0, j+0.5, k+0}; 
                        xyz[1]=interpolate(cube.verticies[0],cube.verticies[4],cube.values[0],cube.values[4]);
                    }
                    else if (lookupCube.Y.at(b).first == 1) {
                        xyz[1] = Point{i+1, j+0.5, k+0};
                        xyz[1]=interpolate(cube.verticies[1],cube.verticies[5],cube.values[1],cube.values[5]);
                    }
                    else if (lookupCube.Y.at(b).first == 2) {
                        xyz[1] = Point{i+1, j+0.5, k+1};  
                        xyz[1]=interpolate(cube.verticies[2],cube.verticies[6],cube.values[2],cube.values[6]);   
                    }
                    else {
                        xyz[1] = Point{i+0, j+0.5, k+1};
                        xyz[1]=interpolate(cube.verticies[3],cube.verticies[7],cube.values[3],cube.values[7]);
                    }
                    for (int c = 0; c < lookupCube.Z.size(); c++) {
                        if (lookupCube.Z.at(c).first == 0) {
                            xyz[2] = Point{i+0, j+0, k+0.5};
                            xyz[2]=interpolate(cube.verticies[0],cube.verticies[3],cube.values[0],cube.values[3]);
                        }
                        else if (lookupCube.Z.at(c).first == 1) {
                            xyz[2] = Point{i+1, j+0, k+0.5};
                            xyz[2]=interpolate(cube.verticies[1],cube.verticies[2],cube.values[1],cube.values[2]);
                        }
                        else if (lookupCube.Z.at(c).first == 5) {
                            xyz[2] = Point{i+1, j+1, k+0.5};
                           xyz[2]=interpolate(cube.verticies[5],cube.verticies[6],cube.values[5],cube.values[6]);
                        }
                        else {
                            xyz[2] = Point{i+0, j+1, k+0.5};
                           xyz[2]=interpolate(cube.verticies[4],cube.verticies[7],cube.values[4],cube.values[7]);

                        }
                        triangles.push_back(Triangle{xyz[0],xyz[1],xyz[2]});
                    }
                }
            }
        } // end if

            else if (!lookupCube.Y.size() && !lookupCube.Z.size() && lookupCube.X.size()) {
                    Triangle temp[2];
                    //triangle 1
                    xyz[0] = Point{i,j,k};
                    xyz[0]= interpolate(cube.verticies[0],cube.verticies[1],cube.values[0],cube.values[1]); 
                    xyz[1] = Point{i,j,k+1};
                    xyz[1]= interpolate(cube.verticies[4],cube.verticies[5],cube.values[4],cube.values[5]); 
                    xyz[2] = Point{i,j+1,k+1};
                    xyz[2]= interpolate(cube.verticies[7],cube.verticies[6],cube.values[7],cube.values[6]);
                    temp[0] = Triangle{xyz[0],xyz[1],xyz[2]};
                   
                    //triangle 2
                    xyz[0] = Point{i,j,k};
                    xyz[0]= interpolate(cube.verticies[0],cube.verticies[1],cube.values[0],cube.values[1]); 
                    xyz[1] = Point{i,j+1,k+1};
                    xyz[1]= interpolate(cube.verticies[7],cube.verticies[6],cube.values[7],cube.values[6]);
                    xyz[2] = Point{i,j+1,k};
                    xyz[2]= interpolate(cube.verticies[2],cube.verticies[3],cube.values[2],cube.values[3]);
                    temp[1] = Triangle{xyz[0],xyz[1],xyz[2]};
                    triangles.push_back(temp[0]);
                    triangles.push_back(temp[1]);
            }
            // y
            else if (!lookupCube.X.size() && !lookupCube.Z.size() && lookupCube.Y.size()) {
                    Triangle temp[2];
                    //triangle 1
                    xyz[0] = Point{i,j,k};
                    xyz[0]= interpolate(cube.verticies[0],cube.verticies[4],cube.values[0],cube.values[4]);
                    xyz[1] = Point{i+1,j,k};
                    xyz[1]= interpolate(cube.verticies[1],cube.verticies[5],cube.values[1],cube.values[5]);
                    xyz[2] = Point{i+1,j,k+1};
                    xyz[2]= interpolate(cube.verticies[2],cube.verticies[6],cube.values[2],cube.values[6]);
                    temp[0] = Triangle{xyz[0],xyz[1],xyz[2]};
                    //triangle 2
                    xyz[0] = Point{i,j,k};
                    xyz[0]= interpolate(cube.verticies[0],cube.verticies[4],cube.values[0],cube.values[4]);
                    xyz[1] = Point{i+1,j,k+1};
                    xyz[1]= interpolate(cube.verticies[2],cube.verticies[6],cube.values[2],cube.values[6]);
                    xyz[2] = Point{i,j,k+1};
                    xyz[2]= interpolate(cube.verticies[3],cube.verticies[7],cube.values[3],cube.values[7]);
                    temp[1] = Triangle{xyz[0],xyz[1],xyz[2]};
                    triangles.push_back(temp[0]);
                    triangles.push_back(temp[1]);
            }
            
             else if (!lookupCube.X.size() && !lookupCube.Y.size() && lookupCube.Z.size()) {
                     Triangle temp[2];
                    //triangle 1
                    xyz[0] = Point{i,j,k};
                    xyz[0]= interpolate(cube.verticies[0],cube.verticies[3],cube.values[0],cube.values[3]);
                    xyz[1] = Point{i+1,j,k};
                    xyz[1]= interpolate(cube.verticies[1],cube.verticies[2],cube.values[1],cube.values[2]);
                    xyz[2] = Point{i+1,j+1,k};
                    xyz[2]= interpolate(cube.verticies[5],cube.verticies[6],cube.values[5],cube.values[6]);
                    temp[0] = Triangle{xyz[0],xyz[1],xyz[2]};
                    //triangle 2
                    xyz[0] = Point{i,j,k};
                    xyz[0]= interpolate(cube.verticies[0],cube.verticies[3],cube.values[0],cube.values[3]);
                    xyz[1] = Point{i+1,j+1,k};
                    xyz[1]= interpolate(cube.verticies[1],cube.verticies[2],cube.values[1],cube.values[2]);
                    xyz[2] = Point{i,j+1,k};
                    xyz[1]= interpolate(cube.verticies[4],cube.verticies[7],cube.values[4],cube.values[7]);
                    temp[1] = Triangle{xyz[0],xyz[1],xyz[2]};
                    triangles.push_back(temp[0]);
                    triangles.push_back(temp[1]);
             }
             
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