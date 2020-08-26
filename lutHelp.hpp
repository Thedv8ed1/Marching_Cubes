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


class baseCase{
public:
baseCase(){}
   virtual void p(){
        std::cout << "index: " << index << std::endl;
        std::cout << "numOfTriangles: " << numOfTriangles << std::endl;
        for(int i = 0; i < numOfTriangles*3; i++){
            std::cout << stencil[i];
        }
        
    }
    uint8_t index;
    int numOfTriangles;
    int stencil[12];
};

class case1 :public baseCase{
public:
    case1(){
        index = 1;
        numOfTriangles = 1;
        int c1Stencil[3] ={0,3,8};
        std::copy(c1Stencil,c1Stencil+3,stencil);
    }
};

class case2 : public baseCase{
public:
    case2(){
        index = 3;
        numOfTriangles = 2;
        int c2Stencil[6] ={1,3,9,    3,8,9};
        std::copy(c2Stencil,c2Stencil+6,stencil);
    } 
};
class case3 : public baseCase{
public:
    case3(){
        index = 33;
        numOfTriangles = 2;
        int c3Stencil[6] ={0,3,8,    5,6,9};
        std::copy(c3Stencil,c3Stencil+6,stencil);
    } 
};
class case4 : public baseCase{
public:
    case4(){
        index = 65;
        numOfTriangles = 2;
        int c4Stencil[6] ={0,3,8,    5,6,10};
        std::copy(c4Stencil,c4Stencil+6,stencil);
    }
     
};
class case5 : public baseCase{
public:
    case5(){
        index = 14;
        numOfTriangles = 3;
        int c5Stencil[9] ={0,3,9,    3,9,11,    9,10,11};
        std::copy(c5Stencil,c5Stencil+9,stencil);
    }
};
class case6 : public baseCase{
public:
    case6(){
        index = 67;
        numOfTriangles = 3;
        int c6Stencil[9] ={1,3,9,    3,8,9,    5,6,10};
        std::copy(c6Stencil,c6Stencil+9,stencil);
    }
     
};
class case7 : public baseCase{
public:
    case7(){
        index = 82;
        numOfTriangles = 3;
        int c7Stencil[9] ={0,1,9,    4,7,8,    5,6,10};
        std::copy(c7Stencil,c7Stencil+9,stencil);
    }
     
};
class case8 : public baseCase{
public:
    case8(){
        index = 15;
        numOfTriangles = 2;
        int c8Stencil[6] ={8,9,10,    8,10,11};
        std::copy(c8Stencil,c8Stencil+6,stencil);
    }
     
};
class case9 : public baseCase{
public:
    case9(){
        index = 141;
        numOfTriangles = 4;
        int c9Stencil[12] ={0,1,10,    0,6,10,    0,6,8,    6,7,8};
        std::copy(c9Stencil,c9Stencil+12,stencil);
    }
     
};
class case10 : public baseCase{
public:
    case10(){
        index = 85;
        numOfTriangles = 4;
        int c10Stencil[12] ={0,3,4,    3,4,7,    1,2,5,    2,5,6};
        std::copy(c10Stencil,c10Stencil+12,stencil);
    }
     
};
class case11 : public baseCase{
public:
    case11(){
        index = 77;
        numOfTriangles = 4;
        int c11Stencil[12] ={0,1,5,    0,6,10,    0,6,8,    6,7,8};
        std::copy(c11Stencil,c11Stencil+12,stencil);
    }
     
};
class case12 : public baseCase{
public:
    case12(){
        index = 30;
        numOfTriangles = 4;
        int c12Stencil[12] ={0,3,9,    3,9,11,    4,7,8,    9,10,11}; 
        std::copy(c12Stencil,c12Stencil+12,stencil);
    }
};
class case13 : public baseCase{
public:
    case13(){
        index = 165;
        numOfTriangles = 4;
        int c13Stencil[12] ={0,3,8,    1,2,10,    4,5,9,    6,7,11};
        std::copy(c13Stencil,c13Stencil+12,stencil);
    }
     
};
class case14 : public baseCase{
public:
    case14(){
        index = 142;
        numOfTriangles = 4;
        int c14Stencil[12] ={0,3,7,    0,7,10,    0,9,10,    6,7,10};
        std::copy(c14Stencil,c14Stencil+12,stencil);
    }
};
/*
    A 12 element array symbolizes the cube
    Each group of 4 is a side. The group are arranged as:   bot  top  middle
    0,1,2,3  4,5,6,7  8,9,10,11

*/

