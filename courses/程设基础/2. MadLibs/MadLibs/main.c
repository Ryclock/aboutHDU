/* Madlibs.c -- C Project 2 - MadLibs: Story Maker */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>

/*
 * Copyright(C)
 * All rights reserved.
 * Author : JIANG YAONAN<姜曜楠> 2102115 <学号> HDU
 * Date : 2021-11-22-11.50.57
 * Description : Mad Libs is a fun party game. The object of
 the game is to produce a humorous story by using word
 substitutions. Word descriptions are followed by blank
 spaces. Players fill in these blank spaces with words that
 match the descriptions. Most word descriptions are simple
 parts of speech, like "noun", "verb", "adjective", etc.
 When complete the story will be funny, crazy, ridiculous or
 just plain dumb. You can never tell till the story is read
 back. Nevertheless, it's FUN! */

#define WIDTH 40
#define MIDDLE 25
#define LEFT 5
#define SPACE ' '
#define SIGN '$'

void Menu(void);
void top_line(char ch, char  * pch);
void every_line(char * left, char * right);
void show_n_char(char ch,int num);
void MadBoy(void);
void MadPanda(void);
void MadCrime(void);
void MadDay(void);
void MadCrime(void);

void main(void)
{
    int choice;

    Menu();
    printf("\n\tPlease choose one number : ");
    fflush(stdin);
    scanf("%d",&choice);
    printf("\n");

    switch(choice)
    {
        case 1: MadBoy();break;
        case 2: MadPanda();break;
        case 3: MadCrime();break;
        case 4: MadDay();break;
        case 5: MadLife();break;
        case 6: return 0;
        default: {printf("\n"),printf("Wrong! Please choose another true number!!\n"),printf("\n"),main();};
    }

    return 0;
}

void Menu(void)
{
    int spaces;
    int middle;

    char * top = "THE MENU";
    char * start = "Mad Lib Games";
    char * end = "CopyRight@JIANG YAONAN<姜曜楠> HDU";
    char * choice1 = "1.MadBoy";
    char * choice2 = "2.MadPanda";
    char * choice3 = "3.MadCrime";
    char * choice4 = "4.MadDay";
    char * choice5 = "5.MadLife";
    char * choice6 = "6.Exit";

    top_line('=', top);
    printf("\n\n");

    top_line('*', start);

    printf("\n\t%c",SIGN);
    show_n_char(SPACE,WIDTH);
    printf("%c",SIGN);
    printf("\n\t%c",SIGN);
    show_n_char(SPACE,WIDTH);
    printf("%c",SIGN);

    every_line(choice1,choice2);
    every_line(choice3,choice4);
    every_line(choice5,choice6);

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
    show_n_char(ch,m);
    //printf("%s", pch);
    for(i = 0; i < strlen(pch); i++){
        printf("%c",*(pch + i));
    }
    show_n_char(ch,WIDTH + 1 - strlen(pch) - m);
}

void every_line(char * left, char * right)//控制每行的left和right分别对齐
{
    int middle,spaces;

    printf("\n\t");
    middle = MIDDLE - strlen(left) - LEFT;
    spaces = WIDTH - strlen(left) - strlen(right)- LEFT - middle;
    putchar(SIGN);
    show_n_char(SPACE,LEFT);
    printf("%s",left);
    show_n_char(SPACE,middle);
    printf("%s",right);
    show_n_char(SPACE,spaces);
    putchar(SIGN);

}

void show_n_char(char ch,int num)//输出num个ch字符
{
    int count;

    for(count = 1; count <= num; count++){
        putchar(ch);
    }
}

