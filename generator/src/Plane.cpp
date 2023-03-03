#include "../include/Plane.hpp"

void Plane::generateTriangles(int length, int divisions)
{
    float divisionSize = (float)length / (float)divisions;
    float r = (float)length / 2.0;

    for (int i = 0; i < divisions; i++)
    {
        float xp = -r + i * divisionSize;
        for (int j = 0; j < divisions; j++)
        {
            float z = r - j * divisionSize;
            Point p1(xp, 0, z);
            Point p2(xp + divisionSize, 0, z);
            Point p3(xp + divisionSize, 0, z - divisionSize);

            // p1 e p3
            Point p4(xp, 0, z - divisionSize);

            Triangle t1(p1, p2, p3), t2(p1, p3, p4);
            addTriangle(t1);
            addTriangle(t2);
        }
    }
}
