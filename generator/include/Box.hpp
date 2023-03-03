#ifndef BOX_HPP
#define BOX_HPP

#include "Shape.hpp"

class Box : public Shape
{
public:
    void generateTriangles(int, int);
};

#endif