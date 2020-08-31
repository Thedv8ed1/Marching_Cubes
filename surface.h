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
    unsigned char get_index(double *vertValues);
    void marching_cube();
    void generate_triangles(Cube cube);


 Point interpolate(Point p1, Point p2,double v1, double v2){ 
        Point p;    
         p.x = p1.x + (abs(v1)) / (abs(v1) + abs(v2)) * (p2.x - p1.x);
        p.y = p1.y + (abs(v1)) / (abs(v1) + abs(v2)) * (p2.y - p1.y);
        p.z = p1.z + (abs(v1)) / (abs(v1) + abs(v2))* (p2.z - p1.z);
        return p;
        p.x = p1.x + (v1 / (v2 - v1))*(p2.x - p1.x);
        p.y = p1.y + (v1 / (v2 - v1))*(p2.y - p1.y);
        p.z = p1.z + (v1 / (v2 - v1))*(p2.z - p1.z);
    
        return p;
    }

    void render_surface();

    double*** points;

    int width,height,depth;
    std::vector<Triangle> triangles;
    private:

    int edgeTable[256] = {
        0, 265, 515, 778, 1030, 1295, 1541, 1804, 2060, 2309, 2575, 2822, 3082, 3331, 3593, 3840, 400, 
153, 915, 666, 1430, 1183, 1941, 1692, 2460, 2197, 2975, 2710, 3482, 3219, 3993, 3728, 560, 
825, 51, 314, 1590, 1855, 1077, 1340, 2620, 2869, 2111, 2358, 3642, 3891, 3129, 3376, 928, 
681, 419, 170, 1958, 1711, 1445, 1196, 2988, 2725, 2479, 2214, 4010, 3747, 3497, 3232, 1120, 
1385, 1635, 1898, 102, 367, 613, 876, 3180, 3429, 3695, 3942, 2154, 2403, 2665, 2912, 1520, 
1273, 2035, 1786, 502, 255, 1013, 764, 3580, 3317, 4095, 3830, 2554, 2291, 3065, 2800, 1616, 
1881, 1107, 1370, 598, 863, 85, 348, 3676, 3925, 3167, 3414, 2650, 2899, 2137, 2384, 1984, 
1737, 1475, 1226, 966, 719, 453, 204, 4044, 3781, 3535, 3270, 3018, 2755, 2505, 2240, 2240, 
2505, 2755, 3018, 3270, 3535, 3781, 4044, 204, 453, 719, 966, 1226, 1475, 1737, 1984, 2384, 
2137, 2899, 2650, 3414, 3167, 3925, 3676, 348, 85, 863, 598, 1370, 1107, 1881, 1616, 2800, 
3065, 2291, 2554, 3830, 4095, 3317, 3580, 764, 1013, 255, 502, 1786, 2035, 1273, 1520, 2912, 
2665, 2403, 2154, 3942, 3695, 3429, 3180, 876, 613, 367, 102, 1898, 1635, 1385, 1120, 3232, 
3497, 3747, 4010, 2214, 2479, 2725, 2988, 1196, 1445, 1711, 1958, 170, 419, 681, 928, 3376, 
3129, 3891, 3642, 2358, 2111, 2869, 2620, 1340, 1077, 1855, 1590, 314, 51, 825, 560, 3728, 
3993, 3219, 3482, 2710, 2975, 2197, 2460, 1692, 1941, 1183, 1430, 666, 915, 153, 400, 3840, 
3593, 3331, 3082, 2822, 2575, 2309, 2060, 1804, 1541, 1295, 1030, 778, 515, 265, 0 };

    std::pair<int,int> edgeToVertex(int edgeList) {
        if(((edgeList>>0)&1)){return std::make_pair(0,1);}
        else if(((edgeList>>1)&1)){return std::make_pair(1,2);}
        else if(((edgeList>>2)&1)){return std::make_pair(2,3);}
        else if(((edgeList>>3)&1)){return std::make_pair(3,0);}
        else if(((edgeList>>4)&1)){return std::make_pair(4,5);}
        else if(((edgeList>>5)&1)){return std::make_pair(5,6);}
        else if(((edgeList>>6)&1)){return std::make_pair(6,7);}
        else if(((edgeList>>7)&1)){return std::make_pair(7,4);}
        else if(((edgeList>>8)&1)){return std::make_pair(0,4);}
        else if(((edgeList>>9)&1)){return std::make_pair(1,5);}
        else if(((edgeList>>10)&1)){return std::make_pair(2,6);}
        else if(((edgeList>>11)&1)){return std::make_pair(3,7);}
        else{return std::make_pair(-1,-1);}
    };
};