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

void Surface::load_surface_data(char *fileName){

    std::fstream file;
    file.open(fileName);
    std::string s;
    
    do{  // get surface dimentions and skip over comments
        string line, search;

        // read commentaries
        std::getline(file, line);

        search = "width";
        if (line.find(search) != string::npos)
            height = atoi(line.substr(line.find(search) + search.length()).c_str());

        search = "height";
        if (line.find(search) != string::npos)
            width = atoi(line.substr(line.find(search) + search.length()).c_str());
        
        search = "depth";
        if (line.find(search) != string::npos)
            depth = atoi(line.substr(line.find(search) + search.length()).c_str());
        s = line;
    }
    while(s[0] == '#');
    
    int xIN, yIN, zIN;
    /*
        Create the 3d array of the size spcified in the file
        Assume all points are outside a surface
    */
    points = new double**[width];
    for (int x = 0; x < width; x+=1){
        points[x] = new double*[height];
        for (int y = 0; y < height; y+=1){
            points[x][y] = new double[depth];
            for (int z = 0; z < depth; z+=1){
                points[x][y][z] = INT_MAX;
            }
        }
    }

    /*
        Load the surface data
    */
    for (int x = 0; x < width; x+=1){
        for (int y = 0; y < height; y+=1){
            for (int z = 0; z < depth; z+=1){
                file >> s;
                xIN = std::stoi(s);
                file >> s;
                yIN = std::stoi(s);
                file >> s;
                zIN = std::stoi(s);
                file >> s;
                if(xIN > width || yIN > height || zIN > depth){continue;} // if a point is greater than a specified dimention skip over it
                points[xIN][yIN][zIN] = std::stod(s);               

                std::cout << xIN << " " << yIN << " " << zIN << " " << points[xIN][yIN][zIN]     <<std::endl;      
            }
        }
    }
  file.close();
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
               /*
                cube.values[0] = points[i  ][j  ][k];     cube.verticies[0] = Point{i,  j , k};
                cube.values[1] = points[i+1][j  ][k];     cube.verticies[1] = Point{i+1,j,  k};
                cube.values[2] = points[i+1][j  ][k+1];   cube.verticies[2] = Point{i+1,j,  k+1};
                cube.values[3] = points[i  ][j  ][k+1];   cube.verticies[3] = Point{i,  j,  k+1};
                cube.values[4] = points[i  ][j+1][k];     cube.verticies[4] = Point{i , j+1,k};
                cube.values[5] = points[i+1][j+1][k];     cube.verticies[5] = Point{i+1,j+1,k};
                cube.values[6] = points[i+1][j+1][k+1];   cube.verticies[6] = Point{i+1,j+1,k+1};
                cube.values[7] = points[i  ][j+1][k+1];   cube.verticies[7] = Point{i,  j+1,k+1};   
                */

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