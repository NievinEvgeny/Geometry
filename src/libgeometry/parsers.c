#include "geometry.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void SkipSpace(char* str, int* i)
{
    while (isspace(str[*i]))
    {
        *i = *i + 1;
    }
}

int CorrectWritingCircle(char* str, int* i, Circle_S* ArrayOfCircles, int CurrentCircle)
{
    char Circle[] = {"circle"};
    int LengthOfCircle = strlen(Circle);

    SkipSpace(str, i);

    if (strncmp(&str[*i], Circle, LengthOfCircle) != 0)
    {
        return 1;
    }

    *i = *i + LengthOfCircle;

    SkipSpace(str, i);

    if (str[*i] != '(')
    {
        return -1;
    }

    *i = *i + 1;
    SkipSpace(str, i);

    char* LetterAfterFirstCoord = &str[*i];
    ArrayOfCircles[CurrentCircle].x = strtod(LetterAfterFirstCoord, &LetterAfterFirstCoord);

    if ((ArrayOfCircles[CurrentCircle].x == 0) && (LetterAfterFirstCoord == &str[*i]))
    {
        return -2;
    }

    if (*LetterAfterFirstCoord != ' ')
    {
        return -3;
    }

    *i = *i + LetterAfterFirstCoord - &str[*i];
    SkipSpace(str, i);

    char* LetterAfterSecondCoord = &str[*i];
    ArrayOfCircles[CurrentCircle].y = strtod(LetterAfterSecondCoord, &LetterAfterSecondCoord);

    if ((ArrayOfCircles[CurrentCircle].y == 0) && (LetterAfterSecondCoord == &str[*i]))
    {
        return -4;
    }

    *i = *i + LetterAfterSecondCoord - &str[*i];
    SkipSpace(str, i);

    if (str[*i] != ',')
    {
        return -5;
    }

    *i = *i + 1;
    SkipSpace(str, i);

    char* LetterAfterRadius = &str[*i];
    ArrayOfCircles[CurrentCircle].radius = strtod(LetterAfterRadius, &LetterAfterRadius);

    if ((ArrayOfCircles[CurrentCircle].radius == 0) && (LetterAfterRadius == &str[*i]))
    {
        return -6;
    }

    if (ArrayOfCircles[CurrentCircle].radius < 0)
    {
        return -7;
    }

    *i = *i + LetterAfterRadius - &str[*i];
    SkipSpace(str, i);

    if (str[*i] != ')')
    {
        return -8;
    }

    *i = *i + 1;

    SkipSpace(str, i);

    if (str + *i != str + strlen(str))
    {
        return -9;
    }

    *i = 0;
    return 0;
}

int CorrectWritingTriangle(char* str, int* i, Triangle_S* ArrayOfTriangles, int CurrentTriangle, int* CurrentCoord)
{
    int NumberOfCoordinatePairs = 4;
    char* LetterAfterCoord;
    char Triangle[] = {"triangle"};
    int LengthOfTriangle = strlen(Triangle);

    SkipSpace(str, i);

    if (strncmp(&str[*i], Triangle, LengthOfTriangle) != 0)
    {
        return 1;
    }

    *i = *i + LengthOfTriangle;

    SkipSpace(str, i);

    if (str[*i] != '(')
    {
        return -1;
    }

    *i = *i + 1;
    SkipSpace(str, i);

    while (*CurrentCoord < NumberOfCoordinatePairs)
    {
        LetterAfterCoord = &str[*i];
        ArrayOfTriangles[CurrentTriangle].x[*CurrentCoord] = strtod(LetterAfterCoord, &LetterAfterCoord);

        if ((ArrayOfTriangles[CurrentTriangle].x[*CurrentCoord] == 0) && (LetterAfterCoord == &str[*i]) && (*CurrentCoord == 0))
        {
            return -2;
        }

        if ((ArrayOfTriangles[CurrentTriangle].x[*CurrentCoord] == 0) && (LetterAfterCoord == &str[*i]) && (*CurrentCoord != 0))
        {
            return -3;
        }

        if (*LetterAfterCoord != ' ')
        {
            return -4;
        }

        *i = *i + LetterAfterCoord - &str[*i];
        SkipSpace(str, i);

        LetterAfterCoord = &str[*i];
        ArrayOfTriangles[CurrentTriangle].y[*CurrentCoord] = strtod(LetterAfterCoord, &LetterAfterCoord);

        if ((ArrayOfTriangles[CurrentTriangle].y[*CurrentCoord] == 0) && (LetterAfterCoord == &str[*i]))
        {
            return -5;
        }

        *i = *i + LetterAfterCoord - &str[*i];
        SkipSpace(str, i);

        if (*CurrentCoord < NumberOfCoordinatePairs - 1)
        {
            if (str[*i] != ',')
            {
                return -6;
            }
            *i = *i + 1;
        }
        *CurrentCoord = *CurrentCoord + 1;
    }

    if ((ArrayOfTriangles[CurrentTriangle].x[NumberOfCoordinatePairs - 4] != ArrayOfTriangles[CurrentTriangle].x[NumberOfCoordinatePairs - 1])
        || (ArrayOfTriangles[CurrentTriangle].y[NumberOfCoordinatePairs - 4] != ArrayOfTriangles[CurrentTriangle].y[NumberOfCoordinatePairs - 1]))
    {
        return -7;
    }

    if (str[*i] != ')')
    {
        return -8;
    }

    *i = *i + 1;

    SkipSpace(str, i);

    if (str + *i != str + strlen(str))
    {
        return -9;
    }

    *i = 0;
    return 0;
}