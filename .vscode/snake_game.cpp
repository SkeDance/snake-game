#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

bool Game = true;

const int width = 41;
const int height = 20;
char map[] = 
"########################################\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"#                                      #\n"
"########################################\n";

const int max_lenght_snake = (width - 3) * (height - 2);
char snake = 'O';
int snake_x[max_lenght_snake] = {0};
int snake_y[max_lenght_snake] = {0};
int snake_len = 1;
enum Direction
{
    up,
    down,
    LEFT,
    RIGHT
};
int snake_dir = up;

class Food
{
    public:
        void SetFoodPosition_x()
        {
            food_x = 1 + (rand() % (width - 3));
        }
        void SetFoodPosition_y()
        {
            food_y = 1 + (rand() % (height - 2));
        }
        int GetFoodPosition_x()
        {
            return food_x;
        }
        int GetFoodPosition_y()
        {
            return food_y;
        }
        int DrawFood()
        {
            return food;
        }

    private:
        int food_x = 1 + (rand() % (width - 3));
        int food_y = 1 + (rand() % (height - 2));
        char food = '*';
};

void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

int main()
{
    Food apple;
    snake_x[0] = width / 2;
    snake_y[0] = height / 2;


    int time1 = clock();
    while(Game)
    {
        srand(time(0));
        if (GetKeyState('A') & 0x8000)
			if (snake_dir != RIGHT)
				snake_dir = LEFT;
		if (GetKeyState('D') & 0x8000)
			if (snake_dir != LEFT)
				snake_dir = RIGHT;
		if (GetKeyState('W') & 0x8000)
			if (snake_dir != down)
				snake_dir = up;

		if (GetKeyState('S') & 0x8000)
			if (snake_dir != up)
				snake_dir = down;

        if ((clock() - time1) / CLOCKS_PER_SEC >= 1) 
		{
            time1 = clock();
            if (snake_x[0] == apple.GetFoodPosition_x() && snake_y[0] == apple.GetFoodPosition_y())
            {
                ++snake_len;
                apple.SetFoodPosition_x();
                apple.SetFoodPosition_y();
            }
            
			for (int i = snake_len - 2; i >= 0; --i)
			{
				snake_x[i + 1] = snake_x[i];
				snake_y[i + 1] = snake_y[i];
			}

            if (snake_dir == 0)
            {
                --snake_y[0];
            }
            if (snake_dir == 1)
            {
                ++snake_y[0];
            }
            if (snake_dir == 2)
            {
                --snake_x[0];
            }
            if (snake_dir == 3)
            {
                ++snake_x[0];
            }

            if (snake_x[0] == 0 || snake_y[0] == 0 || snake_x[0] == width - 2 || snake_y[0] == height - 1)
            {
                Game = false;
            }
            for (int i = 1; i < snake_len; ++i)
            {
                if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i])
                {
                    Game = false;
                    i = snake_len;
                }
            }
            gotoxy(0, 0);
            map[apple.GetFoodPosition_y() * width + apple.GetFoodPosition_x()] = apple.DrawFood();
            for(int i = 0; i < snake_len; ++i)
            {
                map[snake_y[i] * width + snake_x[i]] = snake;
            }
            cout << map;
            for(int i = 0; i < snake_len; ++i)
            {
                map[snake_y[i] * width + snake_x[i]] = ' ';
            }
        }
    }
    gotoxy(1, height / 2);
    cout << "Score: " << snake_len << endl;
    gotoxy(width, height);
}
