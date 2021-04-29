#pragma once
#include <stdio.h>

typedef struct
{
    float x;
    float y;
    float radius;
    float perimeter;
    float area;
} Circle_S;

typedef struct
{
    float x[4];
    float y[4];
    float perimeter;
    float area;
} Triangle_S;

void CheckForCollisions(Circle_S* Circles, Triangle_S* Triangles, int NumCircles, int NumTriangles, short Collisions[][NumCircles + NumTriangles]);

void FindASides(Triangle_S Triangle, float* side);

double DistanceBetweenPoints(float a, float b);

float PerimeterOfACircle(Circle_S Circle);

float AreaOfACircle(Circle_S Circle);

float PerimeterOfATriangle(Triangle_S Triangle);

float AreaOfATriangle(Triangle_S Triangle);

int CorrectWritingCircle(char* str, int* i, Circle_S* ArrayOfCircles, int CurrentCircle);

int CorrectWritingTriangle(char* str, int* i, Triangle_S* ArrayOfTriangles, int CurrentTriangle, int* CurrentCoord);
