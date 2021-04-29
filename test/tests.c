#include <ctest.h>
#include <libgeometry/geometry.h>
#include <stdlib.h>

CTEST(P_and_A_of_triangles, Sides)
{
    float real[3];
    Triangle_S Triangle;
    Triangle.x[0] = 1;
    Triangle.x[1] = 5;
    Triangle.x[2] = -3;
    Triangle.x[3] = 1;
    Triangle.y[0] = 4;
    Triangle.y[1] = -3;
    Triangle.y[2] = 2;
    Triangle.y[3] = 4;

    FindASides(Triangle, real);

    float expside[3];
    expside[0] = 8.06225;
    expside[1] = 9.43398;
    expside[2] = 4.47213;

    ASSERT_DBL_NEAR(expside[0], real[0]);
    ASSERT_DBL_NEAR(expside[1], real[1]);
    ASSERT_DBL_NEAR(expside[2], real[2]);
}

CTEST(P_and_A_of_triangles, Perimeter)
{
    Triangle_S Triangle;
    Triangle.x[0] = 1;
    Triangle.x[1] = 5;
    Triangle.x[2] = -3;
    Triangle.x[3] = 1;
    Triangle.y[0] = 4;
    Triangle.y[1] = -3;
    Triangle.y[2] = 2;
    Triangle.y[3] = 4;

    float real = PerimeterOfATriangle(Triangle);

    float expP = 21.96836;

    ASSERT_DBL_NEAR(expP, real);
}

CTEST(P_and_A_of_triangles, Area)
{
    Triangle_S Triangle;
    Triangle.x[0] = 1;
    Triangle.x[1] = 5;
    Triangle.x[2] = -3;
    Triangle.x[3] = 1;
    Triangle.y[0] = 4;
    Triangle.y[1] = -3;
    Triangle.y[2] = 2;
    Triangle.y[3] = 4;

    float real = AreaOfATriangle(Triangle);

    float expA = 18;

    ASSERT_DBL_NEAR(expA, real);
}

CTEST(P_and_A_of_circles, Perimeter)
{
    Circle_S Circle;
    Circle.radius = 2;

    float real = PerimeterOfACircle(Circle);

    float expP = 12.56636;

    ASSERT_DBL_NEAR(expP, real);
}

CTEST(P_and_A_of_circles, Area)
{
    Circle_S Circle;
    Circle.radius = 2;

    float real = AreaOfACircle(Circle);

    float expP = 12.56636;

    ASSERT_DBL_NEAR(expP, real);
}

