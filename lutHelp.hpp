#pragma once

#include <fstream>
#include <vector>
#include <iostream>

/*
    Y
    ^    Z
    |   /
    |  /
    | /
    O------->X


   5--------6
  / |      /|
 /  |     / |
4--------7  |
|   |    |  |
|   3----|--2
|  /     | /
| /      |/
0--------1


   x---6----x
  7 |      5|
 /  |     / |
x------4-x  |
|   11   |  10
|   x--2-|--x
8  3     9 1
| /      |/
x----0---x
*/

/*

 cases are built by moving in a counter-clockwise direction taking the first
 vertex encounterd and adding the other verticies of that triangle in order

*/

/*
    TRIANGLE PATTERN EXAMPLES
        1     1         1
CASE 1: 0 1 2 3 4 5 6 7 8 9 10 11

              2         2 2
          1   1           1
CASE 2: 0 1 2 3 4 5 6 7 8 9 10 11

                2 2       2
        1     1         1
CASE 2: 0 1 2 3 4 5 6 7 8 9 10 11
*/

void outputTriTable(std::vector< std::vector<int> > table);

class BaseCase{
public:
    BaseCase(){}
    virtual uint8_t get_index(){return 0;};
    virtual std::vector<int> get_triangles() {
        std::vector<int> triangles;
        for(int tri = 0; tri < numOfTriangles; tri++){
            triangles.push_back(edges[stencil[tri*3]]);
            triangles.push_back(edges[stencil[1+(tri*3)]]);
            triangles.push_back(edges[stencil[2+(tri*3)]]);
        }
        return triangles;
    };
    void rotateX(){rotateX(verts,edges);}
    void rotateY(){rotateY(verts,edges);}
    void rotateZ(){rotateZ(verts,edges);}

    void mirrorX(){mirrorX(verts,edges);}
    void mirrorY(){mirrorY(verts,edges);}
    void mirrorZ(){mirrorZ(verts,edges);}


    int numOfTriangles;
    int stencil[12];

    protected:
    void rotateX(int verts[8],int edges[12]);
    void rotateY(int verts[8],int edges[12]);
    void rotateZ(int verts[8],int edges[12]);

    void mirrorX(int verts[8],int edges[12]);
    void mirrorY(int verts[8],int edges[12]);
    void mirrorZ(int verts[8],int edges[12]);

