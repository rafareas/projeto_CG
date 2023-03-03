#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Triangle.hpp"

#include <iostream>
#include <fstream>

#include <vector>

using namespace std;

class Shape
{

private:
    vector<Triangle> triangulos;

public:
    void serialize(ofstream *);
    void addTriangle(Triangle);
    void addTriangles(vector<Triangle>);
    vector<Triangle> getTriangles();
};

#endif