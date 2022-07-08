#include "snake.h"

int main(void)
{
    srand((unsigned int)time(0));
    bool isContinue = true;
    while (isContinue)
    {
        int choice = PrintMenuAndGetChoice();
        switch (choice)
        {
        case 1:
            StartGame();
            break;
        case 2:
            PrintHelp();
            break;
        case 3:
            PrintAbout();
            break;
        default:
            isContinue = false;
            break;
        }
    }
    return 0;
}