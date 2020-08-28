#include "application.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include "lutHelp.hpp"

void circle();
void Etable();
void Ttable();
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
        3593, 3331, 3082, 2822, 2575, 2309, 2060, 1804, 1541, 1295, 1030, 778, 515, 265, 0, };

/* 34 and 9 are reversed*/
int main(int argc, char* argv[]){

   
    buildTriangulationTable();
   // return 0;

   circle();
    //Etable(); 
    //Ttable();
  //  return 0;
    int width = 640;
    int height = 480;

    application app;
    app.init(argc, argv, width, height);
    if(argc == 2)
        app.load_grid(argv[1]);
    app.run();
}


void circle(){
    std::fstream file;
    const int width = 20;
    const int height = 20;
    const int depth = 20;

    file.open("circle.txt",std::fstream::out);
    file << "# Dimentions are for number of points NOT CUBES" <<
    "\n# width " << width <<
    "\n# height " << height<<
    "\n# depth " << depth << std::endl << std::endl;
    int shiftAmt = 10;
    for(int x = 0; x < 20; x++){
        for(int y = 0; y < 20; y++){
            for(int z = 0; z < 20; z++){
                file << x << " ";
                file << y << " ";
                file << z << " ";
                file << (x-shiftAmt)*(x-shiftAmt)+(y-shiftAmt)*(y-shiftAmt)+(z-shiftAmt)*(z-shiftAmt)-25;
                file << std::endl;
            }   
        }      
    }
    file.close();
}

void Etable(){
    std::fstream file;
    file.open("table.txt",std::fstream::out);
    for(int i = 0; i< 256; i++){
        int edges= 0;
        if((i&1)){//v0
            if((i&2)==0){edges += 1; } // if not v1 set e0
            if((i&8)==0){edges += 8;} // if not v3 set ee3
            if((i&16)==0){edges += 256;} // if not v4 set e8
        }
        if(i&2){//v1
            if((i&1)==0){edges += 1;} // if not v0 set e0
            if((i&4)==0){edges += 2;} // if  not v2 set e1
            if((i&32)==0){edges += 512;} // if not v5 set e9
        }
        if(i&4 ){//v2
            if((i&2)==0){edges += 2;} // if not v1 set e1
            if((i&8)==0){edges += 4;} // if not v3 set e2
            if((i&64)==0){edges += 1024;} // if not v6 set e10
        }
        if(i&8 ){//v3
            if((i&1)==0){edges += 8;} // if not v0 set e3
            if((i&4)==0){edges += 4;} // if not v2 set e2
            if((i&128)==0){edges += 2048;} // if not v7 set e11
        }
        if(i&16 ){//v4
            if((i&1)==0){edges += 256;} // if not v0 set e8
            if((i&32)==0){edges += 16;} // if not v5 set e4
            if((i&128)==0){edges += 128;} // if not v7 set e7
        }
        if(i&32){//v5
            if((i&2)==0){edges += 512;} // if not v1 set e9
            if((i&16)==0){edges += 16;} // if not v4 set e4
            if((i&64)==0){edges += 32;} // if not v6 set e5
        }
        if(i&64 ){//v6
            if((i&4)==0){edges += 1024;} // if not v2 set e10
            if((i&32)==0){edges += 32;} // if not v5 set e5
            if((i&128)==0){edges += 64;} // if not v7 set e6
        }
        if(i&128){//v7
            if((i&8)==0){edges += 2048;} // if not v3 set e11
            if((i&16)==0){edges += 128;} // if not v4 set e7
            if((i&64)==0){edges += 64;} // if not v6 set e6
        }
       file << edges << ", ";
       if(i>0 && i%16 == 0){file << std::endl;}
        //file << std::hex <<edges << " ";
    }
    file.close();
}



