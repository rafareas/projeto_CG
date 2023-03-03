#include "../include/Cone.hpp"
#define _USE_MATH_DEFINES 
#include <cmath>
#include <math.h>

void Cone::generateTriangles(int size, int high, int slices, int stacks)
{
    float stackDistance = high * 1.0 / stacks;
    float stackSize =  size * 1.0 / stacks;
    float stackAngle = 2 * M_PI / slices;
    int i, j;
    float y1, y2, sliceRadius1, sliceRadius2, angle1, angle2;
    Point p1, p2, p3, p4;
    Triangle t;
    
    //the cone 
    for (i = 0; i < stacks; i++) {
        for (j = 0; j < slices; j++)
        {
            y1 = high - i * stackDistance;
            sliceRadius1 = size - (stacks - i) * stackSize;
            angle1 = j * stackAngle;

            i++;
            j++;
            y2 = high - i * stackDistance;
            sliceRadius2 = size - (stacks - i) * stackSize;
            angle2 = j * stackAngle;
            j--;
            i--;
            
            p1 = Point(sin(angle1) * sliceRadius1, y1, cos(angle1) * sliceRadius1);
            p2 = Point(sin(angle1) * sliceRadius2, y2, cos(angle1) * sliceRadius2);
            p3 = Point(sin(angle2) * sliceRadius2, y2, cos(angle2) * sliceRadius2);
            p4 = Point(sin(angle2) * sliceRadius1, y1, cos(angle2) * sliceRadius1);

            t = Triangle(p1, p2, p3);
            addTriangle(t);
            t = Triangle(p1, p3, p4);
            addTriangle(t);

            if (i == stacks - 1) {
                p1 = Point(0, 0, 0);
                t = Triangle(p2, p1, p3);
                addTriangle(t);

            }
        }
    }

    

}
