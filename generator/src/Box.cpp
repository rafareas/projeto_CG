#include "../include/Box.hpp"
#include "../include/Plane.hpp"

void Box::generateTriangles(int size, int divisions)
{
    float squareSize = (float)size / (float)divisions;
    float radius = (float)size / 2.0;

    float divisionSize, currentdivision;
    int i, j;
    Point p1, p2, p3, p4;
    Triangle t1, t2;

    // Create the bottom face of the box
    for (i = 0; i < divisions; i++){

        divisionSize = -radius + i * squareSize;
        for (j = 0; j < divisions; j++){
            currentdivision = radius - j * squareSize;
            p1 = Point(divisionSize, -radius, currentdivision);
            p2 = Point(divisionSize + squareSize, -radius, currentdivision);
            p3 = Point(divisionSize + squareSize, -radius, currentdivision - squareSize);

            // p1 e p3
            p4 = Point(divisionSize, -radius, currentdivision - squareSize);

            t1 = Triangle(p2, p1, p3);
            t2 = Triangle(p3, p1, p4);

            addTriangle(t1);
            addTriangle(t2);

            // Create the top face of the box
            p1 = Point(divisionSize, radius, currentdivision);
            p2 = Point(divisionSize + squareSize, radius, currentdivision);
            p3 = Point(divisionSize + squareSize, radius, currentdivision - squareSize);

            // p1 e p3
            p4 = Point(divisionSize, radius, currentdivision - squareSize);

            t1 = Triangle(p1, p2, p3);
            t2 = Triangle(p1, p3, p4);
            addTriangle(t1);
            addTriangle(t2);
        }
    }

    // Create the left face of the box
    for (i = 0; i < divisions; i++)
    {
        divisionSize = -radius + i * squareSize;
        for (j = 0; j < divisions; j++)
        {
            currentdivision = radius - j * squareSize;
            p1 = Point(divisionSize, currentdivision, -radius);
            p2 = Point(divisionSize + squareSize, currentdivision, -radius);
            p3 = Point(divisionSize + squareSize, currentdivision - squareSize, -radius);

            // p1 e p3
            p4 = Point(divisionSize, currentdivision - squareSize, -radius);

            t1 = Triangle(p1, p2, p3);
            t2 = Triangle(p1, p3, p4);
            addTriangle(t1);
            addTriangle(t2);

            // Create the right face of the box
            p1 = Point(divisionSize, currentdivision, radius);
            p2 = Point(divisionSize + squareSize, currentdivision, radius);
            p3 = Point(divisionSize + squareSize, currentdivision - squareSize, radius);

            // p1 e p3
            p4 = Point(divisionSize, currentdivision - squareSize, radius);

            t1 = Triangle(p2, p1, p3);
            t2 = Triangle(p3, p1, p4);
            addTriangle(t1);
            addTriangle(t2);
        }
    }

    // Create the front face of the box
    for (i = 0; i < divisions; i++)
    {
        divisionSize = -radius + i * squareSize;
        for (j = 0; j < divisions; j++)
        {
            currentdivision = radius - j * squareSize;
            p1 = Point(radius, currentdivision, divisionSize);
            p2 = Point(radius, currentdivision, divisionSize + squareSize);
            p3 = Point(radius, currentdivision - squareSize, divisionSize + squareSize);

            // p1 e p3
            p4 = Point(radius, currentdivision - squareSize, divisionSize);

            t1 = Triangle(p1, p2, p3);
            t2 = Triangle(p1, p3, p4);
            addTriangle(t1);
            addTriangle(t2);

            // Create the back face of the box
            p1 = Point(-radius, currentdivision, divisionSize);
            p2 = Point(-radius, currentdivision, divisionSize + squareSize);
            p3 = Point(-radius, currentdivision - squareSize, divisionSize + squareSize);

            // p1 e p3
            p4 = Point(-radius, currentdivision - squareSize, divisionSize);

            t1 = Triangle(p2, p1, p3);
            t2 = Triangle(p3, p1, p4);
            addTriangle(t1);
            addTriangle(t2);
        }
    }
}