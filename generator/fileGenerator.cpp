#include <stdio.h>
#include <iostream>
#include <fstream>

#include "include/Plane.hpp"
#include "include/Box.hpp"
#include "include/Sphere.hpp"
#include "include/Cone.hpp"

using namespace std;

int main(){
    // Create and open a text file
    ofstream MyFile("shape.txt");

    // Write to the file
    Cone p;
    p.generateTriangles(1, 2, 4, 3);
    p.serialize(&MyFile);

    // Close the file
    MyFile.close();
};