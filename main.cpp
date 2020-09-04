#include "application.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include "lutHelp.hpp"


void circle();
void Etable();
void Ttable();

int main(int argc, char* argv[]){
   buildTriangulationTable();

   circle();
    //Etable(); 
    //Ttable();
  //  return 0;
    int width = 640;
    int height = 480;

    application app;
    app.init(argc, argv, width, height);
    if(argc == 2){
        app.load_grid(argv[1]);
    }
    else{
        buildTriangulationTable();
    }
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
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            for(int z = 0; z < depth; z++){
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