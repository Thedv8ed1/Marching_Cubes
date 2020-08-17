#pragma once
#include <GL/glut.h>
#include "grid.h"
#include <stdlib.h>
#include <vector>
#include <utility>
enum AXIS{
    X=0,
    Y,
    Z,
};
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
    int get_index(double *vertValues){
        int index;
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
    void generate_triangles(){
        
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
             for (int a = 0; a < lookupCube.X.size(); ++a) {
                if (lookupCube.X.at(a).first == 0) {
                    xyz[0] = Point{i+0.5, j+0, k+0}; 
                    //xyz[0] = Point{0.5, 0, 0}; 
                    //xyz[0].x = interpolate(cube.values[0],cube.values[1]);
                    xyz[0]=interpolate2(cube.verticies[0],cube.verticies[1],cube.values[0],cube.values[1]);           
                }
                else if (lookupCube.X.at(a).first == 3) {
                    xyz[0] = Point{i+0.5, j+0, k+1};
                    //xyz[0] = Point{0.5, 0, 1};
                    //xyz[0].x = interpolate(cube.values[3],cube.values[2]);
                    xyz[0]=interpolate2(cube.verticies[3],cube.verticies[2],cube.values[3],cube.values[2]);
                }
                else if (lookupCube.X.at(a).first == 4) {
                    xyz[0] = Point{i+0.5, j+1, k+0};
                    //xyz[0] = Point{0.5, 1, 0};
                   // xyz[0].x = interpolate(cube.values[4],cube.values[5]); 
                   xyz[0]=interpolate2(cube.verticies[4],cube.verticies[5],cube.values[4],cube.values[5]);           
                }
                else {
                    xyz[0] = Point{i+0.5, j+1, k+1};  
                    //xyz[0] = Point{0.5, 1, 1};
                    //xyz[0].x = interpolate(cube.values[6],cube.values[7]);  
                    xyz[0]=interpolate2(cube.verticies[6],cube.verticies[7],cube.values[6],cube.values[7]);        
                }
                for (int b = 0; b < lookupCube.Y.size(); ++b) {
                    if (lookupCube.Y.at(b).first == 0) {
                        xyz[1] = Point{i+0, j+0.5, k+0}; 
                        //xyz[1] = Point{0, 0.5, 0}; 
                        //xyz[1].y = interpolate(cube.values[0],cube.values[4]); 
                        xyz[1]=interpolate2(cube.verticies[0],cube.verticies[4],cube.values[0],cube.values[4]);          
                    }
                    else if (lookupCube.Y.at(b).first == 1) {
                        xyz[1] = Point{i+1, j+0.5, k+0};
                        //xyz[1] = Point{1, 0.5, 0};
                        //xyz[1].y = interpolate(cube.values[1],cube.values[5]);
                        xyz[1]=interpolate2(cube.verticies[1],cube.verticies[5],cube.values[1],cube.values[5]);
                    }
                    else if (lookupCube.Y.at(b).first == 2) {
                        xyz[1] = Point{i+1, j+0.5, k+1};  
                        //xyz[1] = Point{1, 0.5, 1}; 
                        //xyz[1].y = interpolate(cube.values[2],cube.values[6]); 
                        xyz[1]=interpolate2(cube.verticies[2],cube.verticies[6],cube.values[2],cube.values[6]);         
                    }
                    else {
                        xyz[1] = Point{i+0, j+0.5, k+1};
                        //xyz[1] = Point{0, 0.5, 1};
                        //xyz[1].y = interpolate(cube.values[3],cube.values[7]); 
                        xyz[1]=interpolate2(cube.verticies[3],cube.verticies[7],cube.values[3],cube.values[7]);           
                    }
                    for (int c = 0; c < lookupCube.Z.size(); ++c) {
                        if (lookupCube.Z.at(c).first == 0) {
                            xyz[2] = Point{i+0, j+0, k+0.5};
                            //xyz[2] = Point{0, 0, 0.5};
                            //xyz[2].z = interpolate(cube.values[0],cube.values[3]);
                            xyz[2]=interpolate2(cube.verticies[0],cube.verticies[3],cube.values[0],cube.values[3]);
                        }
                        else if (lookupCube.Z.at(c).first == 1) {
                            xyz[2] = Point{i+1, j+0, k+0.5};
                            //xyz[2] = Point{1, 0, 0.5};
                           // xyz[2].z = interpolate(cube.values[1],cube.values[2]);
                            xyz[2]=interpolate2(cube.verticies[1],cube.verticies[2],cube.values[1],cube.values[2]);
                        }
                        else if (lookupCube.Z.at(c).first == 5) {
                            xyz[2] = Point{i+1, j+1, k+0.5};
                            //xyz[2] = Point{1, 1, 0.5};
                           // xyz[2].z = interpolate(cube.values[5],cube.values[6]);
                           xyz[2]=interpolate2(cube.verticies[5],cube.verticies[6],cube.values[5],cube.values[6]);
                        }
                        else {
                            xyz[2] = Point{i+0, j+1, k+0.5};
                            //xyz[2] = Point{0, 1, 0.5};
                            //xyz[2].z = interpolate(cube.values[4],cube.values[7]);
                            xyz[2]=interpolate2(cube.verticies[4],cube.verticies[7],cube.values[4],cube.values[7]);
                        }
                        triangles.push_back(Triangle{xyz[0],xyz[1],xyz[2]});
                    }
                }
            }
         }
     }
 }

    } 

 Point interpolate2(Point p1, Point p2,double v1, double v2){ 
        Point p;    
        p.x = p1.x + (abs(v1)) / (abs(v1) + abs(v2)) * (p2.x - p1.x);
        p.y = p1.y + (abs(v1)) / (abs(v1) + abs(v2)) * (p2.y - p1.y);
        p.z = p1.z + (abs(v1)) / (abs(v1) + abs(v2)) * (p2.z - p1.z);
        return p;
    }
    double interpolate(double v1, double v2){ 
       if (v1 > v2) {
         return abs(v2)/(abs(v1) + abs(v2));
       }
       else {
        return abs(v1)/(abs(v1) + abs(v2));
       }
    }

    void render_surface(){

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

    std::vector<Triangle> triangles;
    Point ***points = nullptr;
    private:
    int width,height,depth;
std::vector<lookup> table = {
/*0*/   lookup(),
/*1*/   lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*2*/   lookup({std::make_pair(0, 1)}, {std::make_pair(1, 5)}, {std::make_pair(1, 2)}), 
/*3*/   lookup({}, {std::make_pair(0, 4), std::make_pair(1, 5)}, {std::make_pair(0, 3), std::make_pair(1, 2)}),
/*4*/   lookup({std::make_pair(3, 2)}, {std::make_pair(6, 2)}, {std::make_pair(1, 2)}),
/*5*/   lookup({std::make_pair(0, 1), std::make_pair(2, 3)}, {std::make_pair(0, 4), std::make_pair(2, 6)}, {std::make_pair(0, 3), std::make_pair(1, 2)}),
/*6*/   lookup({std::make_pair(0, 1), std::make_pair(3, 2)}, {std::make_pair(1, 5), std::make_pair(2, 6)}, {}),
/*7*/   lookup({std::make_pair(3, 2)}, {std::make_pair(0, 4), std::make_pair(1, 5), std::make_pair(2, 6)}, {std::make_pair(0, 3)}),
/*8*/   lookup({std::make_pair(3, 2)}, {std::make_pair(3, 7)}, {std::make_pair(0, 3)}),
/*9*/   lookup({std::make_pair(0, 1), std::make_pair(3, 2)}, {std::make_pair(0, 4), std::make_pair(3, 7)}, {}),
/*10*/  lookup({std::make_pair(0, 1), std::make_pair(2, 3)}, {std::make_pair(1, 5), std::make_pair(3, 7)}, {std::make_pair(0, 3), std::make_pair(1, 2)}),
/*11*/  lookup({std::make_pair(3, 2)}, {std::make_pair(0, 4), std::make_pair(1, 5), std::make_pair(3, 7)}, {std::make_pair(1, 2)}),
/*12*/  lookup({}, {std::make_pair(3, 7), std::make_pair(2, 6)}, {std::make_pair(0, 3), std::make_pair(1, 2)}), 
/*13*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4), std::make_pair(3, 7), std::make_pair(2, 6)}, {std::make_pair(1, 2)}),
/*14*/  lookup({std::make_pair(0, 1)}, {std::make_pair(1, 5), std::make_pair(2, 6), std::make_pair(3, 7)}, {std::make_pair(0, 3)}),
/*15*/  lookup({}, {std::make_pair(0, 4), std::make_pair(1, 5), std::make_pair(2, 6), std::make_pair(3, 7)}, {}),
/*16*/  lookup({std::make_pair(4, 5)}, {std::make_pair(0, 4)}, {std::make_pair(4, 7)}),
/*17*/  lookup({std::make_pair(0, 1), std::make_pair(4, 5)}, {}, {std::make_pair(0, 3), std::make_pair(4, 7)}),
/*18*/  lookup({std::make_pair(0, 1), std::make_pair(4, 5)}, {std::make_pair(0, 4), std::make_pair(1, 5)}, {std::make_pair(1, 2), std::make_pair(4, 7)}),
/*19*/  lookup({std::make_pair(4, 5)}, {std::make_pair(1, 5)}, {std::make_pair(0, 3), std::make_pair(4, 7), std::make_pair(1, 2)}),
/*20*/  lookup({std::make_pair(4, 5), std::make_pair(2, 3)}, {std::make_pair(0, 4), std::make_pair(2, 6)}, {std::make_pair(0, 3), std::make_pair(1, 2)}),

/*21*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*22*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*23*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*24*/  lookup({std::make_pair(3, 2), std::make_pair(4, 5)}, {std::make_pair(0, 4), std::make_pair(3, 7)}, {std::make_pair(0, 3), std::make_pair(4, 7)}),
/*25*/  lookup({std::make_pair(0, 1), std::make_pair(3, 2), std::make_pair(4, 5)}, {std::make_pair(3, 7)}, {std::make_pair(4, 7)}),

/*26*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*27*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*28*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*29*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*30*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*31*/  lookup({std::make_pair(4, 5)}, {std::make_pair(1, 5), std::make_pair(2, 6), std::make_pair(3, 7)}, {std::make_pair(4, 7)}),
/*32*/  lookup({std::make_pair(4, 5)}, {std::make_pair(1, 5)}, {std::make_pair(5, 6)}),
/*33*/  lookup({std::make_pair(4, 5), std::make_pair(0, 1)}, {std::make_pair(1, 5), std::make_pair(0, 4)}, {std::make_pair(5, 6), std::make_pair(0, 3)}),
/*34*/  lookup({std::make_pair(4, 5), std::make_pair(0, 1)}, {}, {std::make_pair(5, 6), std::make_pair(1, 2)}),
/*35*/  lookup({std::make_pair(4, 5)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3), std::make_pair(1, 2), std::make_pair(5, 6)}),
/*36*/  lookup({std::make_pair(4, 5), std::make_pair(2, 3)}, {std::make_pair(1, 5), std::make_pair(2, 6)}, {std::make_pair(1, 2), std::make_pair(5, 6)}),

/*37*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*38*/  lookup({std::make_pair(0, 1), std::make_pair(4, 5), std::make_pair(3, 2)}, {std::make_pair(2, 6)}, {std::make_pair(5, 6)}),

/*39*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*40*/  lookup({std::make_pair(4, 5), std::make_pair(2, 3)}, {std::make_pair(1, 5), std::make_pair(3, 7)}, {std::make_pair(0, 3), std::make_pair(5, 6)}),

/*41*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*42*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*43*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*44*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*45*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*46*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*47*/  lookup({std::make_pair(4, 5)}, {std::make_pair(0, 4), std::make_pair(3, 7), std::make_pair(2, 6)}, {std::make_pair(5, 6)}),
/*48*/  lookup({}, {std::make_pair(0, 4), std::make_pair(1, 5)}, {std::make_pair(4, 7), std::make_pair(5, 6)}),        
/*49*/  lookup({std::make_pair(0, 1)}, {std::make_pair(1, 5)}, {std::make_pair(0, 3), std::make_pair(4, 7), std::make_pair(5, 6)}),
/*50*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(1, 2), std::make_pair(4, 7), std::make_pair(5, 6)}),

/*51*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*52*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*53*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*54*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*55*/  lookup({std::make_pair(3, 2)}, {std::make_pair(2, 6)}, {std::make_pair(0, 3), std::make_pair(5, 6), std::make_pair(4, 7)}),

/*56*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*57*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*58*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*59*/  lookup({std::make_pair(3, 2)}, {std::make_pair(3, 7)}, {std::make_pair(4, 7), std::make_pair(5, 6), std::make_pair(1, 2)}),

/*60*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*61*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*62*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*63*/  lookup({}, {std::make_pair(3, 7), std::make_pair(2, 6)}, {std::make_pair(4, 7), std::make_pair(5, 6)}),
/*64*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*65*/  lookup({std::make_pair(0, 1), std::make_pair(6, 7)}, {std::make_pair(0, 4), std::make_pair(2, 6)}, {std::make_pair(0, 3), std::make_pair(5, 6)}),
/*66*/  lookup({std::make_pair(0, 1), std::make_pair(6, 7)}, {std::make_pair(1, 5), std::make_pair(2, 6)}, {std::make_pair(2, 4), std::make_pair(5, 6)}),

/*67*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*68*/  lookup({std::make_pair(3, 2), std::make_pair(6, 7)}, {}, {std::make_pair(1, 2), std::make_pair(5, 6)}),

/*69*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*70*/  lookup({std::make_pair(0, 1), std::make_pair(3, 2), std::make_pair(7, 6)}, {std::make_pair(1, 5)}, {std::make_pair(5, 6)}),

/*71*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*72*/  lookup({std::make_pair(2, 3), std::make_pair(6, 7)}, {std::make_pair(3, 7), std::make_pair(2, 6)}, {std::make_pair(0, 3), std::make_pair(5, 6)}),

/*73*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*74*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*75*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*76*/  lookup({std::make_pair(7, 6)}, {std::make_pair(3, 7)}, {std::make_pair(5, 6), std::make_pair(1, 2), std::make_pair(0, 3)}),

/*77*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*78*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*79*/  lookup({std::make_pair(7, 6)}, {std::make_pair(0, 4), std::make_pair(1, 5), std::make_pair(3, 7)}, {std::make_pair(5, 6)}),
/*80*/  lookup({std::make_pair(4, 5), std::make_pair(6, 7)}, {std::make_pair(0, 4), std::make_pair(2, 6)}, {std::make_pair(4, 7), std::make_pair(5, 6)}),

/*81*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*82*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*83*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*84*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*85*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*86*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*87*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*88*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*89*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*90*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*91*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*92*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*93*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*94*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*95*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*96*/  lookup({std::make_pair(4, 5), std::make_pair(6, 7)}, {std::make_pair(1, 5), std::make_pair(2, 6)}, {}),

/*97*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*98*/  lookup({std::make_pair(0, 1), std::make_pair(4, 5), std::make_pair(7, 6)}, {std::make_pair(2, 6)}, {std::make_pair(1, 2)}),

/*99*/  lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*100*/ lookup({std::make_pair(3, 2), std::make_pair(4, 5), std::make_pair(7, 6)}, {std::make_pair(1, 5)}, {std::make_pair(1, 2)}),

/*101*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*102*/ lookup({std::make_pair(0, 1), std::make_pair(3, 2), std::make_pair(4, 5), std::make_pair(7, 6)}, {}, {}),
/*103*/ lookup({std::make_pair(3, 2), std::make_pair(7, 6), std::make_pair(4, 5)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),

/*104*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*105*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*106*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*107*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*108*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*109*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*110*/ lookup({std::make_pair(0, 1), std::make_pair(7, 6), std::make_pair(4, 5)}, {std::make_pair(3, 7)}, {std::make_pair(0, 3)}),
/*111*/ lookup({std::make_pair(4, 5), std::make_pair(6, 7)}, {std::make_pair(0, 4), std::make_pair(3, 7)}, {}),
/*112*/ lookup({std::make_pair(7, 6)}, {std::make_pair(0, 4), std::make_pair(1, 5), std::make_pair(2, 6)}, {std::make_pair(4, 7)}),

/*113*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*114*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*115*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*116*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*117*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*118*/ lookup({std::make_pair(0, 1), std::make_pair(3, 2), std::make_pair(7, 6)}, {std::make_pair(0, 4)}, {std::make_pair(4, 7)}),
/*119*/ lookup({std::make_pair(6, 7), std::make_pair(3, 2)}, {}, {std::make_pair(0, 3), std::make_pair(4, 7)}),

/*120*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped
/*121*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),
/*122*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*123*/ lookup({std::make_pair(3, 2), std::make_pair(7, 6)}, {std::make_pair(2, 6), std::make_pair(3, 7)}, {std::make_pair(1, 2), std::make_pair(4, 7)}),

/*124*/ lookup({std::make_pair(0, 1)}, {std::make_pair(0, 4)}, {std::make_pair(0, 3)}),        // skipped

/*125*/ lookup({std::make_pair(0, 1), std::make_pair(6, 7)}, {std::make_pair(1, 5), std::make_pair(3, 7)}, {std::make_pair(1, 2), std::make_pair(4, 7)}),
/*126*/ lookup({std::make_pair(0, 1), std::make_pair(6, 7)}, {std::make_pair(0, 4), std::make_pair(3, 7)}, {std::make_pair(0, 3), std::make_pair(4, 7)}),
/*127*/ lookup({std::make_pair(6, 7)}, {std::make_pair(3, 7)}, {std::make_pair(4, 7)}),
};

};
//P = P_1 + (isovalue-V_1)(P_2-P_1)/(V_2 - V_1);


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