//头文件避免重复包含
#ifndef _ADD_H_
#define _ADD_H_

void add(void);

void add(void)
{
    puts("NOTICE: Input 000 to Return to the Menu.");

    char ch;

    printf("\n\tInput student No.:");
    scanf("%s",stu[count].stuno);
    if(!strcmp(stu[count].stuno,"000")){
        main();
    }
    printf("\n\tInput student Name:");
    scanf("%s",stu[count].name);
    printf("\n\tInput student Gender<M/F>:");
    fflush(stdin);
    scanf("%c", &ch);
    switch(ch)
    {
        case 'F':
            strcpy(stu[count].gender, "Female");
            break;
        case 'M':
            strcpy(stu[count].gender, "Male");
            break;
    }
    printf("\n\tInput student Phone:");
    scanf("%s",stu[count].phone);
    printf("\n\tInput student WeChat:");
    scanf("%s",stu[count].wechat);
    printf("\n\tInput student Dormitory:");
    scanf("%s",stu[count].dor ->dormitory_number);
    apart_dornum(stu[count].dor ->dormitory_number,
            stu[count].dor ->building_number,
            stu[count].dor ->floor_number,
            stu[count].dor ->room_number);
    printf("\n\tInput student Score:");
    scanf("%lf",&(stu[count].score));

    stu[count - 1].next = (stu + count);
    stu[count].prev = (stu + count - 1);
    stu[count].next = NULL;

    puts("\n\tA student has been added.");
    show('x',count);
    count++;

    system("pause");
    main();
}

#endif


