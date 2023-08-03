#include <iostream>
#include <Windows.h>

const int width = 30;
const int height = 30;
int grid[width][height] = {0};
int nextGrid[width][height] = {0};

void setup()
{
    // ???????
    // ????????????????
    grid[width / 2][height / 2] = 1;
    grid[width / 2 + 1][height / 2] = 1;
    grid[width / 2][height / 2 + 1] = 1;
    grid[width / 2 - 1][height / 2 - 1] = 1;
    grid[width / 2][height / 2 - 1] = 1;
}

void draw()
{
    // ????????????
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(hConsole, pos);

    // ??????
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (grid[x][y] == 1)
                std::cout << "¡ö";
            else
                std::cout << "¡õ";
        }
        std::cout << std::endl;
    }
}

int countNeighbors(int x, int y)
{
    // ??(x, y)???????
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int neighborX = x + i;
            int neighborY = y + j;
            if (neighborX >= 0 && neighborX < width && neighborY >= 0 && neighborY < height)
            {
                if (i != 0 || j != 0)
                    count += grid[neighborX][neighborY];
            }
        }
    }
    return count;
}

void update()
{
    // ??????
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int neighbors = countNeighbors(x, y);
            if (grid[x][y] == 1)
            {
                if (neighbors < 2 || neighbors > 3)
                    nextGrid[x][y] = 0; // ???????,??
                else
                    nextGrid[x][y] = 1; // 2?3????,????
            }
            else
            {
                if (neighbors == 3)
                    nextGrid[x][y] = 1; // ??????3????,??
                else
                    nextGrid[x][y] = 0; // ????,????
            }
        }
    }

    // ?nextGrid???grid,??????
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            grid[x][y] = nextGrid[x][y];
        }
    }
}

int main()
{
    setup();

    while (true)
    {
        draw();
        update();
        Sleep(100); // ??????,?????(???0.1?)
    }

    return 0;
}
