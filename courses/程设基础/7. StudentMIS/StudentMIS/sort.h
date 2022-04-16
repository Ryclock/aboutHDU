//头文件避免重复包含
#ifndef _SORT_H_
#define _SORT_H_

void swap(void *, void *);
void sor_stuno(void);
void sor_name(void);
void sor_gen(void);
void sor_pho(void);
void sor_wec(void);
void sor_dor(void);
void sor_sco(void);

void swap(void *a, void *b)
{
    struct student *aa = (struct student*)a;
    struct student *bb = (struct student*)b;
    struct student temp = *aa;
    *aa = *bb;
    *bb = temp;
}

void sor_stuno(void)
{
    puts("To sort the students by their student Numbers.");
    puts("Press ENTER to the sort in ASC order, others in DESC"
         "order:");

    char ch;
    fflush(stdin);
    if((ch = getchar()) == '\n'){
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (strcmp(stu[j].stuno, stu[j + 1].stuno) > 0){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }
    else{
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (strcmp(stu[j].stuno, stu[j + 1].stuno) < 0){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }

    for (int i = 0; i < count; i++) {
        stu[i].prev = (stu + i - 1);
        stu[i].next = (stu + i + 1);

        if(0 == i){
            stu[i].prev = NULL;
        }
        else if(count - 1 == i){
            stu[i].next = NULL;
        }
    }

    system("pause");
    main();
}

void sor_name(void)
{
    puts("To sort the students by their names.");
    puts("Press ENTER to the sort in ASC order, others in DESC"
         "order:");

    char ch;
    fflush(stdin);
    if((ch = getchar()) == '\n'){
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (strcmp(stu[j].name, stu[j + 1].name) > 0){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }
    else{
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (strcmp(stu[j].name, stu[j + 1].name) < 0){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }

    for (int i = 0; i < count; i++) {
        stu[i].prev = (stu + i - 1);
        stu[i].next = (stu + i + 1);

        if(0 == i){
            stu[i].prev = NULL;
        }
        else if(count - 1 == i){
            stu[i].next = NULL;
        }
    }

    system("pause");
    main();
}

void sor_gen(void)
{
    puts("To sort the students by their Genders.");
    puts("Press ENTER to the sort in ASC order, others in DESC"
         "order:");

    char ch;
    fflush(stdin);
    if((ch = getchar()) == '\n'){
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (strcmp(stu[j].gender, stu[j + 1].gender) > 0){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }
    else{
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (strcmp(stu[j].gender, stu[j + 1].gender) < 0){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }

    for (int i = 0; i < count; i++) {
        stu[i].prev = (stu + i - 1);
        stu[i].next = (stu + i + 1);

        if(0 == i){
            stu[i].prev = NULL;
        }
        else if(count - 1 == i){
            stu[i].next = NULL;
        }
    }

    system("pause");
    main();
}

void sor_pho(void)
{
    puts("To sort the students by their Phones.");
    puts("Press ENTER to the sort in ASC order, others in DESC"
         "order:");

    char ch;
    fflush(stdin);
    if((ch = getchar()) == '\n'){
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (strcmp(stu[j].phone, stu[j + 1].phone) > 0){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }
    else{
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (strcmp(stu[j].phone, stu[j + 1].phone) < 0){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }

    for (int i = 0; i < count; i++) {
        stu[i].prev = (stu + i - 1);
        stu[i].next = (stu + i + 1);

        if(0 == i){
            stu[i].prev = NULL;
        }
        else if(count - 1 == i){
            stu[i].next = NULL;
        }
    }

    system("pause");
    main();
}

void sor_wec(void)
{
    puts("To sort the students by their Wechats.");
    puts("Press ENTER to the sort in ASC order, others in DESC"
         "order:");

    char ch;
    fflush(stdin);
    if((ch = getchar()) == '\n'){
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (strcmp(stu[j].wechat, stu[j + 1].wechat) > 0){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }
    else{
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (strcmp(stu[j].wechat, stu[j + 1].wechat) < 0){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }

    for (int i = 0; i < count; i++) {
        stu[i].prev = (stu + i - 1);
        stu[i].next = (stu + i + 1);

        if(0 == i){
            stu[i].prev = NULL;
        }
        else if(count - 1 == i){
            stu[i].next = NULL;
        }
    }

    system("pause");
    main();
}

void sor_dor(void)
{
    puts("To sort the students by their Dormitory.");
    puts("Press ENTER to the sort in ASC order, others in DESC"
         "order:");

    char ch;
    fflush(stdin);
    if((ch = getchar()) == '\n'){
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (strcmp(stu[j].dor ->dormitory_number,
                           stu[j + 1].dor ->dormitory_number) > 0){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }
    else{
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (strcmp(stu[j].dor ->dormitory_number,
                           stu[j + 1].dor ->dormitory_number) < 0){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }

    for (int i = 0; i < count; i++) {
        stu[i].prev = (stu + i - 1);
        stu[i].next = (stu + i + 1);

        if(0 == i){
            stu[i].prev = NULL;
        }
        else if(count - 1 == i){
            stu[i].next = NULL;
        }
    }

    system("pause");
    main();
}

void sor_sco(void)
{
    puts("To sort the students by their Scores.");
    puts("Press ENTER to the sort in ASC order, others in DESC"
         "order:");

    char ch;
    fflush(stdin);
    if((ch = getchar()) == '\n'){
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (stu[j].score > stu[j + 1].score){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }
    else{
        for (int i = 0; i < count - 1 ; i++) {
            for (int j = 0; j < count - 1 - i; j++){
                if (stu[j].score < stu[j + 1].score){
                    swap(&(stu[j]),&(stu[j + 1]));
                }
            }
        }
    }

    for (int i = 0; i < count; i++) {
        stu[i].prev = (stu + i - 1);
        stu[i].next = (stu + i + 1);

        if(0 == i){
            stu[i].prev = NULL;
        }
        else if(count - 1 == i){
            stu[i].next = NULL;
        }
    }

    system("pause");
    main();
}

#endif

