#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Shape.hpp"

class Sphere : public Shape
{
public:
    void generateTriangles(int, int, int);
};

#endif