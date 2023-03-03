#include "../include/Point.hpp"

Point::Point(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

float Point::getx()
{
    return this->x;
}

float Point::gety()
{
    return this->y;
}

float Point::getz()
{
    return this->z;
}

void Point::setx(float xx)
{
    this->x = xx;
}

void Point::sety(float yy)
{
    this->y = yy;
}

void Point::setz(float zz)
{
    this->z = zz;
}

void Point::negative() {
    this->x = - (this->x);
    this->y = - (this->y);
    this->z = - (this->z);
}

void Point::serialize(std::ofstream *pontos)
{
    *pontos << x << " , " << y << " , " << z;
}