CTEST(ParseOfCircle, NoErrors)
{
    char str[50] = {"  circle ( 1   2 ,  6  )"};
    int i = 0;
    Circle_S circles[1];
    int current_circle = 0;

    int real = CorrectWritingCircle(str, &i, circles, current_circle);

    int exp = 0;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfCircle, ErrorInCircleName)
{
    char str[50] = {"  cirle ( 1   2 ,  6  )"};
    int i = 0;
    Circle_S circles[1];
    int current_circle = 0;

    int real = CorrectWritingCircle(str, &i, circles, current_circle);

    int exp = 1;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfCircle, NotABracketAfterName)
{
    char str[50] = {"  circle a( 1   2 ,  6  )"};
    int i = 0;
    Circle_S circles[1];
    int current_circle = 0;

    int real = CorrectWritingCircle(str, &i, circles, current_circle);

    int exp = -1;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfCircle, NotACoordAfterBracket)
{
    char str[50] = {"  circle  (  a1   2 ,  6  )"};
    int i = 0;
    Circle_S circles[1];
    int current_circle = 0;

    int real = CorrectWritingCircle(str, &i, circles, current_circle);

    int exp = -2;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfCircle, NotASpaceAfterFirstCoord)
{
    char str[50] = {"  circle  (  1a  2 ,  6  )"};
    int i = 0;
    Circle_S circles[1];
    int current_circle = 0;

    int real = CorrectWritingCircle(str, &i, circles, current_circle);

    int exp = -3;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfCircle, NotASecondCoordAfterFirstCoord)
{
    char str[50] = {"  circle  (  1 a  2 ,  6  )"};
    int i = 0;
    Circle_S circles[1];
    int current_circle = 0;

    int real = CorrectWritingCircle(str, &i, circles, current_circle);

    int exp = -4;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfCircle, NotACommaAfterSecondCoord)
{
    char str[50] = {"  circle  (  1   2a ,  6  )"};
    int i = 0;
    Circle_S circles[1];
    int current_circle = 0;

    int real = CorrectWritingCircle(str, &i, circles, current_circle);

    int exp = -5;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfCircle, NotARadiusAfterComma)
{
    char str[50] = {"  circle  (  1   2 ,  a 6  )"};
    int i = 0;
    Circle_S circles[1];
    int current_circle = 0;

    int real = CorrectWritingCircle(str, &i, circles, current_circle);

    int exp = -6;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfCircle, NotABracketAfterRadius)
{
    char str[50] = {"  circle  (  1   2 ,   6  a)"};
    int i = 0;
    Circle_S circles[1];
    int current_circle = 0;

    int real = CorrectWritingCircle(str, &i, circles, current_circle);

    int exp = -8;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfCircle, NotEndAfterBracket)
{
    char str[50] = {"  circle  (  1   2 ,   6  )  a"};
    int i = 0;
    Circle_S circles[1];
    int current_circle = 0;

    int real = CorrectWritingCircle(str, &i, circles, current_circle);

    int exp = -9;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfCircle, RadiusIsLowerThanZero)
{
    char str[50] = {"  circle  (  1   2 ,   -6  )"};
    int i = 0;
    Circle_S circles[1];
    int current_circle = 0;

    int real = CorrectWritingCircle(str, &i, circles, current_circle);

    int exp = -7;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfTriangle, NoErrors)
{
    char str[50] = {"  triangle  ( 1 5  ,  -3  5  ,   15 7 ,  1  5 ) "};
    int i = 0;
    Triangle_S triangles[1];
    int current_triangle = 0;
    int current_coord = 0;

    int real = CorrectWritingTriangle(str, &i, triangles, current_triangle, &current_coord);

    int exp = 0;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfTriangle, ErrorInTriangleName)
{
    char str[50] = {"  triagle  ( 1 5  ,  -3  5  ,   15 7 ,  1  5 ) "};
    int i = 0;
    Triangle_S triangles[1];
    int current_triangle = 0;
    int current_coord = 0;

    int real = CorrectWritingTriangle(str, &i, triangles, current_triangle, &current_coord);

    int exp = 1;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfTriangle, NotABracketAfterName)
{
    char str[50] = {"  triangle a ( 1 5  ,  -3  5  ,   15 7 ,  1  5 ) "};
    int i = 0;
    Triangle_S triangles[1];
    int current_triangle = 0;
    int current_coord = 0;

    int real = CorrectWritingTriangle(str, &i, triangles, current_triangle, &current_coord);

    int exp = -1;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfTriangle, NotACoordAfterBracket)
{
    char str[50] = {"  triangle  ( a 1 5  ,  -3  5  ,   15 7 ,  1  5 ) "};
    int i = 0;
    Triangle_S triangles[1];
    int current_triangle = 0;
    int current_coord = 0;

    int real = CorrectWritingTriangle(str, &i, triangles, current_triangle, &current_coord);

    int exp = -2;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfTriangle, NotASpaceAfterXCoord)
{
    char str[50] = {"  triangle  (  1a 5  ,  -3  5  ,   15 7 ,  1  5 ) "};
    int i = 0;
    Triangle_S triangles[1];
    int current_triangle = 0;
    int current_coord = 0;

    int real = CorrectWritingTriangle(str, &i, triangles, current_triangle, &current_coord);

    int exp = -4;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfTriangle, NotAYCoordAfterXCoord)
{
    char str[50] = {"  triangle  (  1 a5  ,  -3  5  ,   15 7 ,  1  5 ) "};
    int i = 0;
    Triangle_S triangles[1];
    int current_triangle = 0;
    int current_coord = 0;

    int real = CorrectWritingTriangle(str, &i, triangles, current_triangle, &current_coord);

    int exp = -5;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfTriangle, NotACommaAfterYCoord)
{
    char str[50] = {"  triangle  (  1 5 a ,  -3  5  ,   15 7 ,  1  5 ) "};
    int i = 0;
    Triangle_S triangles[1];
    int current_triangle = 0;
    int current_coord = 0;

    int real = CorrectWritingTriangle(str, &i, triangles, current_triangle, &current_coord);

    int exp = -6;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfTriangle, CommaAfterLastYCoord)
{
    char str[50] = {"  triangle  (  1 5 ,  -3  5  ,   15 7 ,  1  5 , ) "};
    int i = 0;
    Triangle_S triangles[1];
    int current_triangle = 0;
    int current_coord = 0;

    int real = CorrectWritingTriangle(str, &i, triangles, current_triangle, &current_coord);

    int exp = -8;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfTriangle, NotABracketAfterLastYCoord)
{
    char str[50] = {"  triangle  (  1 5 ,  -3  5  ,   15 7 ,  1  5 a ) "};
    int i = 0;
    Triangle_S triangles[1];
    int current_triangle = 0;
    int current_coord = 0;

    int real = CorrectWritingTriangle(str, &i, triangles, current_triangle, &current_coord);

    int exp = -8;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfTriangle, TheTriangleDoesNotClose)
{
    char str[50] = {"  triangle  (  1 5 ,  -3  5  ,   15 7 ,  2  5  ) "};
    int i = 0;
    Triangle_S triangles[1];
    int current_triangle = 0;
    int current_coord = 0;

    int real = CorrectWritingTriangle(str, &i, triangles, current_triangle, &current_coord);

    int exp = -7;

    ASSERT_EQUAL(exp, real);
}

