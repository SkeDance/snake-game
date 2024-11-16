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


enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};


class Snake
{
    public:
        bool IsOccupied(int x, int y)
        {
            for (int i = 0; i < snake_len; ++i)
            {
                if (snake_x[i] == x && snake_y[i] == y)
                {
                    return true;
                }
            }
            return false;
        }

        int DrawSnake()
        {
            return snake;
        }
        void GrowSnake()
        {
            if (snake_len < max_lenght_snake)
            {
                snake_len++;
            }
        }
        int GetSnakeLenght()
        {
            return snake_len;
        }
        void SetSnakePosition()
        {
            snake_x[0] = width / 2;
            snake_y[0] = height / 2;
        }
        int GetSnakeHeadPosition_x()
        {
            return snake_x[0];
        }
        int GetSnakeHeadPosition_y()
        {
            return snake_y[0];
        }
        int GetSnakeTailPosition_x(int i)
        {
            return snake_x[i];
        }
        int GetSnakeTailPosition_y(int i)
        {
            return snake_y[i];
        }
        void MoveHead(Direction dir)
        {
            snake_x[0] += directionTable[static_cast<int>(dir)][0];
            snake_y[0] += directionTable[static_cast<int>(dir)][1];
        }
        
        void UpdateSnakeBody()
        {
            for (int i = snake_len - 1; i > 0; --i)
            {
                snake_x[i] = snake_x[i - 1];
                snake_y[i] = snake_y[i - 1];
            }
        }     

    private:
        char snake = 'O';
        int max_lenght_snake = (width - 3) * (height - 2);    
        int snake_x[(width - 3) * (height - 2)] = {0};
        int snake_y[(width - 3) * (height - 2)] = {0};
        int snake_len = 1;

        int directionTable[4][2] = {
            {0, -1},
            {0, 1},
            {-1, 0},
            {1, 0}
        };
};

class KeyBoard
{
    public:
        void KeyBoardPoll()
        {
            if (GetKeyState('A') & 0x8000)
			if (snake_dir != RIGHT)
				snake_dir = LEFT;
		if (GetKeyState('D') & 0x8000)
			if (snake_dir != LEFT)
				snake_dir = RIGHT;
		if (GetKeyState('W') & 0x8000)
			if (snake_dir != DOWN)
				snake_dir = UP;

		if (GetKeyState('S') & 0x8000)
			if (snake_dir != UP)
				snake_dir = DOWN;
        }

        Direction GetSnakeDir()
        {
            return snake_dir;
        }
    private:
        Direction snake_dir = UP;
};

class Food
{
    public:
        void SetFoodPosition(Snake& snake)
        {
            bool validPosition = false;
            while(!validPosition)
            {
                food_x = 1 + (rand() % (width - 3));
                food_y = 1 + (rand() % (height - 2));
                if (!snake.IsOccupied(food_x, food_y))
                {
                    validPosition = true;
                }
            }
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
    Snake snake;
    KeyBoard keyboard;

    snake.SetSnakePosition();

    srand(time(0));
    double time1 = clock();
    while(Game)
    {
        keyboard.KeyBoardPoll();

        if ((clock() - time1) / CLOCKS_PER_SEC >= 1) 
		{
            time1 = clock();
            if (snake.GetSnakeHeadPosition_x() == apple.GetFoodPosition_x() && snake.GetSnakeHeadPosition_y() == apple.GetFoodPosition_y())
            {
                snake.GrowSnake();
                apple.SetFoodPosition(snake);
            }
            
            snake.UpdateSnakeBody();
            
            snake.MoveHead(keyboard.GetSnakeDir());

            if (snake.GetSnakeHeadPosition_x() == 0 || snake.GetSnakeHeadPosition_y() == 0 || snake.GetSnakeHeadPosition_x() == width - 2 || snake.GetSnakeHeadPosition_y() == height - 1)
            {
                Game = false;
            }
            for (int i = 1; i < snake.GetSnakeLenght(); ++i)
            {
                if (snake.GetSnakeHeadPosition_x() == snake.GetSnakeTailPosition_x(i) && snake.GetSnakeHeadPosition_y() == snake.GetSnakeTailPosition_y(i))
                {
                    Game = false;
                    i = snake.GetSnakeLenght();
                }
            }
            gotoxy(0, 0);
            map[apple.GetFoodPosition_y() * width + apple.GetFoodPosition_x()] = apple.DrawFood();
            for(int i = 0; i < snake.GetSnakeLenght(); ++i)
            {
                map[snake.GetSnakeTailPosition_y(i) * width + snake.GetSnakeTailPosition_x(i)] = snake.DrawSnake();
            }
            cout << map;
            for(int i = 0; i < snake.GetSnakeLenght(); ++i)
            {
                map[snake.GetSnakeTailPosition_y(i) * width + snake.GetSnakeTailPosition_x(i)] = ' ';
            }
        }
    }
    gotoxy(1, height / 2);
    cout << "Score: " << snake.GetSnakeLenght() << endl;
    gotoxy(width, height);
}
