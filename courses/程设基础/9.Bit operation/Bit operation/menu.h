
#define WIDTH 40
#define MIDDLE 25
#define LEFT 5
#define SPACE ' '
#define SIGN '*'

void Menu(void)
{
    int spaces;
    int middle;

    char *top = "THE MENU";
    char *start = "Bit Operation";
    char *end = "Made@Ryclock";
    char *choice1 = "1-'&'";
    char *choice2 = "2-'|'";
    char *choice3 = "3-'~'";
    char *choice4 = "4-'^'";
    char *choice5 = "5-'<<'";
    char *choice6 = "6-'>>'";
    char *choice7 = "7-PrintfBinary";
    char *choice8 = "8-Encryption";
    char *choice9 = "9-Decrypt";
    char *choice10 = "10-C_E_devision";
    char *choice11 = "11-Exit";

    top_line('=', top);
    printf("\n\n");

    top_line('*', start);

    printf("\n\t%c", SIGN);
    show_n_char(SPACE, WIDTH);
    printf("%c", SIGN);
    printf("\n\t%c", SIGN);
    show_n_char(SPACE, WIDTH);
    printf("%c", SIGN);

    every_line('$', choice1);
    every_line('$', choice2);
    every_line('$', choice3);
    every_line('$', choice4);
    every_line('$', choice5);
    every_line('$', choice6);
    every_line('$', choice7);
    every_line('$', choice8);
    every_line('$', choice9);
    every_line('$', choice10);
    every_line('$', choice11);

    printf("\n\t%c", SIGN);
    show_n_char(SPACE, WIDTH);
    printf("%c", SIGN);

    top_line('*', end);
}

void top_line(char ch, char *pch) //头尾行输出
{
    int m, i;

    m = (WIDTH - strlen(pch)) / 2;

    printf("\n\t%c", ch);
    show_n_char(ch, m); // printf("%s", pch);
    for (i = 0; i < strlen(pch); i++)
    {
        printf("%c", *(pch + i));
    }
    show_n_char(ch, WIDTH + 1 - strlen(pch) - m);
}

void every_line(char ch, char *pch)
{
    printf("\n\t%c", ch);
    show_n_char(SPACE, LEFT);
    printf("%s", pch);
    show_n_char(SPACE, WIDTH - strlen(pch) - LEFT);
    printf("%c", ch);
    printf("\n\t%c", ch);
    show_n_char(SPACE, WIDTH);
    printf("%c", ch);
}

void show_n_char(char ch, int num) //输出num个ch字符
{
    int count;

    for (count = 1; count <= num; count++)
    {
        putchar(ch);
    }
}
