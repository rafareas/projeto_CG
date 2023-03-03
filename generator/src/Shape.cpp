#include "../include/Shape.hpp"
#include <cmath>

void Shape::serialize(ofstream *figura)
{
    vector<Triangle>::iterator i;

    for (i = triangulos.begin(); i != triangulos.end(); i++)
    {
        i->serialize(figura);
    }
}

void Shape::addTriangle(Triangle triangulo)
{
    this->triangulos.push_back(triangulo);
}

void Shape::addTriangles(vector<Triangle> triangulos)
{
    this->triangulos = triangulos;
}

vector<Triangle> Shape::getTriangles()
{
    return this->triangulos;
}
