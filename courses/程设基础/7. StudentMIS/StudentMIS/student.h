//头文件避免重复包含
#ifndef _STUDENT_H_
#define _STUDENT_H_

void apart_dornum(char*, char*, char*, char*);

#define STUDENT 50
#define STUNO_LENTH 8
#define NAME_MAXLEN 8
#define GENDER_LENTH 6
#define PHONE_LENTH 11
#define WECHAT_LENTH 5
#define ROOMNUMBER_LENTH 4
#define DOR_LENTH 8

struct dormitory
{
    char *building_number;
    char *floor_number;
    char *room_number;
    char *dormitory_number;
};

struct student
{
    char *stuno;
    char *name;
    char *gender;
    char *phone;
    char *wechat;
    struct dormitory *dor;
    double score;
    struct student *prev;
    struct student *next;
};

void apart_dornum(char *d, char *b, char *f, char *r)
{
    char p[ROOMNUMBER_LENTH];
    char ch[2] = {'0', '\0'};

    ch[0] = *(d + 0);
    strcpy(b,ch);
    ch[0] = *(d + 2);
    strcpy(f,ch);

    for (int i = 4; i < DOR_LENTH; i++) {
        p[i - 4] = *(d + i);
    }

    strcpy(r,p);
}

struct student *stu;
int count = 0;
int num_male = 0;
int num_female = 0;

#endif

