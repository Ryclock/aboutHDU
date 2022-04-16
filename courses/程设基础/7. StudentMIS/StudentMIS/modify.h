//头文件避免重复包含
#ifndef _MODIFY_H_
#define _MODIFY_H_

void mod(void);
int mod1(int, int a[]);
int mod2(int, int a[]);
void mod3(int, int);
int judge(char*, int);

void mod(void)
{
    puts("NOTICE: Input 000 to Return to the Menu.");
    puts("\nTo modify students, we need to find them first.");
    printf("Please input information of the students to be changed:");

    int num[STUDENT] = {0};
    int t = 0;

    t = mod1(t, num);

    int p;
    p = mod2(t,num);

    int dcount, k;
    dcount = t;

    if(-1 == p){
        for (p = num[dcount - 1];dcount > 0; dcount--) {
            k = t - dcount + 1;
            mod3(p,k);
        }
        if(1 == k){
            puts("Finished! There only one.");
        }
    }
    else{
        mod3(p,0);
    }

    system("pause");
    main();
}

int mod1(int t, int num[])
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
        t = mod1(t, num);
    }

    return t;
}

int mod2(int t, int num[])
{
    printf("\nPress ENTER to modify all or input the StudentNo.:");
    char *need2;
    need2 = (char *)malloc(sizeof(char) * STUNO_LENTH);

    char ch;
    int p = -1;

    fflush(stdin);
    gets(need2);
    if(need2[0] == '\0'){
        printf("\nYou are going to change all the above students.");
    }
    else{
        printf("\nYou are going to change the student whose StuNo"
               " is %s",need2);

        while(t > 0){
            if(!strcmp(need2,stu[num[t - 1]].stuno)){
                p = num[t - 1];
                break;
            }
            t--;
        }
        if(-1 == p){
            printf("\n\nSorry! There is no student with StuNo %s",
                   need2);
            puts("\nPlease input again!");
            p = mod2(t,num);
        }
    }

    return p;
}

void mod3(int p, int k)
{
    char *need,ch;

    if(k != 0){
        printf("\nNow please input the information to change 第%d个 "
         "student's.If make no change, press the ENTER key.",
         k);

    }

    need = (char *)malloc(sizeof(char) * STUNO_LENTH);
    printf("\n\nInput a new student No.:");
    fflush(stdin);
    gets(need);
    if(need[0] != '\0'){
        if(!judge(need, p)){
            strncpy(stu[p].stuno, need,STUNO_LENTH);
        }
        else{
            puts("Please put again!");
            fflush(stdin);
            gets(need);
            if(need[0] != '\0'){
                if(!judge(need, p)){
                    strncpy(stu[p].stuno, need,STUNO_LENTH);
                }
            else{
                puts("It's still wrong. Now quit modifying!");
                system("pause");
                main();
            }
            }
        }
    }
    free(need);

    need = (char *)malloc(sizeof(char) * NAME_MAXLEN);
    printf("\n\nInput student Name:");
    fflush(stdin);
    gets(need);
    if(need[0] != '\0'){
        strncpy(stu[p].name, need,NAME_MAXLEN);
    }
    free(need);

    printf("\n\nInput student Gender<M/F>:");
    fflush(stdin);
    if((ch = getchar()) != '\n'){
        if('F' == ch){
            strncpy(stu[p].gender, "Female",6);
        }
        else if('M' == ch){
            strncpy(stu[p].gender, "Male",6);
        }
    }


    need = (char *)malloc(sizeof(char) * PHONE_LENTH);
    printf("\n\nInput student Phone:");
    fflush(stdin);
    gets(need);
    if(need[0] != '\0'){
        strncpy(stu[p].phone, need,PHONE_LENTH);
    }
    free(need);

    need = (char *)malloc(sizeof(char) * WECHAT_LENTH);
    printf("\n\nInput student Wechat:");
    fflush(stdin);
    gets(need);
    if(need[0] != '\0'){
        strncpy(stu[p].wechat, need,WECHAT_LENTH);
    }
    free(need);

    need = (char *)malloc(sizeof(char) * DOR_LENTH);
    printf("\n\nInput student Domitory:");
    fflush(stdin);
    gets(need);
    if(need[0] != '\0'){
        strncpy(stu[p].dor ->dormitory_number, need,DOR_LENTH);
        apart_dornum(stu[p].dor ->dormitory_number,
            stu[p].dor ->building_number,
            stu[p].dor ->floor_number,
            stu[p].dor ->room_number);
    }
    free(need);

    need = (char *)malloc(sizeof(char) * 4);
    printf("\n\nInput student Score:");
    fflush(stdin);
    gets(need);
    if(need[0] != '\0'){
        stu[p].score = (double)atoi(need);
    }
    free(need);

    if(k != 0){
        printf("\nThis is the end after changing 第%d个 "
               "students's information",k);
    }

    show('x',p);
}

int judge(char* judge, int p)
{
    for (int i = 0; i < count; i++) {
        if(i != p && !strcmp(judge,stu[i].stuno)){
            printf("\n Repeat!");
            return 1;
        }
    }

    return 0;
}

#endif


