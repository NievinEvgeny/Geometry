#include "geometry.h"
#include <math.h>

double DistanceBetweenPoints(float a, float b)
{
    return sqrt((pow(a, 2) + pow(b, 2)));
}

float PerimeterOfACircle(Circle_S Circle)
{
    Circle.perimeter = 2 * M_PI * Circle.radius;
    return Circle.perimeter;
}

float AreaOfACircle(Circle_S Circle)
{
    float Radius = Circle.radius;
    Circle.area = M_PI * pow(Radius, 2);
    return Circle.area;
}

void FindASides(Triangle_S Triangle, float* side)
{
    int i;
    int NumberOfCoords = 3;
    float x[NumberOfCoords];
    float y[NumberOfCoords];
    for (i = 0; i < NumberOfCoords; i++)
    {
        x[i] = Triangle.x[i + 1] - Triangle.x[i];
        y[i] = Triangle.y[i + 1] - Triangle.y[i];
        side[i] = DistanceBetweenPoints(x[i], y[i]);
    }
}

float PerimeterOfATriangle(Triangle_S Triangle)
{
    int i;
    int NumberOfSides = 3;
    float side[NumberOfSides];
    Triangle.perimeter = 0;
    FindASides(Triangle, side);
    for (i = 0; i < NumberOfSides; i++)
    {
        Triangle.perimeter += side[i];
    }
    return Triangle.perimeter;
}

float AreaOfATriangle(Triangle_S Triangle)
{
    int NumberOfSides = 3;
    float side[NumberOfSides];
    float p;
    FindASides(Triangle, side);
    p = (side[0] + side[1] + side[2]) / 2;
    Triangle.area = sqrt((p * (p - side[0]) * (p - side[1]) * (p - side[2])));
    return Triangle.area;
}