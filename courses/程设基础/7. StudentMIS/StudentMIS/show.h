//头文件避免重复包含
#ifndef _SHOW_H_
#define _SHOW_H_

void show(char,int);
void show_top(void);
void show_sel(void);

void show_top(void)
{
    printf("\n%-10s %-12s %-10s %-11s %-10s %-10s %s",
            "StuNo", "Name", "Gender", "Phone", "Wechat",
           "Dormitory", "Score");
}

void show(char cmd, int cmdnum)
{
    struct student *k = (stu + 0);
    switch (cmd)
    {
        case 'R':
            while(k ->prev != NULL){
                k = (k + 1);
            }
            while(k != NULL){
                printf("\n%-10s %-12s %-8s %-13s %-10s %-10s %.2lf",
                k ->stuno, k ->name, k ->gender, k ->phone,
                k ->wechat, k ->dor ->dormitory_number, k ->score);
                k = k ->next;
            }
            break;

        case 'x' :
            k = (stu + cmdnum);
            printf("\n%-10s %-12s %-8s %-13s %-10s %-10s %.2lf",
            k ->stuno, k ->name,  k ->gender, k ->phone,
            k ->wechat, k ->dor ->dormitory_number, k ->score);
            break;

        default : break;
    }

    puts("");
}

void show_sel(void)
{
    int hide[7] = {0};  //hide 数组内元素 1 代表隐藏，0代表显示
                        //表示顺序依次为 "StuNo", "Name", "Gender",
                        // "Phone", "Wechat","Dormitory", "Score"

/* 选择是否隐藏 */
    puts("Press ENTER to SHOW the data field, others to HIDE it:");

    char ch;

    printf("\n\tShow or Hide the Student Number:");
    fflush(stdin);
    if((ch = getchar()) != '\n'){
        hide[0] = 1;
    }

    printf("\n\tShow or Hide the Name:");
    fflush(stdin);
    if((ch = getchar()) != '\n'){
        hide[1] = 1;
    }

    printf("\n\tShow or Hide the Gender:");
    fflush(stdin);
    if((ch = getchar()) != '\n'){
        hide[2] = 1;
    }

    printf("\n\tShow or Hide the Phone:");
    fflush(stdin);
    if((ch = getchar()) != '\n'){
        hide[3] = 1;
    }

    printf("\n\tShow or Hide the Wechat:");
    fflush(stdin);
    if((ch = getchar()) != '\n'){
        hide[4] = 1;
    }

    printf("\n\tShow or Hide the Dormitory:");
    fflush(stdin);
    if((ch = getchar()) != '\n'){
        hide[5] = 1;
    }

    printf("\n\tShow or Hide the Score:");
    fflush(stdin);
    if((ch = getchar()) != '\n'){
        hide[6] = 1;
    }

/* 输出隐藏后的状态 */
    for (int i = 0; i < count; i++) {
        puts("");
        if(!hide[0]){
            printf("%-10s ",(stu + i) ->stuno);
        }
        if(!hide[1]){
            printf("%-12s ",(stu + i) ->name);
        }
        if(!hide[2]){
            printf("%-8s ",(stu + i) ->gender);
        }
        if(!hide[3]){
            printf("%-13s ",(stu + i) ->phone);
        }
        if(!hide[4]){
            printf("%-10s ",(stu + i) ->wechat);
        }
        if(!hide[5]){
            printf("%-10s ",(stu + i) ->dor ->dormitory_number);
        }
        if(!hide[6]){
            printf("%.2lf",(stu + i) ->score);
        }
    }

    puts("");
    system("pause");
    main();
}

#endif