void Ttable(){
        std::fstream fileOUT;
    fileOUT.open("edgelist.txt");

        for(int i = 0; i < 256; i++){
            fileOUT << "/*" << i << "*/ "; 
            int count = 0;
            long pos = fileOUT.tellp();
        if((i>>0)&1){//v0
            if(((i>>1)&1)!=((i>>0)&1)){fileOUT << "0 "; count++; } // if not v1 set e0
            if(((i>>3)&1)!=((i>>0)&1)){fileOUT << "3 ";count++;} // if not v3 set e3
            if(((i>>4)&1)!=((i>>0)&1)){fileOUT << "8 ";count++;} // if not v4 set e8
        }
        if((i>>1)&1){//v1
            if(((i>>0)&1)!=((i>>1)&1)){fileOUT << "0 ";count++;} // if not v0 set e0
            if(((i>>2)&1)!=((i>>1)&1)){fileOUT << "1 ";count++;} // if  not v2 set e1
            if(((i>>5)&1)!=((i>>1)&1)){fileOUT << "9 ";count++;} // if not v5 set e9
        }
        if((i>>2)&1 ){//v2
            if(((i>>1)&1)!=((i>>2)&1)){fileOUT << "1 ";count++;} // if not v1 set e1
            if(((i>>3)&1)!=((i>>2)&1)){fileOUT << "2 ";count++;} // if not v3 set e2
            if(((i>>6)&1)!=((i>>2)&1)){fileOUT << "10 ";count++;} // if not v6 set e10
        }
        if((i>>3)&1 ){//v3
            if(((i>>0)&1)!=((i>>3)&1)){fileOUT << "3 ";count++;} // if not v0 set e3
            if(((i>>2)&1)!=((i>>3)&1)){fileOUT << "2 ";count++;} // if not v2 set e2
            if(((i>>7)&1)!=((i>>3)&1)){fileOUT << "0 ";count++;} // if not v7 set e11
        }
        if((i>>4)&1 ){//v4
            if(((i>>0)&1)!=((i>>4)&1)){fileOUT << "8 ";count++;} // if not v0 set e8
            if(((i>>5)&1)!=((i>>4)&1)){fileOUT << "4 ";count++;} // if not v5 set e4
            if(((i>>7)&1)!=((i>>4)&1)){fileOUT << "7 ";count++;} // if not v7 set e7
        }
        if((i>>5)&1){//v5
            if(((i>>1)&1)!=((i>>5)&1)){fileOUT << "9 ";count++;} // if not v1 set e9
            if(((i>>4)&1)!=((i>>5)&1)){fileOUT << "4 ";count++;} // if not v4 set e4
            if(((i>>6)&1)!=((i>>5)&1)){fileOUT << "5 ";count++;} // if not v6 set e5
        }
        if((i>>6)&1){//v6
            if(((i>>2)&1)!=((i>>6)&1)){fileOUT << "10 ";count++;} // if not v2 set e10
            if(((i>>5)&1)!=((i>>6)&1)){fileOUT << "5 ";count++;} // if not v5 set e5
            if(((i>>7)&1)!=((i>>6)&1)){fileOUT << "6 ";count++;} // if not v7 set e6
        }
        if((i>>7)&1){//v7
            if(((i>>3)&1)!=((i>>7)&1)){fileOUT << "11 ";count++;} // if not v3 set e11
            if(((i>>4)&1)!=((i>>7)&1)){fileOUT << "7 ";count++;} // if not v4 set e7
            if(((i>>6)&1)!=((i>>7)&1)){fileOUT << "6 ";count++;} // if not v6 set e6
        }

        /*
        long pos2 = fileOUT.tellp();
        if(count%3 != 0){
        for(int j = 0; j < (count%3)+1; j++){
            fileOUT.seekp(pos); // go to start of line
            std::string s;
            fileOUT >> s; //get edge number
            pos = fileOUT.tellp(); // since we moved up the stream get the positon
            fileOUT.seekp(pos2); // move to the end
            fileOUT << s <<" "; // put the edge number at the end
            pos2 = fileOUT.tellp(); // update the end position

        }
        }*/
        fileOUT << std::endl;
        }
fileOUT.close();

}

/*

 3 8 1 9 1 3

     5 6 
  12 4 3 7 
  11 1 2 8
    10 9   


    
    e5 e6  e7  e8
    e9 e10 e11 e12
    e1 e2  e3  e4


    e10 e11 e12
    e7  e8  e9
    e4  e5  e6
    e1  e2  e3

 case 1 00000001 
        000100001001

 case 2 00000010
        001000000011

 case 3 00000011
        001100001010

case 4 00000100
        01000000110

 case 5 00000101
        010100001111

*/
