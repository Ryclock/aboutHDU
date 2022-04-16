/* Pictures.c -- C Project 1 - Print Graphics on the Screen */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

/*
 * Copyright(C)
 * All rights reserved.
 * Author : Ryclock
 * Date : 2021-11-22-11.55.57
 * Description :  Print Interesting Graphics Using C.
 */

#define WIDTH 60
#define MIDDLE 27
#define LEFT 5
#define RIGHT 45
#define SPACE ' '
#define SIGN '*'

void Menu(void);
void top_line(char ch);
void every_line(char *left, char *middle, char *right);
void show_n_char(char ch, int num);
void CHINA_520(void);
void Bear(void);
void Horse(void);
void Bird(void);
void Mouse(void);

int main(void)
{
    int choice;

    Menu();
    printf("Please choose one number : ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice)
    {
    case 1:
        CHINA_520();
        break;
    case 2:
        Bear();
        break;
    case 3:
        Horse();
        break;
    case 4:
        Bird();
        break;
    case 5:
        Mouse();
        break;
    case 6:
        return 0;
    default:
        printf("\n");
        printf("Wrong! Please choose another true number!!\n");
        printf("\n");
    }

    printf("\n\n\n\n");
    main();
    return 0;
}

void Menu(void)
{
    int spaces;

    char *top = "THE MENU";
    char *choice1 = "1.520CHINA";
    char *choice2 = "2.Bear";
    char *choice3 = "3.Horse";
    char *choice4 = "4.Bird";
    char *choice5 = "5.Mouse";
    char *choice6 = "6.Exit";
    char *copyright = "Made@Ryclock";

    top_line(SIGN);

    top_line(SPACE);

    spaces = (WIDTH - strlen(top)) / 2;
    putchar(SIGN);
    show_n_char(SPACE, spaces);
    printf("%s", top);
    show_n_char(SPACE, spaces);
    putchar(SIGN);
    putchar('\n');

    every_line(choice1, choice2, choice3);
    every_line(choice4, choice5, choice6);

    top_line(SPACE);

    spaces = (WIDTH - strlen(copyright)) / 2;
    putchar(SIGN);
    show_n_char(SPACE, spaces);
    printf("%s", copyright);
    show_n_char(SPACE, spaces);
    putchar(SIGN);
    putchar('\n');

    top_line(SIGN);
}

void top_line(char ch) //?¦Â?????
{
    printf("%c", SIGN); // putchar(SIGN);
    show_n_char(ch, WIDTH);
    putchar(SIGN);
    putchar('\n');
}

void every_line(char *left, char *middle, char *right) //??????§Ö?left??middle??right??????
{
    int spaces_ltom, spaces_mtor, spaces_r;

    spaces_ltom = MIDDLE - LEFT - strlen(left);
    spaces_mtor = RIGHT - MIDDLE - strlen(middle);
    spaces_r = WIDTH - RIGHT - strlen(right);

    putchar(SIGN);

    show_n_char(SPACE, LEFT);

    printf("%s", left);

    show_n_char(SPACE, spaces_ltom);

    printf("%s", middle);

    show_n_char(SPACE, spaces_mtor);

    printf("%s", right);

    show_n_char(SPACE, spaces_r);

    putchar(SIGN);
    putchar('\n');
}

void show_n_char(char ch, int num) //???num??ch???
{
    int count;

    for (count = 1; count <= num; count++)
    {
        putchar(ch);
    }
}

void CHINA_520(void)
{
    printf("\n\t       ,----,.                                              ");
    printf("\n\t     ,'   ,' |                                              ");
    printf("\n\t   ,'   .'   |     ,----,     ,----..                       ");
    printf("\n\t ,----.'    .'   .'   .' \   /   /   \                      ");
    printf("\n\t |    |   .'   ,----,'    | /   .     :                     ");
    printf("\n\t :    :  |--,  |    :  .  ;.   /   ;.  \                    ");
    printf("\n\t :    |  ;.' \ ;    |.'  /.   ;   /  ` ;                    ");
    printf("\n\t |    |      | `----'/  ; ;   |  ; \ ; |                    ");
    printf("\n\t `----'.'\   ;   /  ;  /  |   :  | ; | '                    ");
    printf("\n\t   __  \  .  |  ;  /  /-, .   |  ' ' ' :                    ");
    printf("\n\t /   /\/  /  : /  /  /.`| '   ;  \; /  |                    ");
    printf("\n\t/ ,,/  ',-   ./__;      :  \   \  ',  /                     ");
    printf("\n\t\ ''\       ;|   :    .'    ;   :    /                      ");
    printf("\n\t \   \    .' ;   | .'        \   \ .'                       ");
    printf("\n\t  `--`-,-'   `---' ,--,       `---`     ,--.                ");
    printf("\n\t  ,----..        ,--.'|   ,---,       ,--.'|   ,---,        ");
    printf("\n\t /   /   \    ,--,  | :,`--.' |   ,--,:  : |  '  .' \       ");
    printf("\n\t|   :     :,---.'|  : '|   :  :,`--.'`|  ' : /  ;    '.     ");
    printf("\n\t.   |  ;. /|   | : _' |:   |  '|   :  :  | |:  :       \    ");
    printf("\n\t.   ; /--` :   : |.'  ||   :  |:   |   \ | ::  |   /\   \   ");
    printf("\n\t;   | ;    |   ' '  ; :'   '  ;|   : '  '; ||  :  ' ;.   :  ");
    printf("\n\t|   : |    '   |  .'. ||   |  |'   ' ;.    ;|  |  ;/  \   \ ");
    printf("\n\t.   | '___ |   | :  | ''   :  ;|   | | \   |'  :  | \  \ ,' ");
    printf("\n\t'   ; : .'|'   : |  : ;|   |  ''   : |  ; .'|  |  '  '--'   ");
    printf("\n\t'   | '/  :|   | '  ,/ '   :  ||   | '`--'  |  :  :         ");
    printf("\n\t|   :    / ;   : ;--'  ;   |.' '   : |      |  | ,'         ");
    printf("\n\t \   \ .'  |   ,/      '---'   ;   |.'      `--''           ");
    printf("\n\t  `---`    '---'               '---'                        ");
}

void Bear(void)
{
    printf("\n\t??§»?§µ??????????? ");
    printf("\n\t                                                            ");
    printf("\n\t?§»?§»?????????????????? ");
    printf("\n\t                                                            ");
    printf("\n\t??§»????????????????????? ");
    printf("\n\t                                                            ");
    printf("\n\t?§»?M?????????????????????? ");
    printf("\n\t                                                            ");
    printf("\n\t??§º?????????????????????? ");
    printf("\n\t                                                            ");
    printf("\n\t?§»???????????????????????????? ");
    printf("\n\t                                                            ");
    printf("\n\t???????????????????????????? ");
    printf("\n\t                                                            ");
    printf("\n\t?§º?????????????????????????????????");
    printf("\n\t                                                            ");
    printf("\n\t??????????????????????????????? ??");
    printf("\n\t                                                            ");
    printf("\n\t???????????????????????????????}?{");
    printf("\n\t                                                            ");
    printf("\n\t???????????????????????????????????? ??");
    printf("\n\t                                                            ");
    printf("\n\t????????????????????????????????????? ??");
    printf("\n\t                                                            ");
    printf("\n\t?§»???????????????????????????????????????");
    printf("\n\t                                                            ");
    printf("\n\t?????????????????????????????????????????");
    printf("\n\t                                                            ");
    printf("\n\t?§ºM???????M????????????????????????? ?M");
    printf("\n\t                                                            ");
    printf("\n\t*?M???_???????????M?????????? ?????????");
    printf("\n\t                                                            ");
    printf("\n\t??§»?§»?§»? ????????????? ???????????????");
    printf("\n\t                                                            ");
    printf("\n\t?????????W?i?i?i?i?i?i?i?i????? ?M?? ????????????\\");
    printf("\n\t                                                            ");
    printf("\n\t?????????d?p?p?p?p?p?p?p?p???????????? ?? ?? / /");
}

void Horse(void)
{
    printf("\n\t                               _(\_/) ");
    printf("\n\t                             ,((((^`\\");
    printf("\n\t                             ((((  (6 \ ");
    printf("\n\t                          ,((((( ,    \\");
    printf("\n\t       ,,,_              ,(((((  / ._  ,`,");
    printf("\n\t      ((((\\ ,...       ,((((   /    `-.-'");
    printf("\n\t      )))  ;'    `''????((((   (      ");
    printf("\n\t    (((  /            (((      \\");
    printf("\n\t      )) |                      |");
    printf("\n\t     ((  |        .       '     |");
    printf("\n\t     ))  \     _ '      `t   ,.')");
    printf("\n\t     (   |   y;- -,-''''-.\   \/  ");
    printf("\n\t    )   / ./  ) /         `\  \\");
    printf("\n\t        |./   ( (           / /'");
    printf("\n\t        ||     \\          //'|");
    printf("\n\t        ||      \\       _//'||");
    printf("\n\t        ||       ))     |_/ ||");
    printf("\n\t        \\_\\     |_/         ||");
    printf("\n\t        `''                 \\_\\");
    printf("\n\t                            `' '");
}

void Bird(void)
{
    printf("\n\t              .=''=.");
    printf("\n\t             / _  _ \\");
    printf("\n\t            |  d  b  |");
    printf("\n\t            \\   /\\   /");
    printf("\n\t          ,/??-=\\/=-??\\,");
    printf("\n\t          / /        \\ \\");
    printf("\n\t         | /          \\ |");
    printf("\n\t         \\/ \\        / \\/");
    printf("\n\t             ??.    .??");
    printf("\n\t             _|`~~`|_");
    printf("\n\t             /|\\  /|\\");
}

void Mouse(void)
{
    printf("\n\t        ,-.,-.  ");
    printf("\n\t        (  (  (        ");
    printf("\n\t         \\  )  ) _..-.._   ");
    printf("\n\t        __)/ ,??,??       `.");
    printf("\n\t      ,'     `.     ,--.  `.   ");
    printf("\n\t    ,'   @        .??    `   \\");
    printf("\n\t   (Y            (           ;????.");
    printf("\n\t    `--.____,     \\          ,  ; ");
    printf("\n\t    ((_ ,----?? ,---??      _,??_,?? ");
    printf("\n\t        (((_,- (((______,-??");
}
