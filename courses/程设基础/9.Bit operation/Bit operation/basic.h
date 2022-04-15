void bit_and(void);
void bit_or(void);
void bit_not_or(void);
void bit_not(void);
void bit_left(void);
void bit_right(void);

void bit_and()
{
    int a, b;

    puts("Now input 'a'");
    a = getinteger();
    puts("Now input 'b'");
    b = getinteger();

    printf("The result is %d", (a & b));

}

void bit_or()
{
    int a, b;

    puts("Now input 'a'");
    a = getinteger();
    puts("Now input 'b'");
    b = getinteger();

    printf("The result is %d", (a | b));

}

void bit_not_or()
{
    int a, b;

    puts("Now input 'a'");
    a = getinteger();
    puts("Now input 'b'");
    b = getinteger();

    printf("The result is %d", (a ^ b));

}

void bit_not()
{
    int a;

    a = getinteger();

    puts("////~n = ~ (n + 1)");
    printf("The result is %d", (~a));

}

void bit_left()
{
    int a;

    a = getinteger();

    puts("\nInput 'E' to Return Menu!!!");
    for (int i = 1; ( 'E' == getchar() ); i++) {
        printf("\nLeft = %d", a << i);

        system("pause");
    }

}

void bit_right()
{
    int a;

    a = getinteger();

    puts("\nInput 'E' to Return Menu!!!");
    for (int i = 1; ( 'E' == getchar() ); i++) {
        printf("\nRight = %d", a >> i);

        system("pause");
    }

}


