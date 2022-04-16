int getinteger(void);

int getinteger()
{
    int a;

    printf("Please input an integer:");
    while( !scanf("%d", &a) ){
        puts("NOT AN INTEGER!!");
        printf("Please input again:");

        fflush(stdin);
    }

    return a;
}