/*
    TODO: make the method of edges match the method of verticies
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
*/
void rotateY(int arr[12], unsigned int *vertIndex){
    *vertIndex = ((*vertIndex>>1)&119) + // >> 7 6 5 3 2 1
    ((*vertIndex<<3)&136); // << 4 0

    int tmp[4];
    for(int i = 0; i < 12; i++){
        tmp[i] = arr[i];
    }
    arr[0] = tmp[1];
    arr[1] = tmp[2];
    arr[2] = tmp[3];
    arr[3] = tmp[0];
    arr[4] = tmp[5];
    arr[5] = tmp[6];
    arr[6] = tmp[7];
    arr[7] = tmp[4];
    arr[8] = tmp[9];
    arr[9] = tmp[10];
    arr[10] = tmp[11];
    arr[11] = tmp[8];
}

void rotateZ(int arr[12], unsigned int *vertIndex){
    *vertIndex = ((*vertIndex<<1)&130) +// << 6 0
     ((*vertIndex>>1)&20) + // >> 5 3
      ((*vertIndex>>4)&9) +  // >> 7 4
      ((*vertIndex<<4)&96) ;   // 2 1
    int tmp[12];
    for(int i = 0; i < 12; i++){
        tmp[i] = arr[i];
    }
    arr[0] = tmp[8];
    arr[1] = tmp[3];
    arr[2] = tmp[11];
    arr[3] = tmp[7];
    arr[4] = tmp[9];
    arr[5] = tmp[1];
    arr[6] = tmp[10];
    arr[7] = tmp[5];
    arr[8] = tmp[4];
    arr[9] = tmp[0];
    arr[10] = tmp[2];
    arr[11] = tmp[6];
}

void rotateX(int arr[12], unsigned int *vertIndex){
  *vertIndex = ((*vertIndex>>4)&3) + // >> 5 4
   ((*vertIndex<<4)&192) + // << 3 2
    ((*vertIndex>>3)&16)+ // >> 7
    ((*vertIndex>>1)&32)+ // >> 6
    ((*vertIndex<<3)&8) + // << 0
    ((*vertIndex<<1)&4); // << 1    
    int tmp[12];
    for(int i = 0; i < 12; i++){
        tmp[i] = arr[i];
    }
    arr[0] = tmp[4];
    arr[1] = tmp[9];
    arr[2] = tmp[0];
    arr[3] = tmp[8];
    arr[4] = tmp[6];
    arr[5] = tmp[10];
    arr[6] = tmp[2];
    arr[7] = tmp[11];
    arr[8] = tmp[7];
    arr[9] = tmp[5];
    arr[10] = tmp[1];
    arr[11] = tmp[3];

}

void mirrorY(int arr[12],unsigned int *vertIndex){
    *vertIndex = ((*vertIndex<<4)&240) + // << 3 2 1 0
     ((*vertIndex>>4)&15); // >> 7 6 5 4
    
    int tmp[12];
    for(int i = 0; i < 12; i++){
        tmp[i] = arr[i];
    }

    arr[0] = tmp[4];
    arr[1] = tmp[5];
    arr[2] = tmp[6];
    arr[3] = tmp[7];
    arr[4] = tmp[0];
    arr[5] = tmp[1];
    arr[6] = tmp[2];
    arr[7] = tmp[3];
    arr[8] = tmp[8];
    arr[9] = tmp[9];
    arr[10] = tmp[10];
    arr[11] = tmp[11];
}

void mirrorZ(int arr[12],unsigned int *vertIndex){
   * vertIndex = ((*vertIndex>>3)&17) + // >> 7 3
    ((*vertIndex>>1)&34) + // >> 6 2
    ((*vertIndex<<1)&68) + // << 5 1
    ((*vertIndex<<3)&136); // << 0 4

    int tmp[12];

    for(int i = 0; i < 12; i++){
        tmp[i] = arr[i];
    }

    arr[0] = tmp[2];
    arr[1] = tmp[1];
    arr[2] = tmp[0];
    arr[3] = tmp[3];
    arr[4] = tmp[6];
    arr[5] = tmp[5];
    arr[6] = tmp[4];
    arr[7] = tmp[7];
    arr[8] = tmp[11];
    arr[9] = tmp[10];
    arr[10] = tmp[9];
    arr[11] = tmp[8];
}

