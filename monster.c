#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define abs(x) ((x < 0) ? -(x) : (x))

void printMatrix(char **matrix, int ny, int nx)
{
    int x, y;
    for (y = ny - 1; y > -1; y--)
    {
        for (x = 0; x < nx; x++)
        {
            printf("%c ", matrix[y][x]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int boardX = atoi(argv[1]),
        boardY = atoi(argv[2]),
        plrX = atoi(argv[3]),
        plrY = atoi(argv[4]),
        goalX = atoi(argv[5]),
        goalY = atoi(argv[6]),
        monX = atoi(argv[7]),
        monY = atoi(argv[8]),
        x, y;

    // allocate memory for a 2d array of size boardX * boardY
    char **matrix = (char **)malloc(boardY * sizeof(char *));
    for (y = 0; y < boardY; y++)
        matrix[y] = malloc(boardX * sizeof(char));

    // initialize the matrix values
    for (y = 0; y < boardY; y++)
    {
        for (x = 0; x < boardX; x++)
        {
            if (x == plrX && y == plrY)
                matrix[y][x] = 'P';
            else if (x == goalX && y == goalY)
                matrix[y][x] = 'G';
            else if (x == monX && y == monY)
                matrix[y][x] = 'M';
            else
                matrix[y][x] = '.';
        }
    }
    printMatrix(matrix, boardY, boardX);

    // prep work is done, put the logic of the game here
    char playerMove = ' ';
    srand(time(NULL));
    while (scanf("%c", &playerMove) != EOF)
    {
        if (playerMove == '\n')
            continue;

        switch (playerMove)
        {
        case 'W':
            if (plrX - 1 >= 0)
            {
                matrix[plrY][plrX] = '.';
                plrX--;
                if (matrix[plrY][plrX] == 'G')
                {
                    printf("player wins!\n");
                    goto break_loop;
                }
                if (matrix[plrY][plrX] == 'M')
                {
                    printf("monster wins!\n");
                    goto break_loop;
                }
                matrix[plrY][plrX] = 'P';
            }
            else
                printf("invalid move\n");
            break;

        case 'E':
            if (plrX + 1 < boardX)
            {
                matrix[plrY][plrX] = '.';
                plrX++;
                if (matrix[plrY][plrX] == 'G')
                {
                    printf("player wins!\n");
                    goto break_loop;
                }
                if (matrix[plrY][plrX] == 'M')
                {
                    printf("monster wins!\n");
                    goto break_loop;
                }
                matrix[plrY][plrX] = 'P';
            }
            else
                printf("invalid move\n");
            break;

        case 'N':
            if (plrY + 1 < boardY)
            {
                matrix[plrY][plrX] = '.';
                plrY++;
                if (matrix[plrY][plrX] == 'G')
                {
                    printf("player wins!\n");
                    goto break_loop;
                }
                if (matrix[plrY][plrX] == 'M')
                {
                    printf("monster wins!\n");
                    goto break_loop;
                }
                matrix[plrY][plrX] = 'P';
            }
            else
                printf("invalid move\n");
            break;

        case 'S':
            if (plrY - 1 >= 0)
            {
                matrix[plrY][plrX] = '.';
                plrY--;
                if (matrix[plrY][plrX] == 'G')
                {
                    printf("player wins!\n");
                    goto break_loop;
                }
                if (matrix[plrY][plrX] == 'M')
                {
                    printf("monster wins!\n");
                    goto break_loop;
                }
                matrix[plrY][plrX] = 'P';
            }
            else
                printf("invalid move\n");
            break;
        default:
            printf("invalid move\n");
        }

        // monster move
        int verticalDistance = abs(monY - plrY);
        int horizontalDistance = abs(monX - plrX);

        int r = rand() % 2;
        if (verticalDistance == horizontalDistance)
        {
            // randomly pick horizontal or vertical
        }

        if (verticalDistance > horizontalDistance || (r == 1 && verticalDistance == horizontalDistance))
        {
            // reduce vertical distance
            if (monY - plrY > 0)
            {
                matrix[monY][monX] = '.';
                monY--;
                if (matrix[monY][monX] == 'G')
                {
                    monY++;
                    matrix[monY][monX] = 'M';
                    printMatrix(matrix, boardY, boardX);
                    continue;
                }
                printf("monster moves S\n");
                if (matrix[monY][monX] == 'P')
                {
                    printf("monster wins!\n");
                    goto break_loop;
                }
                matrix[monY][monX] = 'M';
                printMatrix(matrix, boardY, boardX);
            }
            else
            {
                matrix[monY][monX] = '.';
                monY++;
                if (matrix[monY][monX] == 'G')
                {
                    monY--;
                    matrix[monY][monX] = 'M';
                    printMatrix(matrix, boardY, boardX);
                    continue;
                }
                printf("monster moves N\n");
                if (matrix[monY][monX] == 'P')
                {
                    printf("monster wins!\n");
                    goto break_loop;
                }
                matrix[monY][monX] = 'M';
                printMatrix(matrix, boardY, boardX);
            }
        }
        if (verticalDistance < horizontalDistance || (r == 0 && verticalDistance == horizontalDistance))
        {
            // reduce horizontal distance
            if (monX - plrX > 0)
            {
                matrix[monY][monX] = '.';
                monX--;
                if (matrix[monY][monX] == 'G')
                {
                    monX++;
                    matrix[monY][monX] = 'M';
                    printMatrix(matrix, boardY, boardX);
                    continue;
                }
                printf("monster moves W\n");
                if (matrix[monY][monX] == 'P')
                {
                    printf("monster wins!\n");
                    goto break_loop;
                }
                matrix[monY][monX] = 'M';
                printMatrix(matrix, boardY, boardX);
            }
            else
            {
                matrix[monY][monX] = '.';
                monX++;
                if (matrix[monY][monX] == 'G')
                {
                    monX--;
                    matrix[monY][monX] = 'M';
                    printMatrix(matrix, boardY, boardX);
                    continue;
                }
                printf("monster moves E\n");
                if (matrix[monY][monX] == 'P')
                {
                    printf("monster wins!\n");
                    goto break_loop;
                }
                matrix[monY][monX] = 'M';
                printMatrix(matrix, boardY, boardX);
            }
        }
    }

break_loop:;

    // free allocated 2d array to avoid memory leak
    for (y = 0; y < boardY; y++)
        free(matrix[y]);
    free(matrix);

    return 0;
}