void MadBoy(void)
{
    char * girl_name;
    char * boy_name;
    char * body_part;
    char * vehicle;
    char * place;
    char * food;
    char * action;
    char * animal;

    girl_name = (char *)malloc(sizeof(char) * 20);
    boy_name = (char *)malloc(sizeof(char) * 20);
    body_part = (char *)malloc(sizeof(char) * 20);
    vehicle = (char *)malloc(sizeof(char) * 20);
    place = (char *)malloc(sizeof(char) * 20);
    food = (char *)malloc(sizeof(char) * 20);
    action = (char *)malloc(sizeof(char) * 20);
    animal = (char *)malloc(sizeof(char) * 20);

    int i;
    char ch1;

    printf("\n\tInput a girl's name: ");
    fflush(stdin);
    scanf("%s", girl_name);
    printf("\tInput a boy's name: ");
    fflush(stdin);
    scanf("%s", boy_name);
    printf("\tInput a body part: ");
    fflush(stdin);
    scanf("%s", body_part);
    printf("\tInput a vehicle: ");
    fflush(stdin);
    scanf("%s", vehicle);
    printf("\tInput a place: ");
    fflush(stdin);
    scanf("%s", place);
    printf("\tInput a food: ");
    fflush(stdin);
    scanf("%s", food);
    printf("\tSomething you can do with your mouth: ");
    fflush(stdin);
    scanf("%s", action);
    printf("\tInput an animal: ");
    fflush(stdin);
    scanf("%s", animal);


    printf("\n\tThe story is:");
    printf("\n\t%s went to %s and grabbed his %s.",
           girl_name,boy_name,body_part);
    printf("\n\t\"Come on\",she said,\"We have to take the "
           "%s to the %s",vehicle,place);
    printf("\n\tas quickly as possible where we can eat "
           "lots of %s!\"",food);
    printf("\n\t\"I hate %s\",he said,\"I would much rather"
           " %s %s poop!",food,action,animal);
    printf("\n\n\tPress Q to Exit the program, "
           "others to the Menu:");

    fflush(stdin);
    if((ch1 = getchar()) != 'Q'){
        main();
    }
}

void MadPanda(void)
{
    char * adjective;
    char * plural_animal;
    char * plural_food;
    char * verb;
    char * single_animal;

    adjective = (char *)malloc(sizeof(char) * 20);
    plural_animal = (char *)malloc(sizeof(char) * 20);
    plural_food = (char *)malloc(sizeof(char) * 20);
    verb = (char *)malloc(sizeof(char) * 20);
    single_animal = (char *)malloc(sizeof(char) * 20);

    int i;
    char ch1;

    printf("\n\tEnter an adjective: ");
    fflush(stdin);
    scanf("%s", adjective);
    printf("\n\tEnter a plural animal: ");
    fflush(stdin);
    scanf("%s", plural_animal);
    printf("\n\tEnter a plural food: ");
    fflush(stdin);
    scanf("%s", plural_food);
    printf("\n\tEnter a verb: ");
    fflush(stdin);
    scanf("%s", verb);
    printf("\n\tEnter a single animal: ");
    fflush(stdin);
    scanf("%s", single_animal);

    printf("\n\tThe story is:");
    printf("\n\tThree %s %s jump to the %s and then %s.",
           adjective,plural_animal,plural_food,verb);
    printf("\n\tA nearby %s is unaffected by these events.",
           single_animal);
    printf("\n\n\tPress Q to Exit the program, "
           "others to the Menu:");

    fflush(stdin);
    if((ch1 = getchar()) != 'Q'){
        main();
    }
}

