#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <fstream>

class Point
{
private:
    float x, y, z;

public:
    Point(float, float, float);
    Point();

    float getx();
    float gety();
    float getz();
    void setx(float);
    void sety(float);
    void setz(float);

    void negative();

    void serialize(std::ofstream *);
};

#endif // ponto