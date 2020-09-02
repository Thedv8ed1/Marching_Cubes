#include "surface.h"
#include <fstream>
#include <iostream>
#include <climits>
#include <string>
#include <cstring>

/*
example: 01010101
every bit flip means we are crossing the isosurface and we need a triangle to representing
the maximum trianges are the amount of bit flips
there are 5 maximim bit flips so there are 5 triangles

rolling the bits accounts for rotation
8 bit rolls sends us back to the original value

*/

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
            }
        }
    }
  file.close();
}


void Surface::marching_cube(){    
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
                generate_triangles(cube);
            }
        }
    }
}

unsigned char Surface::get_index(double *vertValues){
    unsigned char index = 0;
    for(int i = 7; i >= 0; i--){
        vertValues[i] < 0 ? index = index << 1 : index = (index<<1)+1;
    }
    return index;
}

Point Surface::interpolate(Point p1, Point p2, double v1, double v2){
    Point p;   
    p.x = p1.x + (v1 / (v1 - v2))*(p2.x - p1.x);
    p.y = p1.y + (v1 / (v1 - v2))*(p2.y - p1.y);
    p.z = p1.z + (v1 / (v1 - v2))*(p2.z - p1.z);
    return p;
}

std::pair<int,int> Surface::edgeToVertex(int edgeList) {
    switch(edgeList){
        case 1: return std::make_pair(0,1); 
        case 2: return std::make_pair(1,2); 
        case 4: return std::make_pair(2,3);
        case 8: return std::make_pair(3,0);
        case 16: return std::make_pair(4,5);
        case 32: return std::make_pair(5,6);
        case 64: return std::make_pair(6,7);
        case 128: return std::make_pair(7,4);
        case 256: return std::make_pair(0,4);
        case 512: return std::make_pair(1,5);
        case 1024: return std::make_pair(2,6);
        case 2048: return std::make_pair(3,7);
        default: break;
    }
}

void Surface::generate_triangles(Cube cube){    
   unsigned char index; // holds the case of the cube
    // get the index of of the cube from a look up table
    index = get_index(cube.values);

    if(index == 0 ) { return;} 

    Point edgePoints[12];
    int edgeList = edgeTable[index];
    //if(index == 96 ){std::cout << edgeList << std::endl; exit(0);}

    for(int i = 0; i < 12; i++){
        std::pair<int,int> edge2Verts = edgeToVertex(edgeList&(1<<i));
        if(edge2Verts.first == -1){continue;}
        edgePoints[i] = interpolate(cube.verticies[edge2Verts.first],cube.verticies[edge2Verts.second],cube.values[edge2Verts.first],cube.values[edge2Verts.second]);
    }

    for(int edge = 0; edge < triangleTable[index].size(); edge+=3){
        Triangle t;
        t.p[0] = edgePoints[triangleTable[index][edge]];
        t.p[1] = edgePoints[triangleTable[index][edge+1]];
        t.p[2] = edgePoints[triangleTable[index][edge+2]];
        triangles.push_back(t);
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