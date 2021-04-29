#include <libgeometry/geometry.h>

int main()
{
    int NumberOfStrings = 10, NumberOfSymbolsInString = 100;
    char str[NumberOfSymbolsInString];
    int i = 0, IsThatATriangle, IsThatACircle;
    int CurrentString = 1, CurrentCircle = 0, CurrentTriangle = 0;
    Circle_S Circles[NumberOfStrings];
    Triangle_S Triangles[NumberOfStrings];
    int NumberOfFigures;
    int CurrentCoord = 0;

    FILE* InputData;
    InputData = fopen("input.txt", "r");
    if (InputData == NULL)
    {
        printf("ошибка открытия файла\n");
        return -1;
    }

    while (1)
    {
        if (CurrentString == NumberOfStrings)
        {
            printf("Превышено количество строк, максимум: %d\n", NumberOfStrings);
            break;
        }

        if (fgets(str, NumberOfSymbolsInString, InputData) == NULL)
        {
            break;
        }

        if ((IsThatACircle = CorrectWritingCircle(str, &i, Circles, CurrentCircle)) < 0)
        {
            switch (IsThatACircle)
            {
            case -1:
                printf("Ошибка в синтаксисе: Ожидается '(' после 'circle'\n");
                break;
            case -2:
                printf("Ошибка в синтаксисе: Ожидается координата после '('\n");
                break;
            case -3:
                printf("Ошибка в синтаксисе: Ожидается ' ' после первой координаты\n");
                break;
            case -4:
                printf("Ошибка в синтаксисе: Ожидается вторая координата после первой координаты\n");
                break;
            case -5:
                printf("Ошибка в синтаксисе: Ожидается ',' после второй координаты\n");
                break;
            case -6:
                printf("Ошибка в синтаксисе: Ожидается радиус после ','\n");
                break;
            case -7:
                printf("Ошибка: Радиус не может быть отрицательным\n");
                break;
            case -8:
                printf("Ошибка в синтаксисе: Ожидается ')' после радиуса\n");
                break;
            case -9:
                printf("Ошибка в синтаксисе: ожидается 'символ конца строки' после ')'\n");
                break;
            }
            printf("Ошибка в строке №%d\n", CurrentString);
            CurrentString = -1;
            break;
        }

        if (IsThatACircle == 0)
        {
            Circles[CurrentCircle].perimeter = PerimeterOfACircle(Circles[CurrentCircle]);
            Circles[CurrentCircle].area = AreaOfACircle(Circles[CurrentCircle]);

            CurrentCircle++;
        }

        if ((IsThatATriangle = CorrectWritingTriangle(str, &i, Triangles, CurrentTriangle, &CurrentCoord)) < 0)
        {
            switch (IsThatATriangle)
            {
            case -1:
                printf("Ошибка в синтаксисе: Ожидается '(' после 'triangle'\n");
                break;
            case -2:
                printf("Ошибка в синтаксисе: Ожидается %d-я X координата после '('\n", CurrentCoord + 1);
                break;
            case -3:
                printf("Ошибка в синтаксисе: Ожидается %d-я X координата после %d-й ','\n", CurrentCoord + 1, CurrentCoord);
                break;
            case -4:
                printf("Ошибка в синтаксисе: Ожидается ' ' после %d-й X координаты\n", CurrentCoord + 1);
                break;
            case -5:
                printf("Ошибка в синтаксисе: Ожидается %d-я Y координата после %d-й X координаты\n", CurrentCoord + 1, CurrentCoord + 1);
                break;
            case -6:
                printf("Ошибка в синтаксисе: Ожидается ',' после %d-й Y координаты\n", CurrentCoord + 1);
                break;
            case -7:
                printf("Первая координата не соответствует последней -> треугольник не замыкается\n");
                break;
            case -8:
                printf("Ошибка в синтаксисе: Ожидается ')' после последней координаты\n");
                break;
            case -9:
                printf("Ошибка в синтаксисе: ожидается 'символ конца строки' после ')'\n");
                break;
            }
            printf("Ошибка в строке №%d\n", CurrentString);
            CurrentString = -1;
            break;
        }

        CurrentCoord = 0;

        if (IsThatATriangle == 0)
        {
            Triangles[CurrentTriangle].perimeter = PerimeterOfATriangle(Triangles[CurrentTriangle]);
            Triangles[CurrentTriangle].area = AreaOfATriangle(Triangles[CurrentTriangle]);

            if (Triangles[CurrentTriangle].area == 0)
            {
                printf("Ошибка: вершины треугольника совпадают или находятся на одной прямой\n");
                break;
            }

            CurrentTriangle++;
        }

        if ((IsThatACircle == 1) && (IsThatATriangle == 1))
        {
            printf("Ошибка в строке №%d, название фигуры не соответствует 'circle' или 'triangle'\n", CurrentString);
            break;
        }

        CurrentString++;
    }

    if (CurrentString == -1)
    {
        return -1;
    }

    NumberOfFigures = CurrentCircle + CurrentTriangle;
    short Collisions[NumberOfFigures][NumberOfFigures];

    CheckForCollisions(Circles, Triangles, CurrentCircle, CurrentTriangle, Collisions);

    for (int k = 0; k < NumberOfFigures; k++)
    {
        for (int l = 0; l < NumberOfFigures; l++)
        {
            if ((k < CurrentCircle) && (l == 0))
            {
                printf("%d.     circle(%f %f, %f)\n", k + 1, Circles[k].x, Circles[k].y, Circles[k].radius);
                printf("\tperimeter = %f\n", Circles[k].perimeter);
                printf("\tarea = %f\n", Circles[k].area);
                printf("\tintersects:\n");
            }

            if ((k >= CurrentCircle) && (l == 0))
            {
                printf("%d.     triangle(", k + 1);
                printf("%f %f", Triangles[k - CurrentCircle].x[0], Triangles[k - CurrentCircle].y[0]);
                printf(", %f %f", Triangles[k - CurrentCircle].x[1], Triangles[k - CurrentCircle].y[1]);
                printf(", %f %f", Triangles[k - CurrentCircle].x[2], Triangles[k - CurrentCircle].y[2]);
                printf(", %f %f)\n", Triangles[k - CurrentCircle].x[3], Triangles[k - CurrentCircle].y[3]);
                printf("\tperimeter = %f\n", Triangles[k - CurrentCircle].perimeter);
                printf("\tarea = %f\n", Triangles[k - CurrentCircle].area);
                printf("\tintersects:\n");
            }

            if ((Collisions[k][l] == 1) && (l < CurrentCircle))
            {
                printf("\t\t%d. circle\n", l + 1);
            }

            if ((Collisions[k][l] == 1) && (l >= CurrentCircle))
            {
                printf("\t\t%d. triangle\n", l + 1);
            }
        }
        printf("\n");
    }
    return 0;
}