#include "geometry.h"
#include <math.h>

void CheckForCollisions(Circle_S* Circles, Triangle_S* Triangles, int NumCircles, int NumTriangles, short Collisions[][NumCircles + NumTriangles])
{
    int NumberOfFigures = NumCircles + NumTriangles;
    float SumOfRadiuses;
    float DistanceBetweenCenters;
    int i = 0, j = 0;
    int NumberOfVectors = 3, NumberOfSides = 3;
    float Vectors[NumberOfVectors];
    int CurrentLine = 1;
    float Coefficient, Dot_x, Dot_y, Perpendicular;
    float Ymax, Xmax, Ymin, Xmin;
    float Ax1, Ax2, Ay1, Ay2, Bx1, Bx2, By1, By2, v1, v2, v3, v4;

    for (i = 0; i < NumberOfFigures; i++)
    {
        for (j = 0; j < NumberOfFigures; j++)
        {
            if (i == j)
            {
                Collisions[i][j] = 0;
            }
        }
    }

    for (i = 0; i < NumberOfFigures - 1; i++)
    {
        for (j = CurrentLine; j < NumberOfFigures; j++)
        {
            // Two circles
            if ((i < NumCircles) && (j < NumCircles) && (i != j))
            {
                SumOfRadiuses = Circles[i].radius + Circles[j].radius;
                DistanceBetweenCenters = DistanceBetweenPoints((Circles[i].x - Circles[j].x), (Circles[i].y - Circles[j].y));
                if (SumOfRadiuses >= DistanceBetweenCenters)
                {
                    Collisions[i][j] = 1;
                }
                else
                {
                    Collisions[i][j] = 0;
                }
            }

            // Circle and triangle
            if (((i < NumCircles) && (j >= NumCircles)) && (i != j))
            {
                // Center of circle in triangle
                for (int k = 0; k < NumberOfVectors; k++)
                {
                    Vectors[k] = (Triangles[j].x[k] - Circles[i].x) * (Triangles[j].y[k + 1] - Triangles[j].y[k])
                            - (Triangles[j].y[k] - Circles[i].y) * (Triangles[j].x[k + 1] - Triangles[j].x[k]);
                    if (Vectors[k] < pow(10, -15))
                    {
                        Collisions[i][j] = 1;
                        break;
                    }
                }

                if ((Vectors[0] < 0) && (Vectors[1] < 0) && (Vectors[2] < 0))
                {
                    Collisions[i][j] = 1;
                }

                if ((Vectors[0] > 0) && (Vectors[1] > 0) && (Vectors[2] > 0))
                {
                    Collisions[i][j] = 1;
                }

                // Apex of a triangle in circle
                for (int k = 0; k < NumberOfSides; k++)
                {
                    if ((pow((Triangles[j].x[k] - Circles[i].x), 2) + pow((Triangles[j].y[k] - Circles[i].y), 2)) <= pow(Circles[i].radius, 2))
                    {
                        Collisions[i][j] = 1;
                        break;
                    }
                }

                // Perpendicular less than radius
                for (int k = 0; k < NumberOfSides; k++)
                {
                    Coefficient = ((Triangles[j].y[k + 1] - Triangles[j].y[k]) * (Circles[i].x - Triangles[j].x[k])
                                   - (Triangles[j].x[k + 1] - Triangles[j].x[k]) * (Circles[i].y - Triangles[j].y[k]))
                            / (pow((Circles[i].y - Triangles[j].x[k]), 2) + pow((Triangles[j].x[k + 1] - Triangles[j].x[k]), 2));

                    Dot_x = Circles[i].x - Coefficient * (Triangles[j].y[k + 1] - Triangles[j].y[k]);
                    Dot_y = Circles[i].y - Coefficient * (Triangles[j].y[k + 1] - Triangles[j].y[k]);

                    Perpendicular = DistanceBetweenPoints((Dot_x - Circles[i].x), (Dot_y - Circles[i].y));

                    if (Triangles[j].y[k + 1] > Triangles[j].y[k])
                    {
                        Ymax = Triangles[j].y[k + 1];
                        Ymin = Triangles[j].y[k];
                    }
                    else
                    {
                        Ymax = Triangles[j].y[k];
                        Ymin = Triangles[j].y[k + 1];
                    }

                    if (Triangles[j].x[k + 1] > Triangles[j].x[k])
                    {
                        Xmax = Triangles[j].x[k + 1];
                        Xmin = Triangles[j].x[k];
                    }
                    else
                    {
                        Xmax = Triangles[j].x[k];
                        Xmin = Triangles[j].x[k + 1];
                    }

                    if ((Perpendicular <= Circles[i].radius) && (Dot_x >= Xmin) && (Dot_x <= Xmax) && (Dot_y >= Ymin) && (Dot_y <= Ymax))
                    {
                        Collisions[i][j] = 1;
                        break;
                    }
                }

                // Did at least one check succeed
                if (Collisions[i][j] != 1)
                {
                    Collisions[i][j] = 0;
                }
            }

            // Two triangles
            if ((i >= NumCircles) && (j >= NumCircles) && (i != j))
            {
                for (int k = 0; k < NumberOfSides; k++)
                {
                    Ax1 = Triangles[i].x[k];
                    Ax2 = Triangles[i].x[k + 1];
                    Ay1 = Triangles[i].y[k];
                    Ay2 = Triangles[i].y[k + 1];
                    for (int l = 0; l < NumberOfSides; l++)
                    {
                        Bx1 = Triangles[j].x[l];
                        Bx2 = Triangles[j].x[l + 1];
                        By1 = Triangles[j].y[l];
                        By2 = Triangles[j].y[l + 1];
                        v1 = ((Bx2 - Bx1) * (Ay1 - By1) - (By2 - By1) * (Ax1 - Bx1));
                        v2 = ((Bx2 - Bx1) * (Ay2 - By1) - (By2 - By1) * (Ax2 - Bx1));
                        v3 = ((Ax2 - Ax1) * (By1 - Ay1) - (Ay2 - Ay1) * (Bx1 - Ax1));
                        v4 = ((Ax2 - Ax1) * (By2 - Ay1) - (Ay2 - Ay1) * (Bx2 - Ax1));
                        if ((v1 * v2 <= 0) && (v3 * v4 <= 0))
                        {
                            Collisions[i][j] = 1;
                            break;
                        }
                    }
                }

                if (Collisions[i][j] != 1)
                {
                    Collisions[i][j] = 0;
                }
            }
        }

        CurrentLine++;
    }

    for (int i = 0; i < NumberOfFigures; i++)
    {
        for (int j = 0; j < i; j++)
        {
            Collisions[i][j] = Collisions[j][i];
        }
    }
}