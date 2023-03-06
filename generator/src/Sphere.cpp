#include "../include/Sphere.hpp"
#define _USE_MATH_DEFINES 
#include <cmath>
#include <math.h>

void Sphere::generateTriangles(int size, int stacks, int slices)
{
    float radius = size / 2.0;
    float slicedistance = size * 1.0 / stacks;
    float stacksize = M_PI / stacks;
    float stackAngle = 2 * M_PI / slices;
    int i, j;
    float y1, y2, sliceRadius1, sliceRadius2, angle;
    Point p1, p2, p3, p4;
    Triangle t;

    // top and bottom triangles of the sphere
    y2 = radius - slicedistance;
    sliceRadius2 = sqrt(pow(radius, 2) - pow(y2, 2));
   
    for (j = 0; j < slices; j++){
        p1 = Point(0, radius, 0);
        angle = j * stackAngle;
        p2 = Point(sin(angle) * sliceRadius2, y2, cos(angle) * sliceRadius2);

        j++;
        angle = j * stackAngle;
        p3 = Point(sin(angle) * sliceRadius2, y2, cos(angle) * sliceRadius2);

        j--;

        t = Triangle(p1, p2, p3);
        addTriangle(t);
        p1.sety(-radius);
        p2.sety(-radius + slicedistance);
        p3.sety(-radius + slicedistance);
        t = Triangle(p2, p1, p3);
        addTriangle(t);
    }
    //side of the sphere
    for (i = 1; i < stacks-1; i++) {
        y1 = radius - i * slicedistance;
        sliceRadius1 = sqrt(pow(radius, 2) - pow(y1, 2));
        i++;
        y2 = radius - i * slicedistance;
        i--;
        sliceRadius2 = sqrt(pow(radius, 2) - pow(y2, 2));
        
        for (j = 0; j < slices; j++)
        {
            angle = j * stackAngle;
            p1 = Point(sin(angle) * sliceRadius1, y1, cos(angle) * sliceRadius1);

            p2 = Point(sin(angle) * sliceRadius2, y2, cos(angle) * sliceRadius2);

            j++;
            angle = j * stackAngle;
            p3 = Point(sin(angle) * sliceRadius2, y2, cos(angle) * sliceRadius2);

            p4 = Point(sin(angle) * sliceRadius1, y1, cos(angle) * sliceRadius1);
            
            j--;

            t = Triangle(p1, p2, p3);
            addTriangle(t);
            t = Triangle(p1, p3, p4);
            addTriangle(t);
        }
    }
}
