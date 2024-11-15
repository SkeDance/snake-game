#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

const int width = 26;
const int height = 13;

const int max_lenght_snake = (width - 3) * (height - 2);

const int up = 0;
const int down = 1;
const int LEFT = 2;
const int RIGHT = 3;

char snake = 'O';
char food = '*';

int snake_dir = up;

bool Game = true;


int snake_x[max_lenght_snake] = {0};
int snake_y[max_lenght_snake] = {0};
int snake_len = 1;


char map[] = 
"#########################\n"
"#                       #\n"
"#                       #\n"
"#                       #\n"
"#                       #\n"
"#                       #\n"
"#                       #\n"
"#                       #\n"
"#                       #\n"
"#                       #\n"
"#                       #\n"
"#                       #\n"
"#########################\n";
// "########################################\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "#                                      #\n"
// "########################################\n";

void gotoxy(int x, int y)
{
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}


int food_x = 1 + (rand() % (width - 3));
int food_y = 1 + (rand() % (height - 2));


int main()
{
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
            if (snake_x[0] == food_x && snake_y[0] == food_y)
            {
                ++snake_len;
                srand(time(0));
                int food_x = 1 + (rand() % (width - 3));
                int food_y = 1 + (rand() % (height - 2));
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
            map[food_y * width + food_x] = food;
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