    int verts[8] = {0,1,2,3,4,5,6,7};
    int edges[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
};

class case1 :public BaseCase{
public:
    case1(){
        numOfTriangles = 1;
        int c1Stencil[3] ={0,3,8};
        std::copy(c1Stencil,c1Stencil+3,stencil);
    }
    virtual uint8_t get_index() override {return (1<<verts[0]);}
};
class case2 : public BaseCase{
public:
    case2(){
        numOfTriangles = 2;
        int c2Stencil[6] ={1,3,9,    3,8,9};
        std::copy(c2Stencil,c2Stencil+6,stencil);
    } 
    virtual uint8_t get_index()override{return ((1<<verts[0]) + (1<<verts[1]));}
};
class case3 : public BaseCase{
public:
    case3(){
        numOfTriangles = 2;
        int c3Stencil[6] ={0,3,8,    4,5,9};
        std::copy(c3Stencil,c3Stencil+6,stencil);
    } 
    virtual uint8_t get_index()override{return ((1<<verts[0]) + (1<<verts[5]));}

};
class case4 : public BaseCase{
public:
    case4(){
        numOfTriangles = 2;
        int c4Stencil[6] ={0,3,8,    5,6,10};
        std::copy(c4Stencil,c4Stencil+6,stencil);
    }
    virtual uint8_t get_index()override{return ((1<<verts[0]) + (1<<verts[6]));}
};
class case5 : public BaseCase{
public:
    case5(){
        numOfTriangles = 3;
        int c5Stencil[9] ={0,3,9,    3,9,11,    9,10,11};
        std::copy(c5Stencil,c5Stencil+9,stencil);
    }
    virtual uint8_t get_index()override{return ((1<<verts[1]) + (1<<verts[2]) + (1<<verts[3]));}
};
class case6 : public BaseCase{
public:
    case6(){
        numOfTriangles = 3;
        int c6Stencil[9] ={1,3,9,    3,8,9,    5,6,10};
        std::copy(c6Stencil,c6Stencil+9,stencil);
    }
    virtual uint8_t get_index()override{return ((1<<verts[0]) + (1<<verts[1]) + (1<<verts[6]));}
};
class case7 : public BaseCase{
public:
    case7(){
        numOfTriangles = 3;
        int c7Stencil[9] ={0,1,9,    4,7,8,    5,6,10};
        std::copy(c7Stencil,c7Stencil+9,stencil);
    }
    virtual uint8_t get_index()override{return ((1<<verts[1]) + (1<<verts[4]) + (1<<verts[6]));}
};
class case8 : public BaseCase{
public:
    case8(){
        numOfTriangles = 2;
        int c8Stencil[6] ={8,9,10,    8,10,11};
        std::copy(c8Stencil,c8Stencil+6,stencil);
    }
    virtual uint8_t get_index()override{return ((1<<verts[0]) + (1<<verts[1]) + (1<<verts[2]) + (1<<verts[3]));} 
};
class case9 : public BaseCase{
public:
    case9(){
        numOfTriangles = 4;
        int c9Stencil[12] ={0,1,10,    0,6,10,    0,6,8,    6,7,8};
        std::copy(c9Stencil,c9Stencil+12,stencil);
    }
    virtual uint8_t get_index()override{return ((1<<verts[0]) + (1<<verts[2]) + (1<<verts[3]) + (1<<verts[7]));}
};
class case10 : public BaseCase{
public:
    case10(){
        numOfTriangles = 4;
        int c10Stencil[12] ={0,3,4,    3,4,7,    1,2,5,    2,5,6};
        std::copy(c10Stencil,c10Stencil+12,stencil);
    }
    virtual uint8_t get_index()override{return ((1<<verts[0]) + (1<<verts[2]) + (1<<verts[4]) + (1<<verts[6]));}    
};
class case11 : public BaseCase{
public:
    case11(){
        numOfTriangles = 4;
        int c11Stencil[12] ={0,1,5,    0,5,11,    0,8,11,    6,5,11};
        std::copy(c11Stencil,c11Stencil+12,stencil);
    }
    virtual uint8_t get_index()override{return ((1<<verts[0]) + (1<<verts[2]) + (1<<verts[3]) + (1<<verts[6]));}   
};
class case12 : public BaseCase{
public:
    case12(){
        numOfTriangles = 4;
        int c12Stencil[12] ={0,3,9,    3,9,11,    4,7,8,    9,10,11}; 
        std::copy(c12Stencil,c12Stencil+12,stencil);
    }
    virtual uint8_t get_index()override{return ((1<<verts[1]) + (1<<verts[2]) + (1<<verts[3]) + (1<<verts[4]));}
};
class case13 : public BaseCase{
public:
    case13(){
        numOfTriangles = 4;
        int c13Stencil[12] ={0,3,8,    1,2,10,    4,5,9,    6,7,11};
        std::copy(c13Stencil,c13Stencil+12,stencil);
    }
    virtual uint8_t get_index()override{return ((1<<verts[0]) + (1<<verts[2]) + (1<<verts[5]) + (1<<verts[7]));}
};
class case14 : public BaseCase{
public:
    case14(){
        numOfTriangles = 4;
        int c14Stencil[12] ={0,3,7,    0,7,10,    0,9,10,    6,7,10};
        std::copy(c14Stencil,c14Stencil+12,stencil);
    }
    virtual uint8_t get_index()override{return ((1<<verts[1]) + (1<<verts[2]) + (1<<verts[3]) + (1<<verts[7]));}
};
/*
    A 12 element array symbolizes the cube
    Each group of 4 is a side. The default is arranged as:   bot  top  middle
    0,1,2,3  4,5,6,7  8,9,10,11

*/

void resetCube(int arr[12]){
    for(int i = 0; i < 12; i++){
        arr[i] = i;
    }
}

/*
    There is probably a way to do all these with a loop
    TODO: figure it out

*/

/*
    ALL rotations rotate the cube counter-clockwise
    horizontal shifts clockwise
    vertical shifts counter-clockwise

*/
void BaseCase::rotateX(int verts[8], int edges[12]){ 
    int tmpVerts[8];
    for(int i = 0; i < 8; i++){
        tmpVerts[i] = verts[i];

    }
    verts[0] = tmpVerts[4];
    verts[1] = tmpVerts[5];
    verts[2] = tmpVerts[1];
    verts[3] = tmpVerts[0];
    verts[4] = tmpVerts[7];
    verts[5] = tmpVerts[6];
    verts[6] = tmpVerts[2];
    verts[7] = tmpVerts[3];

    int tmpEdges[12];
    for(int i = 0; i < 12; i++){
        tmpEdges[i] = edges[i];
    }
    // vertical
    edges[0] = tmpEdges[4];
    edges[1] = tmpEdges[9];
    edges[2] = tmpEdges[0];
    edges[3] = tmpEdges[8];
    edges[4] = tmpEdges[6];
    edges[5] = tmpEdges[10];
    edges[6] = tmpEdges[2];
    edges[7] = tmpEdges[11];
    edges[8] = tmpEdges[7];
    edges[9] = tmpEdges[5];
    edges[10] = tmpEdges[1];
    edges[11] = tmpEdges[3];    
}

void BaseCase::rotateY(int verts[8], int edges[12]){    
    int tmpVerts[8];
    for(int i = 0; i < 8; i++){
        tmpVerts[i] = verts[i];

    }
    verts[0] = tmpVerts[3];
    verts[1] = tmpVerts[0];
    verts[2] = tmpVerts[1];
    verts[3] = tmpVerts[2];
    verts[4] = tmpVerts[7];
    verts[5] = tmpVerts[4];
    verts[6] = tmpVerts[5];
    verts[7] = tmpVerts[6];

    int tmpEdges[12];
    for(int i = 0; i < 12; i++){
        tmpEdges[i] = edges[i];
    }
    edges[0] = tmpEdges[3];
    edges[1] = tmpEdges[0];
    edges[2] = tmpEdges[1];
    edges[3] = tmpEdges[2];
    edges[4] = tmpEdges[7];
    edges[5] = tmpEdges[4];
    edges[6] = tmpEdges[5];
    edges[7] = tmpEdges[6];
    edges[8] = tmpEdges[11];
    edges[9] = tmpEdges[8];
    edges[10] = tmpEdges[9];
    edges[11] = tmpEdges[10];    
}

void BaseCase::rotateZ(int verts[8], int edges[12]){ 
    int tmpVerts[8];
    for(int i = 0; i < 8; i++){
        tmpVerts[i] = verts[i];

    }
    verts[0] = tmpVerts[4];
    verts[1] = tmpVerts[0];
    verts[2] = tmpVerts[3];
    verts[3] = tmpVerts[7];
    verts[4] = tmpVerts[5];
    verts[5] = tmpVerts[1];
    verts[6] = tmpVerts[2];
    verts[7] = tmpVerts[6];    
    
    int tmpEdges[12];
    for(int i = 0; i < 12; i++){
        tmpEdges[i] = edges[i];
    }
    edges[0] = tmpEdges[8];
    edges[1] = tmpEdges[3];
    edges[2] = tmpEdges[11];
    edges[3] = tmpEdges[7];
    edges[4] = tmpEdges[9];
    edges[5] = tmpEdges[1];
    edges[6] = tmpEdges[10];
    edges[7] = tmpEdges[5];
    edges[8] = tmpEdges[4];
    edges[9] = tmpEdges[0];
    edges[10] = tmpEdges[2];
    edges[11] = tmpEdges[6];
}

void BaseCase::mirrorX(int verts[8], int edges[12]){
    int tmpVerts[8];
    for(int i = 0; i < 8; i++){
        tmpVerts[i] = verts[i];
    }
    verts[0] = tmpVerts[1];
    verts[1] = tmpVerts[0];
    verts[2] = tmpVerts[3];
    verts[3] = tmpVerts[2];
    verts[4] = tmpVerts[5];
    verts[5] = tmpVerts[4];
    verts[6] = tmpVerts[7];
    verts[7] = tmpVerts[6]; 

    int tmpEdges[12];
    for(int i = 0; i < 12; i++){
        tmpEdges[i] = edges[i];
    }
    edges[0] = tmpEdges[0];
    edges[1] = tmpEdges[3];
    edges[2] = tmpEdges[2];
    edges[3] = tmpEdges[1];
    edges[4] = tmpEdges[4];
    edges[5] = tmpEdges[7];
    edges[6] = tmpEdges[6];
    edges[7] = tmpEdges[5];
    edges[8] = tmpEdges[9];
    edges[9] = tmpEdges[8];
    edges[10] = tmpEdges[11];
    edges[11] = tmpEdges[10];
}

void BaseCase::mirrorY(int verts[8], int edges[12]){
    int tmpVerts[8];
    for(int i = 0; i < 8; i++){
        tmpVerts[i] = verts[i];
    }
    verts[0] = tmpVerts[4];
    verts[1] = tmpVerts[5];
    verts[2] = tmpVerts[6];
    verts[3] = tmpVerts[7];
    verts[4] = tmpVerts[0];
    verts[5] = tmpVerts[1];
    verts[6] = tmpVerts[2];
    verts[7] = tmpVerts[3]; 

    int tmpEdges[12];
    for(int i = 0; i < 12; i++){
        tmpEdges[i] = edges[i];
    }
    edges[0] = tmpEdges[4];
    edges[1] = tmpEdges[5];
    edges[2] = tmpEdges[6];
    edges[3] = tmpEdges[7];
    edges[4] = tmpEdges[0];
    edges[5] = tmpEdges[1];
    edges[6] = tmpEdges[2];
    edges[7] = tmpEdges[3];
    edges[8] = tmpEdges[8];
    edges[9] = tmpEdges[6];
    edges[10] = tmpEdges[10];
    edges[11] = tmpEdges[11];
}

void BaseCase::mirrorZ(int verts[8], int edges[12]){
    int tmpVerts[8];
    for(int i = 0; i < 8; i++){
        tmpVerts[i] = verts[i];
    }
    verts[0] = tmpVerts[3];
    verts[1] = tmpVerts[2];
    verts[2] = tmpVerts[1];
    verts[3] = tmpVerts[0];
    verts[4] = tmpVerts[7];
    verts[5] = tmpVerts[6];
    verts[6] = tmpVerts[5];
    verts[7] = tmpVerts[4]; 

    int tmpEdges[12];
    for(int i = 0; i < 12; i++){
        tmpEdges[i] = edges[i];
    }
    edges[0] = tmpEdges[2];
    edges[1] = tmpEdges[3];
    edges[2] = tmpEdges[0];
    edges[3] = tmpEdges[1];
    edges[4] = tmpEdges[6];
    edges[5] = tmpEdges[7];
    edges[6] = tmpEdges[4];
    edges[7] = tmpEdges[5];
    edges[8] = tmpEdges[10];
    edges[9] = tmpEdges[11];
    edges[10] = tmpEdges[8];
    edges[11] = tmpEdges[9];
}

void buildTriangulationTable(){
    std::vector<bool> processedTable;
    processedTable.resize(256,false);
    std::vector<std::vector<int> > table;
    for(int i = 0; i < 256; i++){table.push_back(std::vector<int>());}
    
    std::vector<BaseCase *> cases;
    cases.push_back(new case1);  
    cases.push_back(new case2);
    cases.push_back(new case3);
    cases.push_back(new case4); 
    cases.push_back(new case5); 
    cases.push_back(new case6); 
    cases.push_back(new case7); 
    cases.push_back(new case8);
    cases.push_back(new case9);
    cases.push_back(new case10);
    cases.push_back(new case11);
    cases.push_back(new case12);
    cases.push_back(new case13);
    cases.push_back(new case14);

    for(uint8_t c = 0; c<cases.size(); c++){ // for every case
        for(unsigned int x = 0; x < 4; x++){ // for each x rot
            for(unsigned int y = 0; y < 4; y++){ // for each y rot
                for(unsigned int z = 0; z < 4; z++){ // for each z rot
                    if(processedTable[cases[c]->get_index()] == false){
                        //std::cout << x << " " << y << " " << z << "----" << std::endl;
                        uint8_t compIndex = ~(cases[c]->get_index());
                        //std::cout  << " " << +cases[c]->get_index() << std::endl;
                        std::vector<int> triangles = cases[c]->get_triangles();
                        for(unsigned int i = 0; i < triangles.size(); i++){
                        //    std::cout << triangles[i] << " ";
                            table[cases[c]->get_index()].push_back(triangles[i]);
                            // do the complement case
                            table[compIndex].push_back(triangles[i]);                            
                        }
                        processedTable[cases[c]->get_index()] = true;
                        processedTable[compIndex] = true;
                    } 
                    cases[c]->rotateZ();
               }  
               cases[c]->rotateY();
            }   
            cases[c]->rotateX();   
        }
    }

    outputTriTable(table);
    
}

void outputTriTable(std::vector< std::vector<int> > table){

    std::fstream file;
    file.open("Triangulation.txt",std::fstream::out);

    file << "std::vector<std::vector<int> > triangleTable = {" << std::endl;
    for(unsigned int i = 0; i < table.size(); i++){
        file << "/*" << i << "*/ {";
        for(unsigned int j = 0; j < table[i].size(); j++){
            file << table[i][j] << ", ";
        }
        
        file << "},";
        file << std::endl;
    }
    file << "};";
    file.close();
}