void MadCrime(void)
{
    char * number;
    char * plural_object;
    char * place;
    char * body_part;
    char * verb_ing;
    char * distance;
    char * body_part2;

    number = (char *)malloc(sizeof(char) * 20);
    plural_object = (char *)malloc(sizeof(char) * 20);
    place = (char *)malloc(sizeof(char) * 20);
    body_part = (char *)malloc(sizeof(char) * 20);
    verb_ing = (char *)malloc(sizeof(char) * 20);
    distance = (char *)malloc(sizeof(char) * 20);
    body_part2 = (char *)malloc(sizeof(char) * 20);

    int i;
    char ch1;

    printf("\n\tGive me a number: ");
    fflush(stdin);
    scanf("%s", number);
    printf("\n\tGive me a plural object: ");
    fflush(stdin);
    scanf("%s", plural_object);
    printf("\n\tGive me a place: ");
    fflush(stdin);
    scanf("%s", place);
    printf("\n\tGive me a body part: ");
    fflush(stdin);
    scanf("%s", body_part);
    printf("\n\tGive me a verb ending in ing: ");
    fflush(stdin);
    scanf("%s", verb_ing);
    printf("\n\tGive me a distance: ");
    fflush(stdin);
    scanf("%s", distance);
    printf("\n\tGive me a body part: ");
    fflush(stdin);
    scanf("%s", body_part2);

    printf("\n\tThe story is:");
    printf("\n\tThere was a second degree robbery.");
    printf("\n\t%s %s were stolen from %s.",
           number,plural_object,place);
    printf("\n\tThe crime scene has your %s printfed"
           " all over it",body_part);
    printf("\n\tA camera showed you were %s %s away from the"
           "crime scene",verb_ing,distance);
    printf("\n\tYou need the money to implant your %s",
           body_part2);
    printf("\n\n\tPress Q to Exit the program, "
           "others to the Menu:");

    fflush(stdin);
    if((ch1 = getchar()) != 'Q'){
        main();
    }
}

void MadDay(void)
{
    char * name;
    char * sentence;
    char * place;
    char * name2;
    char * something;

    name = (char *)malloc(sizeof(char) * 20);
    sentence = (char *)malloc(sizeof(char) * 20);
    place = (char *)malloc(sizeof(char) * 20);
    name2 = (char *)malloc(sizeof(char) * 20);
    something = (char *)malloc(sizeof(char) * 20);

    int i;
    char ch1;

    printf("\n\t请输入一个名字: ");
    fflush(stdin);
    scanf("%s", name);
    printf("\n\t请输入一个句子: ");
    fflush(stdin);
    scanf("%s", sentence);
    printf("\n\t请输入一个地点: ");
    fflush(stdin);
    scanf("%s", place);
    printf("\n\t请输入一个名字: ");
    fflush(stdin);
    scanf("%s", name2);
    printf("\n\t请输入一个物品: ");
    fflush(stdin);
    scanf("%s", something);


    printf("\n\t故事是：");
    printf("\n\t阳光明媚的一个上午，%s兴奋地大喊一声：%s，",
           name,sentence);
    printf("\n\t然后心满意足地跑去%s，捡到了%s的%s，",
           place,name2,something);
    printf("\n\t于是他开心得像个孩子一样!");
    printf("\n\n\tPress Q to Exit the program, "
           "others to the Menu:");

    fflush(stdin);
    if((ch1 = getchar()) != 'Q'){
        main();
    }
}

void MadLife(void)
{
    char * something;
    char * noun;
    char * body_about;

    something = (char *)malloc(sizeof(char) * 20);
    noun = (char *)malloc(sizeof(char) * 20);
    body_about = (char *)malloc(sizeof(char) * 20);

    int i;
    char ch1;

    printf("\n\t请输入一个物品: ");
    fflush(stdin);
    scanf("%s", something);
    printf("\n\t请输入一个名词: ");
    fflush(stdin);
    scanf("%s", noun);
    printf("\n\t请输入一个身上的东西或部位: ");
    fflush(stdin);
    scanf("%s", body_about);

    printf("\n\t故事是：");
    printf("\n\t人生就像一张白纸，可我的白纸上却画满了%s",
           something);
    printf("\n\t给我%s，我就能睡上一千年。",noun);
    printf("\n\t我曾经和一个人无数次擦肩而过，%s都擦破了，"
           "也没擦出火花。",body_about);
    printf("\n\n\tPress Q to Exit the program, "
           "others to the Menu:");

    fflush(stdin);
    if((ch1 = getchar()) != 'Q'){
        main();
    }
}