CTEST(ParseOfTriangle, NotEndAfterBracket)
{
    char str[50] = {"  triangle  (  1 5 ,  -3  5  ,   15 7 ,  1  5  ) a"};
    int i = 0;
    Triangle_S triangles[1];
    int current_triangle = 0;
    int current_coord = 0;

    int real = CorrectWritingTriangle(str, &i, triangles, current_triangle, &current_coord);

    int exp = -9;

    ASSERT_EQUAL(exp, real);
}

CTEST(Collisions, CircleIntersectsCircle)
{
    Circle_S Circles[2];
    Triangle_S Triangles[2];
    int NumCircles = 1, NumTriangles = 1;
    int NumOfFigures = NumCircles + NumTriangles;
    short Collisions[NumOfFigures][NumOfFigures];

    Circles[0].x = 3;
    Circles[0].y = 5;
    Circles[0].radius = 2;
    Circles[1].x = 5;
    Circles[1].y = 5;
    Circles[1].radius = 2;

    CheckForCollisions(Circles, Triangles, NumCircles, NumTriangles, Collisions);

    ASSERT_EQUAL(0, Collisions[0][0]);
    ASSERT_EQUAL(1, Collisions[0][1]);
    ASSERT_EQUAL(0, Collisions[1][1]);
    ASSERT_EQUAL(1, Collisions[1][0]);
}