void mirrorX(int arr[12], unsigned int *vertIndex){
    *vertIndex = ((*vertIndex>>1)&85) + // >> 7 5 3 0
     ((*vertIndex<<1)&170); // << 6 4 2 0

    int tmp[12];
    for(int i = 0; i < 12; i++){
        tmp[i] = arr[i];
    }

    arr[0] = tmp[0];
    arr[1] = tmp[3];
    arr[2] = tmp[2];
    arr[3] = tmp[1];
    arr[4] = tmp[4];
    arr[5] = tmp[7];
    arr[6] = tmp[6];
    arr[7] = tmp[5];
    arr[8] = tmp[9];
    arr[9] = tmp[8];
    arr[10] = tmp[11];
    arr[11] = tmp[10];
}


void buildTriangulationTable(){
    std::vector<bool> processedTable;
    processedTable.resize(256,false);
    std::vector<std::vector<int> > table;
    for(int i = 0; i < 256; i++){table.push_back(std::vector<int>());}
    
    std::fstream file;
    file.open("Triangulation.txt",std::fstream::out);

    std::vector<baseCase *> cases;
    cases.push_back(new case1); cases.push_back(new case8); 
    cases.push_back(new case2); cases.push_back(new case9);
    cases.push_back(new case3); cases.push_back(new case10);
    cases.push_back(new case4); cases.push_back(new case11);
    cases.push_back(new case5); cases.push_back(new case12);
    cases.push_back(new case6); cases.push_back(new case13);
    cases.push_back(new case7); cases.push_back(new case14);
    for(int c = 0; c<cases.size(); c++){
        unsigned int index = cases[c]->index;
        int arr[12] = {0,1,2,3,4,5,6,7,8,9,10,11};

        for(int i = 0; i < 7; i++){ // for each mirror
            for(int x = 0; x < 4; x++){ // for each x rot
                for(int y = 0; y < 4; y++){ // for each y rot
                    for(int z = 0; z < 4; z++){ // for each z rot
                        if (processedTable[index] == false){           
                            for(int tri=0; tri < cases[c]->numOfTriangles; tri++){
                                table[index].push_back(arr[cases[c]->stencil[3*tri]]);
                                table[index].push_back(arr[cases[c]->stencil[(3*tri)+1]]);
                                table[index].push_back(arr[cases[c]->stencil[(3*tri)+2]]);
                            }
                            processedTable[index] = true;
                        }
                        // do complement rotations
                        uint8_t t = ~index;
                        if (processedTable[(int)t] == false){ 
                            for(int tri=0; tri < cases[c]->numOfTriangles; tri++){
                                table[(int)t].push_back(arr[cases[c]->stencil[3*tri]]);
                                table[(int)t].push_back(arr[cases[c]->stencil[(3*tri)+1]]);
                                table[(int)t].push_back(arr[cases[c]->stencil[(3*tri)+2]]);
                            }
                            processedTable[(int)t] = true;   
                        }
                        rotateZ(arr,&index);
                    }
                    rotateY(arr,&index);
                }
                rotateX(arr,&index);
            }
            index = cases[c]->index; resetCube(arr);
            if(i==0){mirrorX(arr,&index);}
            if(i==1){mirrorY(arr,&index);}
            if(i==2){mirrorZ(arr,&index);}
            if(i==3){mirrorX(arr,&index);mirrorY(arr,&index);}
            if(i==4){mirrorX(arr,&index);mirrorZ(arr,&index);}
            if(i==5){mirrorY(arr,&index);mirrorZ(arr,&index);}
            if(i==6){mirrorX(arr,&index);mirrorY(arr,&index);mirrorZ(arr,&index);}

        }
    }   
    file << "std::vector<std::vector<int> > triangleTable = {" << std::endl;
    for(int i = 0; i < table.size(); i++){
        file << "/*" << i << "/* {";
        for(int j = 0; j < table[i].size(); j++){
            file << table[i][j] << ", ";
        }
        if(i != 0 && i != 255){
            file.seekp(file.tellp()-2);
        }
        file << "},";
        file << std::endl;
    }
    file << "};";
    file.close();
}

