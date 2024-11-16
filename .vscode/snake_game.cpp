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

class Snake
{
    public:
        
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
        void MoveSnakeHead_mx()
        {
            --snake_x[0];
        }
        void MoveSnakeHead_px()
        {
            ++snake_x[0];
        }
        void MoveSnakeHead_my()
        {
            --snake_y[0];
        }
        void MoveSnakeHead_py()
        {
            ++snake_y[0];
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
};



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
    Snake Spaghetti;
    Spaghetti.SetSnakePosition();

    srand(time(0));
    int time1 = clock();
    while(Game)
    {
        
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
            if (Spaghetti.GetSnakeHeadPosition_x() == apple.GetFoodPosition_x() && Spaghetti.GetSnakeHeadPosition_y() == apple.GetFoodPosition_y())
            {
                Spaghetti.GrowSnake();
                apple.SetFoodPosition_x();
                apple.SetFoodPosition_y();
                cout << Spaghetti.GetSnakeLenght();
            }
            
            Spaghetti.UpdateSnakeBody();
            
	        if (snake_dir == 0)
            {
                Spaghetti.MoveSnakeHead_my();
            }
            if (snake_dir == 1)
            {
                 Spaghetti.MoveSnakeHead_py();
            }
            if (snake_dir == 2)
            {
                Spaghetti.MoveSnakeHead_mx();
            }
            if (snake_dir == 3)
            {
                Spaghetti.MoveSnakeHead_px();
            }

            if (Spaghetti.GetSnakeHeadPosition_x() == 0 || Spaghetti.GetSnakeHeadPosition_y() == 0 || Spaghetti.GetSnakeHeadPosition_x() == width - 2 || Spaghetti.GetSnakeHeadPosition_y() == height - 1)
            {
                Game = false;
            }
            for (int i = 1; i < Spaghetti.GetSnakeLenght(); ++i)
            {
                if (Spaghetti.GetSnakeHeadPosition_x() == Spaghetti.GetSnakeTailPosition_x(i) && Spaghetti.GetSnakeHeadPosition_y() == Spaghetti.GetSnakeTailPosition_y(i))
                {
                    Game = false;
                    i = Spaghetti.GetSnakeLenght();
                }
            }
            gotoxy(0, 0);
            map[apple.GetFoodPosition_y() * width + apple.GetFoodPosition_x()] = apple.DrawFood();
            for(int i = 0; i < Spaghetti.GetSnakeLenght(); ++i)
            {
                map[Spaghetti.GetSnakeTailPosition_y(i) * width + Spaghetti.GetSnakeTailPosition_x(i)] = Spaghetti.DrawSnake();
            }
            cout << map;
            for(int i = 0; i < Spaghetti.GetSnakeLenght(); ++i)
            {
                map[Spaghetti.GetSnakeTailPosition_y(i) * width + Spaghetti.GetSnakeTailPosition_x(i)] = ' ';
            }
        }
    }
    gotoxy(1, height / 2);
    cout << "Score: " << Spaghetti.GetSnakeLenght() << endl;
    gotoxy(width, height);
}