CTEST(Collisions, CircleNotIntersectsCircle)
{
    Circle_S Circles[2];
    Triangle_S Triangles[2];
    int NumCircles = 2, NumTriangles = 0;
    int NumOfFigures = NumCircles + NumTriangles;
    short Collisions[NumOfFigures][NumOfFigures];

    Circles[0].x = 10;
    Circles[0].y = 5;
    Circles[0].radius = 2;
    Circles[1].x = 5;
    Circles[1].y = 5;
    Circles[1].radius = 2;

    CheckForCollisions(Circles, Triangles, NumCircles, NumTriangles, Collisions);

    ASSERT_EQUAL(0, Collisions[0][0]);
    ASSERT_EQUAL(0, Collisions[0][1]);
    ASSERT_EQUAL(0, Collisions[1][1]);
    ASSERT_EQUAL(0, Collisions[1][0]);
}

CTEST(Collisions, CircleAndTriangleAreNotIntersects)
{
    Circle_S Circles[1];
    Triangle_S Triangles[1];
    int NumCircles = 1, NumTriangles = 1;
    int NumOfFigures = NumCircles + NumTriangles;
    short Collisions[NumOfFigures][NumOfFigures];

    Circles[0].x = 0;
    Circles[0].y = 0;
    Circles[0].radius = 2;
    Triangles[0].x[0] = 10;
    Triangles[0].x[1] = 5;
    Triangles[0].x[2] = 7;
    Triangles[0].x[3] = 10;
    Triangles[0].y[0] = 10;
    Triangles[0].y[1] = 7;
    Triangles[0].y[2] = 5;
    Triangles[0].y[3] = 10;

    CheckForCollisions(Circles, Triangles, NumCircles, NumTriangles, Collisions);

    ASSERT_EQUAL(0, Collisions[0][0]);
    ASSERT_EQUAL(1, Collisions[0][1]);
    ASSERT_EQUAL(0, Collisions[1][1]);
    ASSERT_EQUAL(1, Collisions[1][0]);
}

CTEST(Collisions, CenterOfCircleInTriangle)
{
    Circle_S Circles[1];
    Triangle_S Triangles[1];
    int NumCircles = 1, NumTriangles = 1;
    int NumOfFigures = NumCircles + NumTriangles;
    short Collisions[NumOfFigures][NumOfFigures];

    Circles[0].x = 2;
    Circles[0].y = 2;
    Circles[0].radius = 2;
    Triangles[0].x[0] = 0;
    Triangles[0].x[1] = 5;
    Triangles[0].x[2] = 5;
    Triangles[0].x[3] = 0;
    Triangles[0].y[0] = 0;
    Triangles[0].y[1] = 5;
    Triangles[0].y[2] = 0;
    Triangles[0].y[3] = 0;

    CheckForCollisions(Circles, Triangles, NumCircles, NumTriangles, Collisions);

    ASSERT_EQUAL(0, Collisions[0][0]);
    ASSERT_EQUAL(1, Collisions[0][1]);
    ASSERT_EQUAL(0, Collisions[1][1]);
    ASSERT_EQUAL(1, Collisions[1][0]);
}

CTEST(Collisions, ApexOfATriangleInCircle)
{
    Circle_S Circles[1];
    Triangle_S Triangles[1];
    int NumCircles = 1, NumTriangles = 1;
    int NumOfFigures = NumCircles + NumTriangles;
    short Collisions[NumOfFigures][NumOfFigures];

    Circles[0].x = 0;
    Circles[0].y = 0;
    Circles[0].radius = 6;
    Triangles[0].x[0] = 10;
    Triangles[0].x[1] = 5;
    Triangles[0].x[2] = 5;
    Triangles[0].x[3] = -9;
    Triangles[0].y[0] = 10;
    Triangles[0].y[1] = 5;
    Triangles[0].y[2] = 0;
    Triangles[0].y[3] = 9;

    CheckForCollisions(Circles, Triangles, NumCircles, NumTriangles, Collisions);

    ASSERT_EQUAL(0, Collisions[0][0]);
    ASSERT_EQUAL(1, Collisions[0][1]);
    ASSERT_EQUAL(0, Collisions[1][1]);
    ASSERT_EQUAL(1, Collisions[1][0]);
}

