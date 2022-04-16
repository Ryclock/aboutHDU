//头文件避免重复包含
#ifndef _OTHERS_H_
#define _OTHERS_H_

void load(void);
void sear(void);
void statis(void);
void clear(void);
void save(void);

void load(void)
{
    stu = (struct student *)malloc(STUDENT * sizeof(struct student));

    for (int i = 0; i < STUDENT; i++) {
        (stu + i) ->stuno = (char *)malloc(STUNO_LENTH * sizeof(char));
        (stu + i) ->name = (char *)malloc(NAME_MAXLEN * sizeof(char));
        (stu + i) ->gender = (char *)malloc(GENDER_LENTH * sizeof(char));
        (stu + i) ->phone = (char *)malloc(PHONE_LENTH * sizeof(char));
        (stu + i) ->wechat = (char *)malloc(WECHAT_LENTH * sizeof(char));
        (stu + i) ->dor = (struct dormitory *)malloc(sizeof(struct dormitory));
        (stu + i) ->dor ->building_number = (char *)malloc(sizeof(char));
        (stu + i) ->dor ->floor_number = (char *)malloc(sizeof(char));
        (stu + i) ->dor ->room_number = (char *)malloc(ROOMNUMBER_LENTH * sizeof(char));
        (stu + i) ->dor ->dormitory_number = (char *)malloc(DOR_LENTH * sizeof(char));
        (stu + i) ->prev = (struct student *)malloc(sizeof(struct student));
        (stu + i) ->next = (struct student *)malloc(sizeof(struct student));
    }
    puts("\nNotice: Input 000 to Return the Menu.");
    puts("\nPress ENTER to load default file<stu.txt>, or "
         "input a file name:\n");

    char filename[FILENAME_MAX];
    char *fp;
    char ch;

    fflush(stdin);
    if((ch = getchar()) == '\n'){
        strcpy(filename,"stu.txt");
    }
    else{
        filename[0] = ch;
        scanf("%s", filename + 1);
    }

    if(!strcmp(filename,"000")){
            main();
    }

    fp = fopen(filename,"r");
    if(fp != NULL){
        printf("\nFile %s opened success.",filename);
    }
    else{
        printf("\nFile %s Can't be opened!!!",filename);
        system("pause");
        main();
    }

    while( !feof(fp) ){
        if(0 == count){
            stu[count].prev = NULL;
        }
        else{
            stu[count].prev = (stu + count - 1);
        }
        fscanf(fp,"%s",stu[count].stuno);
        fscanf(fp,"%s",stu[count].name);
        fscanf(fp,"%s",stu[count].gender);
        fscanf(fp,"%s",stu[count].phone);
        fscanf(fp,"%s",stu[count].wechat);
        fscanf(fp,"%s",stu[count].dor ->dormitory_number);
        apart_dornum(stu[count].dor ->dormitory_number,
                stu[count].dor ->building_number,
                stu[count].dor ->floor_number,
                stu[count].dor ->room_number);
        if( fscanf(fp,"%lf",&(stu[count].score)) != 1){
            break;
        }

        count++;
    }

    for (int i = 0; i < count; i++) {
        if(count - 1 == i){
            stu[i].next = NULL;
        }
        else{
            stu[i].next = (stu + i + 1);
        }
    }
    printf("\n\nThere are %d students imported.\n", count);
    fclose(fp);

    system("pause");
    main();
}

void sear(void)
{
    puts("NOTICE: Input 000 to Return to the Menu.");

    char *need;
    need = (char *)malloc(sizeof(char) * PHONE_LENTH);

    printf("Please input information of the student:");
    scanf("%s", need);
    if(!strcmp(need,"000")){
        main();
    }

    int num[STUDENT] = {0};
    int t = 0;

    for (int i = 0; i < count; i++) {
        if(!strcmp(need,stu[i].stuno) ||
            !strcmp(need,stu[i].name)||
            !strcmp(need,stu[i].gender)||
            !strcmp(need,stu[i].phone)||
            !strcmp(need,stu[i].wechat) ||
            !strcmp(need,stu[i].dor ->building_number) ||
            !strcmp(need,stu[i].dor ->floor_number) ||
            !strcmp(need,stu[i].dor ->room_number) ||
            !strcmp(need,stu[i].dor ->dormitory_number) ||
           (atoi(need) == (int)stu[i].score) ) {
            if(0 == t){
                show_top();
            }
            show('x',i);
            num[t] = i;
            t++;
        }
    }
    printf("\nThere are %d students with \"%s\"", t,need);

    system("pause");
    main();
}

