#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>

#include "include/Plane.hpp"
#include "include/Box.hpp"
#include "include/Sphere.hpp"
#include "include/Cone.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    
    // Create and open a text file
    ofstream MyFile( argv[argc-1] );
    char* shape = argv[1];

    //Criar triangulos para shape
    if(strcmp(shape,"plane") == 0) {
        if (argc < 5) {
            cout << "Numero de argumentos invalidos para " << shape;
            return 0;
        }
        Plane p;
        p.generateTriangles(stoi(argv[2]), stoi(argv[3]));
        p.serialize(&MyFile);
    }
    else if (strcmp(shape, "sphere") == 0 ) {
        if (argc != 6) {
            cout << "Numero de argumentos invalidos para " << shape;
            return 0;
        }
        Sphere p;
        p.generateTriangles(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
        p.serialize(&MyFile);
    }
    else if (strcmp(shape, "box") == 0) {
        if (argc != 5) {
            cout <<  "Numero de argumentos invalidos para " << shape;
            return 0;
        }
        Box p;
        p.generateTriangles(stoi(argv[2]), stoi(argv[3]));
        p.serialize(&MyFile);
    }
    else if (strcmp(shape, "cone") == 0) {
        if (argc != 7) {
            cout << "Numero de argumentos invalidos para " << shape;
            return 0;
        }
        Cone p;
        p.generateTriangles(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
        p.serialize(&MyFile);
    }

    // Close the file
    MyFile.close();
    return 1;
};