CTEST(Collisions, PerpendicularLessThanRadius)
{
    Circle_S Circles[1];
    Triangle_S Triangles[1];
    int NumCircles = 1, NumTriangles = 1;
    int NumOfFigures = NumCircles + NumTriangles;
    short Collisions[NumOfFigures][NumOfFigures];

    Circles[0].x = 0;
    Circles[0].y = 0;
    Circles[0].radius = 2;
    Triangles[0].x[0] = 2;
    Triangles[0].x[1] = 2;
    Triangles[0].x[2] = 5;
    Triangles[0].x[3] = 2;
    Triangles[0].y[0] = 2;
    Triangles[0].y[1] = -2;
    Triangles[0].y[2] = 0;
    Triangles[0].y[3] = 2;

    CheckForCollisions(Circles, Triangles, NumCircles, NumTriangles, Collisions);

    ASSERT_EQUAL(0, Collisions[0][0]);
    ASSERT_EQUAL(1, Collisions[0][1]);
    ASSERT_EQUAL(0, Collisions[1][1]);
    ASSERT_EQUAL(1, Collisions[1][0]);
}

CTEST(Collisions, TriangleIntersectsTriangle)
{
    Circle_S Circles[2];
    Triangle_S Triangles[2];
    int NumCircles = 0, NumTriangles = 2;
    int NumOfFigures = NumCircles + NumTriangles;
    short Collisions[NumOfFigures][NumOfFigures];

    Triangles[0].x[0] = 0;
    Triangles[0].x[1] = 0;
    Triangles[0].x[2] = 7;
    Triangles[0].x[3] = 0;
    Triangles[0].y[0] = 0;
    Triangles[0].y[1] = 10;
    Triangles[0].y[2] = 5;
    Triangles[0].y[3] = 0;
    Triangles[1].x[0] = -1;
    Triangles[1].x[1] = 5;
    Triangles[1].x[2] = 5;
    Triangles[1].x[3] = -1;
    Triangles[1].y[0] = 5;
    Triangles[1].y[1] = 10;
    Triangles[1].y[2] = 0;
    Triangles[1].y[3] = 5;

    CheckForCollisions(Circles, Triangles, NumCircles, NumTriangles, Collisions);

    ASSERT_EQUAL(0, Collisions[0][0]);
    ASSERT_EQUAL(1, Collisions[0][1]);
    ASSERT_EQUAL(0, Collisions[1][1]);
    ASSERT_EQUAL(1, Collisions[1][0]);
}

CTEST(Collisions, TriangleNotIntersectsTriangle)
{
    Circle_S Circles[2];
    Triangle_S Triangles[2];
    int NumCircles = 0, NumTriangles = 2;
    int NumOfFigures = NumCircles + NumTriangles;
    short Collisions[NumOfFigures][NumOfFigures];

    Triangles[0].x[0] = 0;
    Triangles[0].x[1] = 1;
    Triangles[0].x[2] = 3;
    Triangles[0].x[3] = 0;
    Triangles[0].y[0] = 0;
    Triangles[0].y[1] = 1;
    Triangles[0].y[2] = 5;
    Triangles[0].y[3] = 0;
    Triangles[1].x[0] = 10;
    Triangles[1].x[1] = 15;
    Triangles[1].x[2] = 25;
    Triangles[1].x[3] = 10;
    Triangles[1].y[0] = 5;
    Triangles[1].y[1] = 10;
    Triangles[1].y[2] = 13;
    Triangles[1].y[3] = 5;

    CheckForCollisions(Circles, Triangles, NumCircles, NumTriangles, Collisions);

    ASSERT_EQUAL(0, Collisions[0][0]);
    ASSERT_EQUAL(0, Collisions[0][1]);
    ASSERT_EQUAL(0, Collisions[1][1]);
    ASSERT_EQUAL(0, Collisions[1][0]);
}