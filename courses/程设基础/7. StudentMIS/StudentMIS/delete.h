//头文件避免重复包含
#ifndef _DELETE_H_
#define _DELETE_H_

void del(void);
int del1(int, int a[]);
int del2(int, int a[]);
void del3(int t, int num[]);

void del(void)
{
    puts("NOTICE: Input 000 to Return to the Menu.");
    puts("\nTo delete students, we need to find them first.");
    puts("Please input information of the students to be deleted:");

    int num[STUDENT] = {0};
    int t = 0;

    t = del1(t, num);

    del2(t,num);

    system("pause");
    main();
}

int del1(int t, int num[])
{
    char *need1;
    need1 = (char *)malloc(sizeof(char) * PHONE_LENTH);
    scanf("%s", need1);

    if(!strcmp(need1,"000")){
        main();
    }
    for (int i = 0; i < count; i++) {
        if(!strcmp(need1,stu[i].stuno) ||
            !strcmp(need1,stu[i].name)||
            !strcmp(need1,stu[i].gender)||
            !strcmp(need1,stu[i].phone)||
            !strcmp(need1,stu[i].wechat) ||
            !strcmp(need1,stu[i].dor ->building_number) ||
            !strcmp(need1,stu[i].dor ->floor_number) |
            !strcmp(need1,stu[i].dor ->room_number) ||
            !strcmp(need1,stu[i].dor ->dormitory_number) ||
           (atoi(need1) == (int)stu[i].score) ) {
            if(0 == t){
                show_top();
            }
            show('x',i);
            num[t] = i;
            t++;
        }
    }
    printf("\nThere are %d students with \"%s\"", t,need1);
    if(0 == t){
        puts("\nPlease input again!");
        for (int i = 0; i < STUDENT; i++) {
            num[1] = 0;
        }
        t = 0;
        t = del1(t, num);
    }

    return t;
}

int del2(int t, int num[])
{
    printf("\nPress ENTER to delete all or input the StudentNo.:");
    char *need2;
    need2 = (char *)malloc(sizeof(char) * STUNO_LENTH);

    char ch;
    int p = -1;
    int t1 = t;

    fflush(stdin);
    if((ch = getchar()) == '\n'){
        puts("\nYou are going to delete all the above students.");
        del3(t1, num);
        printf("There are %d students deleted.",t1);
        count -= t1;
    }
    else{
        need2[0] = ch;
        scanf("%s", need2 + 1);
        printf("\nYou are going to delete the student whose StuNo"
               " is %s",need2);

        while(t1 > 0){
            if(!strcmp(need2,stu[num[t1 - 1]].stuno)){
                p = num[t1 - 1];
                break;
            }
            t1--;
        }
        if(-1 == p){
            printf("\n\nSorry! There is no student with StuNo %s",
                   need2);
            puts("\nPlease input again!");
            p = del2(t,num);
        }
        else{
            del3(t1 - 1,num);
            puts("\nThere are 1 students deleted.");
            count--;
        }
    }

    return p;
}

void del3(int t, int num[])
{
    while (t >= 0) {
        if(0 != num[t]){
            stu[num[t] - 1].next = stu[num[t]].next;
            stu[num[t]].next = (struct student *)malloc(sizeof(struct student));
        }
        if(STUDENT - 1 != num[t]){
            stu[num[t] + 1].prev = stu[num[t]].prev;
            stu[num[t]].prev = (struct student *)malloc(sizeof(struct student));
        }

        stu[num[t]].stuno = (char *)malloc(STUNO_LENTH * sizeof(char));
        stu[num[t]].name = (char *)malloc(NAME_MAXLEN * sizeof(char));
        stu[num[t]].gender = (char *)malloc(GENDER_LENTH * sizeof(char));
        stu[num[t]].phone = (char *)malloc(PHONE_LENTH * sizeof(char));
        stu[num[t]].wechat = (char *)malloc(WECHAT_LENTH * sizeof(char));
        stu[num[t]].dor = (struct dormitory *)malloc(sizeof(struct dormitory));
        stu[num[t]].dor ->building_number = (char *)malloc(sizeof(char));
        stu[num[t]].dor ->floor_number = (char *)malloc(sizeof(char));
        stu[num[t]].dor ->room_number = (char *)malloc(ROOMNUMBER_LENTH * sizeof(char));
        stu[num[t]].dor ->dormitory_number = (char *)malloc(DOR_LENTH * sizeof(char));
        stu[num[t]].score = -1;
        stu[num[t]].prev = (struct student *)malloc(sizeof(struct student));
        stu[num[t]].next = (struct student *)malloc(sizeof(struct student));

        t--;
    }
}

#endif