void statis(void)
{
    double max = stu[0].score;
    double min = stu[0].score;
    double sum = 0;
    int maxone = 0;
    int minone = 0;
    struct student *k = (stu + 0);

    while(k ->prev != NULL){
        k = (k + 1);
    }
    while(k != NULL){
        if(!strcmp(k ->gender, "Male")){
            num_male++;
        }
        else{
            num_female++;
        }

        sum += k ->score;
        if(k ->score > max){
            max = k ->score;
            maxone = k - stu;
        }
        if(k ->score < min){
            min = k ->score;
            minone = k - stu;
        }

        k = k ->next;
    }

    puts("\nThe statistics Data of the Students are as follows");

    printf("\n\t%8s: %d", "Students", count);
    printf("\n\t%8s: %d", "Male", num_male);
    printf("\n\t%8s: %d", "Female",num_female);

    printf("\n\t%8s: %.0f", "MaxScore", max);
    printf("\n\t%8s: %.0f", "MinScore", min);
    printf("\n\t%8s: %.2f", "AnyScore",sum / (double) count);

    puts("\n\nThe Information of the MaxScore Students is:\n");
    show_top();
    show('x',maxone);

    puts("\n\nThe Information of the MinScore Students is:\n");
    show_top();
    show('x',minone);

    system("pause");
    main();
}

void clear(void)
{
    for (int i = 0; i < count; i++) {
        free(stu[i].stuno);
        stu[i].stuno = NULL;
        free(stu[i].name);
        stu[i].name = NULL;
        free(stu[i].gender);
        stu[i].gender = NULL;
        free(stu[i].phone);
        stu[i].phone = NULL;
        free(stu[i].wechat);
        stu[i].wechat = NULL;
        free(stu[i].dor ->building_number);
        stu[i].dor ->building_number = NULL;
        free(stu[i].dor ->floor_number);
        stu[i].dor ->floor_number = NULL;
        free(stu[i].dor ->room_number);
        stu[i].dor ->room_number = NULL;
        free(stu[i].dor ->dormitory_number);
        stu[i].dor ->dormitory_number = NULL;
        stu[i].score = -1;
        stu[i].prev = stu[i].next = NULL;
    }
    free(stu);

    printf("\n\tAll the %d data has been cleared.",count);
    puts("");

    system("pause");
    main();
}

void save(void)
{
    puts("\nNotice: Input 000 to Return the Menu.");
    puts("\nPress ENTER to save data to stu_out.txt, or "
         "input a file name:\n");

    char filename[FILENAME_MAX];
    char *fp;
    char ch;

    fflush(stdin);
    if((ch = getchar()) == '\n'){
        strcpy(filename,"stu_out.txt");
    }
    else{
        filename[0] = ch;
        scanf("%s", filename + 1);
    }

    if(!strcmp(filename,"000")){
        main();
    }

    fp = fopen(filename,"w");
    if(fp != NULL){
        printf("\nFile %s opened success.",filename);
    }
    else{
        printf("\nFile %s Can't be opened!!!",filename);
        system("pause");
        main();
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp,"%s  ",stu[i].stuno);
        fprintf(fp,"%s  ",stu[i].name);
        fprintf(fp,"%s  ",stu[i].gender);
        fprintf(fp,"%s  ",stu[i].phone);
        fprintf(fp,"%s  ",stu[i].wechat);
        fprintf(fp,"%s  ",stu[i].dor ->dormitory_number);
        fprintf(fp,"%.2lf",stu[i].score);
        fputc('\n',fp);
    }
    printf("\n\nThere are %d students saved to file: %s\n", count,filename);
    fclose(fp);

    system("pause");
    main();
}

#endif

