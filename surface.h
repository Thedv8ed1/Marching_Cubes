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
        p.x = p1.x + (abs(v1)) / (abs(v1) + abs(v2))* (p2.x - p1.x);
        p.y = p1.y + (abs(v1)) / (abs(v1) + abs(v2))*(p2.y - p1.y);
        p.z = p1.z + (abs(v1)) / (abs(v1) + abs(v2))*(p2.z - p1.z);
        return p;
    }

    

    void render_surface();

    std::vector<Triangle> triangles;
    Point ***points = nullptr;
    private:
    int width,height,depth;
vector<lookup> table = {
/*0*/   lookup(),
/*1*/   lookup({make_pair(0, 1)}, {make_pair(0, 4)}, {make_pair(0, 3)}),
/*2*/   lookup({make_pair(0, 1)}, {make_pair(1, 5)}, {make_pair(1, 2)}), 
/*3*/   lookup({}, {make_pair(0, 4), make_pair(1, 5)}, {make_pair(0, 3), make_pair(1, 2)}),
/*4*/   lookup({make_pair(3, 2)}, {make_pair(2, 6)}, {make_pair(1, 2)}),
/*5*/   lookup({make_pair(0, 1), make_pair(3, 2)}, {make_pair(0, 4), make_pair(2, 6)}, {make_pair(0, 3), make_pair(1, 2)}),
/*6*/   lookup({make_pair(0, 1), make_pair(3, 2)}, {make_pair(1, 5), make_pair(2, 6)}, {}),
/*7*/   lookup({make_pair(3, 2)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6)}, {make_pair(0, 3)}),
/*8*/   lookup({make_pair(3, 2)}, {make_pair(3, 7)}, {make_pair(0, 3)}),
/*9*/   lookup({make_pair(0, 1), make_pair(3, 2)}, {make_pair(0, 4), make_pair(3, 7)}, {}),
/*10*/  lookup({make_pair(0, 1), make_pair(3, 2)}, {make_pair(1, 5), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2)}),
/*11*/  lookup({make_pair(3, 2)}, {make_pair(0, 4), make_pair(1, 5), make_pair(3, 7)}, {make_pair(1, 2)}),
/*12*/  lookup({}, {make_pair(3, 7), make_pair(2, 6)}, {make_pair(0, 3), make_pair(1, 2)}), 
/*13*/  lookup({make_pair(0, 1)}, {make_pair(0, 4), make_pair(3, 7), make_pair(2, 6)}, {make_pair(1, 2)}),
/*14*/  lookup({make_pair(0, 1)}, {make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3)}),
/*15*/  lookup({}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {}),
/*16*/  lookup({make_pair(4, 5)}, {make_pair(0, 4)}, {make_pair(4, 7)}),
/*17*/  lookup({make_pair(0, 1), make_pair(4, 5)}, {}, {make_pair(0, 3), make_pair(4, 7)}),
/*18*/  lookup({make_pair(0, 1), make_pair(4, 5)}, {make_pair(0, 4), make_pair(1, 5)}, {make_pair(1, 2), make_pair(4, 7)}),
/*19*/  lookup({make_pair(4, 5)}, {make_pair(1, 5)}, {make_pair(0, 3), make_pair(4, 7), make_pair(1, 2)}),
/*20*/  lookup({make_pair(4, 5), make_pair(3, 2)}, {make_pair(0, 4), make_pair(2, 6)}, {make_pair(0, 3), make_pair(1, 2)}),
/*21*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5)}, {make_pair(2, 6)}, {make_pair(0, 3), make_pair(1, 2), make_pair(4, 7)}),
/*22*/  lookup({make_pair(4, 5)}, {make_pair(1, 5)}, {make_pair(0, 3), make_pair(1, 2), make_pair(4, 7)}),
/*23*/  lookup({make_pair(4, 5), make_pair(3, 2)}, {make_pair(1, 5), make_pair(2, 6)}, {make_pair(0, 3), make_pair(4, 7)}),
/*24*/  lookup({make_pair(3, 2), make_pair(4, 5)}, {make_pair(0, 4), make_pair(3, 7)}, {make_pair(0, 3), make_pair(4, 7)}),
/*25*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5)}, {make_pair(3, 7)}, {make_pair(4, 7)}),
/*26*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5)}, {make_pair(0, 4), make_pair(1, 5), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2), make_pair(4, 7)}),
/*27*/  lookup({make_pair(4, 5), make_pair(3, 2)}, {make_pair(1, 5), make_pair(3, 7)}, {make_pair(1, 2), make_pair(4, 7)}),
/*28*/  lookup({make_pair(4, 5)}, {make_pair(0, 4), make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2), make_pair(4, 7)}),
/*29*/  lookup({make_pair(0, 1), make_pair(4, 5)}, {make_pair(2, 6), make_pair(3, 7)}, {make_pair(1, 2), make_pair(4, 7)}),
/*30*/  lookup({make_pair(0, 1), make_pair(4, 5)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(4, 7)}),
/*31*/  lookup({make_pair(4, 5)}, {make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(4, 7)}),
/*32*/  lookup({make_pair(4, 5)}, {make_pair(1, 5)}, {make_pair(5, 6)}),
/*33*/  lookup({make_pair(4, 5), make_pair(0, 1)}, {make_pair(1, 5), make_pair(0, 4)}, {make_pair(5, 6), make_pair(0, 3)}),
/*34*/  lookup({make_pair(0, 1), make_pair(4, 5)}, {}, {make_pair(1, 2), make_pair(5, 6)}),
/*35*/  lookup({make_pair(4, 5)}, {make_pair(0, 4)}, {make_pair(0, 3), make_pair(1, 2), make_pair(5, 6)}),
/*36*/  lookup({make_pair(4, 5), make_pair(3, 2)}, {make_pair(1, 5), make_pair(2, 6)}, {make_pair(1, 2), make_pair(5, 6)}),
/*37*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6)}, {make_pair(0, 3), make_pair(1, 2), make_pair(5, 6)}),
/*38*/  lookup({make_pair(0, 1), make_pair(4, 5), make_pair(3, 2)}, {make_pair(2, 6)}, {make_pair(5, 6)}),
/*39*/  lookup({make_pair(3, 2), make_pair(4, 5)}, {make_pair(0, 4), make_pair(2, 6)}, {make_pair(0, 3), make_pair(5, 6)}),
/*40*/  lookup({make_pair(4, 5), make_pair(3, 2)}, {make_pair(1, 5), make_pair(3, 7)}, {make_pair(0, 3), make_pair(5, 6)}),
/*41*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5)}, {make_pair(0, 4), make_pair(3, 7), make_pair(1, 5)}, {make_pair(5, 6)}),
/*42*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 4)}, {make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2), make_pair(5, 6)}),
/*43*/  lookup({make_pair(4, 5), make_pair(3, 2)}, {make_pair(0, 4), make_pair(3, 7)}, {make_pair(1, 2), make_pair(5, 6)}),
/*44*/  lookup({make_pair(4, 5)}, {make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2), make_pair(5, 6)}),
/*45*/  lookup({make_pair(0, 1), make_pair(4, 5)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(1, 2), make_pair(5, 6)}),
/*46*/  lookup({make_pair(0, 1), make_pair(4, 5)}, {make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(5, 6)}),
/*47*/  lookup({make_pair(4, 5)}, {make_pair(0, 4), make_pair(3, 7), make_pair(2, 6)}, {make_pair(5, 6)}),
/*48*/  lookup({}, {make_pair(0, 4), make_pair(1, 5)}, {make_pair(4, 7), make_pair(5, 6)}),        
/*49*/  lookup({make_pair(0, 1)}, {make_pair(1, 5)}, {make_pair(0, 3), make_pair(4, 7), make_pair(5, 6)}),
/*50*/  lookup({make_pair(0, 1)}, {make_pair(0, 4)}, {make_pair(1, 2), make_pair(4, 7), make_pair(5, 6)}),
/*51*/  lookup({}, {}, {make_pair(0, 3), make_pair(1, 2), make_pair(5, 6), make_pair(4, 7)}),
/*52*/  lookup({make_pair(3, 2)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6)}, {make_pair(1, 2), make_pair(5, 6), make_pair(4, 7)}),
/*53*/  lookup({make_pair(0, 1), make_pair(3, 2)}, {make_pair(1, 5), make_pair(2, 6)}, {make_pair(0, 3), make_pair(1, 2), make_pair(4, 7), make_pair(5, 6)}),
/*54*/  lookup({make_pair(0, 1), make_pair(3, 2)}, {make_pair(0, 4), make_pair(2, 6)}, {make_pair(4, 7), make_pair(5, 6)}),
/*55*/  lookup({make_pair(3, 2)}, {make_pair(2, 6)}, {make_pair(0, 3), make_pair(5, 6), make_pair(4, 7)}),
/*56*/  lookup({make_pair(3, 2)}, {make_pair(0, 4), make_pair(1, 5), make_pair(3, 7)}, {make_pair(0, 3), make_pair(4, 7), make_pair(5, 6)}),
/*57*/  lookup({make_pair(0, 1), make_pair(3, 2)}, {make_pair(1, 5), make_pair(3, 7)}, {make_pair(4, 7), make_pair(5, 6)}),
/*58*/  lookup({make_pair(0, 1), make_pair(3, 2)}, {make_pair(0, 4), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2), make_pair(4, 7), make_pair(5, 6)}),
/*59*/  lookup({make_pair(3, 2)}, {make_pair(3, 7)}, {make_pair(4, 7), make_pair(5, 6), make_pair(1, 2)}),
/*60*/  lookup({}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2), make_pair(5, 6), make_pair(4, 7)}),
/*61*/  lookup({make_pair(0, 1)}, {make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(4, 7), make_pair(5, 6), make_pair(1, 2)}),
/*62*/  lookup({make_pair(0, 1)}, {make_pair(0, 4), make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(4, 7), make_pair(5, 6)}),
/*63*/  lookup({}, {make_pair(3, 7), make_pair(2, 6)}, {make_pair(4, 7), make_pair(5, 6)}),
/*64*/  lookup({make_pair(0, 1)}, {make_pair(0, 4)}, {make_pair(0, 3)}),
/*65*/  lookup({make_pair(0, 1), make_pair(7, 6)}, {make_pair(0, 4), make_pair(2, 6)}, {make_pair(0, 3), make_pair(5, 6)}),
/*66*/  lookup({make_pair(0, 1), make_pair(7, 6)}, {make_pair(1, 5), make_pair(2, 6)}, {make_pair(2, 4), make_pair(5, 6)}),
/*67*/  lookup({make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6)}, {make_pair(0, 3), make_pair(1, 2), make_pair(5, 6)}),
/*68*/  lookup({make_pair(3, 2), make_pair(7, 6)}, {}, {make_pair(1, 2), make_pair(5, 6)}),
/*69*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(7, 6)}, {make_pair(0, 4)}, {make_pair(0, 3), make_pair(1, 2), make_pair(5, 6)}),        // nice
/*70*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(7, 6)}, {make_pair(1, 5)}, {make_pair(5, 6)}),
/*71*/  lookup({make_pair(7, 6), make_pair(3, 2)}, {make_pair(0, 4), make_pair(1, 5)}, {make_pair(0, 3), make_pair(5, 6)}),
/*72*/  lookup({make_pair(3, 2), make_pair(7, 6)}, {make_pair(3, 7), make_pair(2, 6)}, {make_pair(0, 3), make_pair(5, 6)}),
/*73*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(7, 6)}, {make_pair(0, 4), make_pair(2, 6), make_pair(3, 7)}, {make_pair(5, 6)}),
/*74*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(7, 6)}, {make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2), make_pair(5, 6)}),
/*75*/  lookup({make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(1, 2), make_pair(5, 6)}),
/*76*/  lookup({make_pair(7, 6)}, {make_pair(3, 7)}, {make_pair(5, 6), make_pair(1, 2), make_pair(0, 3)}),
/*77*/  lookup({make_pair(0, 1), make_pair(7, 6)}, {make_pair(0, 4), make_pair(3, 7)}, {make_pair(5, 6), make_pair(1, 2)}),
/*78*/  lookup({make_pair(0, 1), make_pair(7, 6)}, {make_pair(1, 5), make_pair(3, 7)}, {make_pair(0, 3), make_pair(5, 6)}),
/*79*/  lookup({make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5), make_pair(3, 7)}, {make_pair(5, 6)}),
/*80*/  lookup({make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(2, 6)}, {make_pair(4, 7), make_pair(5, 6)}),
/*81*/  lookup({make_pair(0, 1), make_pair(4, 5), make_pair(7, 6)}, {make_pair(2, 6)}, {make_pair(0, 3), make_pair(5, 6), make_pair(4, 7)}),
/*82*/  lookup({make_pair(0, 1), make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6)}, {make_pair(1, 2), make_pair(5, 6), make_pair(4, 7)}),
/*83*/  lookup({make_pair(4, 5), make_pair(7, 6)}, {make_pair(1, 5), make_pair(2, 6)}, {make_pair(0, 3), make_pair(1, 2), make_pair(5, 6), make_pair(4, 7)}),
/*84*/  lookup({make_pair(4, 5), make_pair(3, 2), make_pair(7, 6)}, {make_pair(0, 4)}, {make_pair(5, 6), make_pair(1, 2), make_pair(4, 7)}),
/*85*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5), make_pair(7, 6)}, {}, {make_pair(0, 3), make_pair(1, 2), make_pair(5, 6), make_pair(4, 7)}),
/*86*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5)}, {make_pair(4, 7), make_pair(5, 6)}),
/*87*/  lookup({make_pair(0, 1), make_pair(4, 5), make_pair(7, 6)}, {make_pair(1, 5)}, {make_pair(0, 3), make_pair(4, 7), make_pair(5, 6)}),
/*88*/  lookup({make_pair(3, 2), make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(4, 7), make_pair(5, 6)}),
/*89*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5), make_pair(7, 6)}, {make_pair(2, 6), make_pair(3, 7)}, {make_pair(4, 7), make_pair(5, 6)}),
/*90*/  lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2), make_pair(4, 7), make_pair(5, 6)}),
/*91*/  lookup({make_pair(3, 2), make_pair(4, 5), make_pair(7, 6)}, {make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(1, 2), make_pair(4, 7), make_pair(5, 6)}),
/*92*/  lookup({make_pair(7, 6)}, {make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2), make_pair(4, 7), make_pair(5, 6)}),
/*93*/  lookup({make_pair(0, 1), make_pair(4, 5), make_pair(7, 6)}, {make_pair(3, 7)}, {make_pair(1, 2), make_pair(4, 7), make_pair(5, 6)}),
/*94*/  lookup({make_pair(0, 1), make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6)}, {make_pair(0, 3), make_pair(4, 5), make_pair(7, 6)}),
/*95*/  lookup({make_pair(4, 5), make_pair(7, 6)}, {make_pair(1, 5), make_pair(3, 7)}, {make_pair(4, 7), make_pair(5, 6)}),
/*96*/  lookup({make_pair(4, 5), make_pair(7, 6)}, {make_pair(1, 5), make_pair(2, 6)}, {}),
/*97*/  lookup({make_pair(0, 1), make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6)}, {make_pair(0, 3)}),
/*98*/  lookup({make_pair(0, 1), make_pair(4, 5), make_pair(7, 6)}, {make_pair(2, 6)}, {make_pair(1, 2)}),
/*99*/  lookup({make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(2, 6)}, {make_pair(0, 3), make_pair(1, 2)}),
/*100*/ lookup({make_pair(3, 2), make_pair(4, 5), make_pair(7, 6)}, {make_pair(1, 5)}, {make_pair(1, 2)}),
/*101*/ lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5)}, {make_pair(0, 3), make_pair(1, 2)}),
/*102*/ lookup({make_pair(0, 1), make_pair(3, 2), make_pair(7, 6), make_pair(4, 5)}, {}, {}),
/*103*/ lookup({make_pair(3, 2), make_pair(7, 6), make_pair(4, 5)}, {make_pair(0, 4)}, {make_pair(0, 3)}),
/*104*/ lookup({make_pair(4, 5), make_pair(3, 2), make_pair(7, 6)}, {make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3)}),
/*105*/ lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {}),
/*106*/ lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5), make_pair(7, 6)}, {make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2)}),
/*107*/ lookup({make_pair(0, 1), make_pair(3, 2), make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(3, 7)}, {make_pair(1, 2)}),
/*108*/ lookup({make_pair(4, 5), make_pair(7, 6)}, {make_pair(1, 5), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2)}),
/*109*/ lookup({make_pair(0, 1), make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5), make_pair(3, 7)}, {make_pair(1, 2)}),
/*110*/ lookup({make_pair(0, 1), make_pair(7, 6), make_pair(4, 5)}, {make_pair(3, 7)}, {make_pair(0, 3)}),
/*111*/ lookup({make_pair(4, 5), make_pair(7, 6)}, {make_pair(0, 4), make_pair(3, 7)}, {}),
/*112*/ lookup({make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6)}, {make_pair(4, 7)}),
/*113*/ lookup({make_pair(0, 1), make_pair(7, 6)}, {make_pair(1, 5), make_pair(2, 6)}, {make_pair(0, 3), make_pair(4, 7)}),
/*114*/ lookup({make_pair(0, 1), make_pair(7, 6)}, {make_pair(0, 4), make_pair(2, 6)}, {make_pair(1, 2), make_pair(4, 7)}),
/*115*/ lookup({make_pair(7, 6)}, {make_pair(2, 6)}, {make_pair(4, 7), make_pair(0, 3), make_pair(1, 2)}),
/*116*/ lookup({make_pair(3, 2), make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5)}, {make_pair(4, 7), make_pair(1, 2)}),
/*117*/ lookup({make_pair(0, 1), make_pair(3, 2), make_pair(7, 6)}, {make_pair(1, 5)}, {make_pair(0, 3), make_pair(1, 2), make_pair(4, 7)}),
/*118*/ lookup({make_pair(0, 1), make_pair(3, 2), make_pair(7, 6)}, {make_pair(0, 4)}, {make_pair(4, 7)}),
/*119*/ lookup({make_pair(7, 6), make_pair(3, 2)}, {}, {make_pair(0, 3), make_pair(4, 7)}),
/*120*/ lookup({make_pair(7, 6), make_pair(3, 2)}, {make_pair(0, 4), make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(4, 7)}),
/*121*/ lookup({make_pair(0, 1), make_pair(3, 2), make_pair(7, 6)}, {make_pair(1, 5), make_pair(2, 6), make_pair(3, 7)}, {make_pair(4, 7)}),
/*122*/ lookup({make_pair(0, 1), make_pair(3, 2), make_pair(7, 6)}, {make_pair(0, 4), make_pair(2, 6), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2), make_pair(4, 7)}),
/*123*/ lookup({make_pair(3, 2), make_pair(7, 6)}, {make_pair(2, 6), make_pair(3, 7)}, {make_pair(1, 2), make_pair(4, 7)}),
/*124*/ lookup({make_pair(7, 6)}, {make_pair(0, 4), make_pair(1, 5), make_pair(3, 7)}, {make_pair(0, 3), make_pair(1, 2), make_pair(4, 7)}),
/*125*/ lookup({make_pair(0, 1), make_pair(7, 6)}, {make_pair(1, 5), make_pair(3, 7)}, {make_pair(1, 2), make_pair(4, 7)}),
/*126*/ lookup({make_pair(0, 1), make_pair(7, 6)}, {make_pair(0, 4), make_pair(3, 7)}, {make_pair(0, 3), make_pair(4, 7)}),
/*127*/ lookup({make_pair(7, 6)}, {make_pair(3, 7)}, {make_pair(4, 7)}),
};
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