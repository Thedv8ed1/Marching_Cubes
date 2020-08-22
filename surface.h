#pragma once
#include <GL/glut.h>
#include "grid.h"
#include <stdlib.h>
#include <vector>
#include <utility>
using namespace std;
class lookup {
    private:
        // vector<bool>vertices[8];
        // vector<bool>edges[12];
    public:
        std::vector<std::pair<int, int>>X;        // edges in X plane
        std::vector<std::pair<int, int>>Y;        // edges in Y plane
        std::vector<std::pair<int, int>>Z;        // edges in Z plane
       // std::vector<triangle> triangle_pts;      // vector of possible triangles
        lookup() {};
        lookup(std::vector<std::pair<int, int>>x, std::vector<std::pair<int, int>>y, std::vector<std::pair<int, int>>z) {X = x; Y = y; Z = z;}
};
class Surface{
    public:
    Surface();
    ~Surface();
    void load_dimensions(int x,int y, int z);
    void load_surface_data(char *file);
    int get_index(double *vertValues);
    void generate_triangles();


 Point interpolate(Point p1, Point p2,double v1, double v2){ 
        Point p;    
        p.x = p1.x + (v1 / (v2 - v1))*(p2.x - p1.x);
        p.y = p1.y + (v1 / (v2 - v1))*(p2.y - p1.y);
        p.z = p1.z + (v1 / (v2 - v1))*(p2.z - p1.z);
    
        return p;
    }

    

    void render_surface();

    std::vector<Triangle> triangles;
    double ***points = nullptr; 
    private:
    int width,height,depth;

};


/*


    7----------6        
  / |         /|
 /  |        / |
/   |       /  |
4----------5   |
|   |      |   |   
|  3-------|---2   
| /        |  /
|/         | /
0----------1        

    ----6-----
  / |         /|
 7  11       5 |
/   |       /  10
 ----4-----    |
|   |      |   |   
8   ----2--|---   
| /3       9  /
|/         | /1
 ----0----- 

*/