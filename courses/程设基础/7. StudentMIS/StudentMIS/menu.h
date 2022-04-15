//头文件避免重复包含
#ifndef _MENU_H_ //if not define
#define _MENU_H_

void Menu(void);

#define WIDTH 70
#define MIDDLE 40
#define LEFT 5
#define SPACE ' '
#define SIGN '*'

void Menu(void)
{
    //int spaces;
    //int middle;

    char * top = "THE MENU";
    char * start = "Students MIS";
    char * end = "CopyRight@JIANG YAONAN<姜曜楠> HDU";
    char * choice1 = "1-Load Data";
    char * choice2 = "2-Show All Students";
    char * choice3 = "3-Search Student";
    char * choice4 = "4-Add Student";
    char * choice5 = "5-Modify Student";
    char * choice6 = "6-Delete Student";
    char * choice7 = "7-Sort by StuNo";
    char * choice8 = "8-Sort by Name";
    char * choice9 = "9-Sort by Gender";
    char * choice10 = "10-Sort by Phone";
    char * choice11 = "11-Sort by WeChat";
    char * choice12 = "12-Sort by Dormitory";
    char * choice13 = "13-Sort by Score";
    char * choice14 = "14-Statistics Data";
    char * choice15 = "15-Clear Data";
    char * choice16 = "16-Save Data To File";
    char * choice17 = "17-Show Selected Data";
    char * choice18 = "18-Exit";

    top_line('=', top);
    printf("\n\n");

    top_line('*', start);

    printf("\n\t%c",SIGN);
    show_n_char(SPACE,WIDTH);
    printf("%c",SIGN);

    every_line('$',choice1,choice2);
    every_line('$',choice3,choice4);
    every_line('$',choice5,choice6);
    every_line('$',choice7,choice8);
    every_line('$',choice9,choice10);
    every_line('$',choice11,choice12);
    every_line('$',choice13,choice14);
    every_line('$',choice15,choice16);
    every_line('$',choice17,choice18);

    printf("\n\t%c",SIGN);
    show_n_char(SPACE,WIDTH);
    printf("%c",SIGN);
    printf("\n\t%c",SIGN);
    show_n_char(SPACE,WIDTH);
    printf("%c",SIGN);

    top_line('*', end);
}

void top_line(char ch,char * pch)//头尾行输出
{
    int m,i;

    m = (WIDTH - strlen(pch)) / 2;

    printf("\n\t%c",ch);
    show_n_char(ch,m);            //printf("%s", pch);
    for(i = 0; i < strlen(pch); i++){
        printf("%c",*(pch + i));
    }
    show_n_char(ch,WIDTH + 1 - strlen(pch) - m);
}

void every_line(char ch, char * left, char * right)//控制每行的left和right分别对齐
{
    /* 较大型时采用隔行效果 */
    printf("\n\t%c", ch);
    show_n_char(SPACE,WIDTH);
    printf("%c", ch);

    int middle,spaces;
    printf("\n\t%c",ch);
    middle = MIDDLE - strlen(left) - LEFT;
    spaces = WIDTH - strlen(left) - strlen(right)- LEFT - middle;
    show_n_char(SPACE,LEFT);
    printf("%s",left);
    show_n_char(SPACE,middle);
    printf("%s",right);
    show_n_char(SPACE,spaces);
    printf("%c", ch);
}

void show_n_char(char ch,int num)//输出num个ch字符
{
    int count;

    for(count = 1; count <= num; count++){
        putchar(ch);
    }
}

#endif

