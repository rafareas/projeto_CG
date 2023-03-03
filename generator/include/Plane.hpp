#ifndef PLANE_HPP
#define PLANE_HPP

#include "Shape.hpp"

class Plane : public Shape
{
public:
    void generateTriangles(int, int);
};

#endif