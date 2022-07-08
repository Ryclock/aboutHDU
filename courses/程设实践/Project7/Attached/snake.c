#include <windows.h>
#include <conio.h>
#include "snake.h"

Snake snake;
Food food;
enum considerHeadOrNot
{
    Head,
    NoHead,
};

/* 局部函数定义 */
void gotoXY(int x, int y);

void hide(void);

void init(void);

void initMap(void);

void initSnake(void);

void printFood(void);

void printScore(void);

/*
    startNode: Mainly whether or not to consider the snake head
        optional value reference: value in enum considerHeadOrNot
 */
bool isOnSnake(int startNode, int x, int y);

void moveSnake(void);

/* direction conflict */
bool isConflict(void);

void changeHead(void);

bool eatFood(void);

bool isDied(void);

bool isOnEdge(int x, int y);

/*
    snake.speed: sleeping delay time
    the higher score, the lower speed value
 */
void speedControl(void);

/* 接口函数实现 */
int PrintMenuAndGetChoice(void)
{
    PrintMenu();
    int result = GetChoice();
    system("cls");
    return result;
}

void PrintMenu(void)
{
    gotoXY(40, 12);
    printf("Welcome to Snake Game");
    gotoXY(43, 14);
    printf("1. Start Game");
    gotoXY(43, 16);
    printf("2. View Help");
    gotoXY(43, 18);
    printf("3. Information about us");
    gotoXY(43, 20);
    printf("Any other key to exit the game");
    hide();
}

int GetChoice(void)
{
    char ch = _getch();
    switch (ch)
    {
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    default:
        return 0;
    }
}

void StartGame(void)
{
    init();
    do
    {
        moveSnake();
    } while (!isDied());
    system("cls");
    gotoXY(45, 14);
    printf("Final Score: %d", snake.score);
    gotoXY(45, 16);
    printf("You lose!");
    gotoXY(45, 18);
    printf("Any key to return to menu");
    char ch = _getch();
    system("cls");
}

void PrintHelp(void)
{
    gotoXY(40, 12);
    printf("'w' UP");
    gotoXY(40, 14);
    printf("'s' DOWN");
    gotoXY(40, 16);
    printf("'a' LEFT");
    gotoXY(40, 18);
    printf("'d' RIGHT");
    gotoXY(40, 20);
    printf("Game over when the snake hits a wall or bites itself");
    gotoXY(45, 22);
    printf("Any key to return to menu");
    hide();
    char ch = _getch();
    system("cls");
}

void PrintAbout(void)
{
    gotoXY(30, 12);
    printf("HDU - program synthesis design practice");
    gotoXY(43, 14);
    printf("Snake - Console Game");
    gotoXY(43, 16);
    printf("Any key to return to menu");
    hide();
    char ch = _getch();
    system("cls");
}

/* 局部函数实现 */
void gotoXY(int x, int y)
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cor = {
        cor.X = x,
        cor.Y = y,
    };
    SetConsoleCursorPosition(hout, cor);
}

void hide(void)
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO corInfo = {1, false};
    SetConsoleCursorInfo(hout, &corInfo);
}

void init(void)
{
    hide();
    initMap();
    initSnake();
    printFood();
    printScore();
}

void initMap(void)
{
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        gotoXY(i, 0);
        printf("-");
        gotoXY(i, MAP_HEIGHT - 1);
        printf("-");
    }
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        gotoXY(0, i);
        printf("|");
        gotoXY(MAP_WIDTH - 1, i);
        printf("|");
    }
}

void initSnake(void)
{
    snake.score = 0;
    snake.length = 3;
    snake.speed = 250;
    snake.nowForward = snake.laterForward = RIGHT;
    snake.body[0].x = MAP_WIDTH / 2 - 1;
    snake.body[0].y = MAP_HEIGHT / 2 - 1;
    gotoXY(snake.body[0].x, snake.body[0].y);
    printf("@");
    for (int i = 1; i < snake.length; i++)
    {
        snake.body[i].x = snake.body[i - 1].x - 1;
        snake.body[i].y = snake.body[i - 1].y;
        gotoXY(snake.body[i].x, snake.body[i].y);
        printf("o");
    }
}

void printFood(void)
{
    do
    {
        food.x = rand() % (MAP_WIDTH - 2) + 1;
        food.y = rand() % (MAP_HEIGHT - 2) + 1;
    } while (isOnSnake(Head, food.x, food.y));
    gotoXY(food.x, food.y);
    printf("$");
}

void printScore(void)
{
    gotoXY(MAP_WIDTH + 10, 5);
    printf("Current Score: %d", snake.score);
}

bool isOnSnake(int startNode, int x, int y)
{
    for (int i = startNode; i < snake.length; i++)
    {
        if (x == snake.body[i].x && y == snake.body[i].y)
        {
            return true;
        }
    }
    return false;
}

void moveSnake(void)
{
    SnakeNode temp = {
        .x = snake.body[snake.length - 1].x,
        .y = snake.body[snake.length - 1].y,
    };
    for (int i = snake.length - 1; i >= 1; i--)
    {
        snake.body[i].x = snake.body[i - 1].x;
        snake.body[i].y = snake.body[i - 1].y;
    }
    gotoXY(snake.body[1].x, snake.body[1].y);
    printf("o");

    if (_kbhit())
    {
        snake.laterForward = _getch();
        if (!isConflict())
        {
            snake.nowForward = snake.laterForward;
        }
    }
    changeHead();

    if (eatFood())
    {
        snake.body[snake.length - 1].x = temp.x;
        snake.body[snake.length - 1].y = temp.y;
        printFood();
        printScore();
    }
    else
    {
        gotoXY(temp.x, temp.y);
        printf(" ");
    }

    speedControl();
    Sleep(snake.speed);
}

bool isConflict(void)
{
    return (snake.laterForward == UP && snake.nowForward == DOWN) ||
           (snake.laterForward == DOWN && snake.nowForward == UP) ||
           (snake.laterForward == LEFT && snake.nowForward == RIGHT) ||
           (snake.laterForward == RIGHT && snake.nowForward == LEFT);
}

void changeHead(void)
{
    switch (snake.nowForward)
    {
    case UP:
        snake.body[0].y--;
        break;
    case DOWN:
        snake.body[0].y++;
        break;
    case LEFT:
        snake.body[0].x--;
        break;
    case RIGHT:
        snake.body[0].x++;
        break;
    }
    gotoXY(snake.body[0].x, snake.body[0].y);
    printf("@");
}

bool eatFood(void)
{
    if (snake.body[0].x == food.x && snake.body[0].y == food.y)
    {
        snake.length++;
        snake.score++;
        return true;
    }
    return false;
}

bool isDied(void)
{
    return isOnSnake(NoHead, snake.body[0].x, snake.body[0].y) || isOnEdge(snake.body[0].x, snake.body[0].y);
}

bool isOnEdge(int x, int y)
{
    return x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1;
}

void speedControl(void)
{
    switch (snake.score)
    {
    case 3:
        snake.speed = 200;
        break;
    case 6:
        snake.speed = 180;
        break;
    case 9:
        snake.speed = 160;
        break;
    case 12:
        snake.speed = 140;
        break;
    case 15:
        snake.speed = 120;
        break;
    case 18:
        snake.speed = 100;
        break;
    case 21:
        snake.speed = 80;
        break;
    case 24:
        snake.speed = 60;
        break;
    case 27:
        snake.speed = 40;
        break;
    default:
        break;
    }
}