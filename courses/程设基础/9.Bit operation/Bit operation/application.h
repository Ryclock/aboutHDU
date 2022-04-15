void printfBinary(void);
void C_E_devision(void);
void encryption(void);
void decrypt(void);

void printfBinary(void)
{
    int x, y;
    int cnt = 0;

    x = getinteger();
    y = sizeof(int) * 8;

    for (int i = y - 1; i >= 0; i--) {
        printf("%d", (x >> i) & 1);

        if(0 == (i % 8)){
            printf(" ");
        }
    }

    while(x){
        x = (x - 1) & x;

        cnt++;
    }
    printf("\nThe number of '1' is %d", cnt);
}

void C_E_devision(void)
{
    char *str;
    int j;

    puts("Input 'E' to Renturn Menu");
    do{
        str = (char*) malloc(sizeof(char) * 1024);

        printf("\nPlease input a string:");
        fflush(stdin);
        gets(str);

        j = sizeof(char) * 1024;

        // Chinese
        printf("\nThe Chinese part is: ");
        for (int i = 0; str[i] != '\0'; i++) {

            if( str[i] & 0x80 ){
                printf("%c%c", str[i], str[i + 1]);
                i += 1;
            }
        }

        // English
        printf("\nThe English part is: ");
        for (int i = 0; str[i] != '\0'; i++) {

            if( !(str[i] & 0x80) ){
                printf("%c", str[i]);
            }
        }

        free(str);
    }while( !(getchar() == 'E') );
}

// �����������ֽڣ�
// ��str[0] �����һ���ֵ���߲��֣�
//   str[1]�����һ���ֵ��ұ߲���
void encryption(void)
{
    /* һ�ؼ��� */

    int a;
    int key;

    puts("\nNow input 'key'");
    key = getinteger();
    puts("\nNow input 'a'");
    a = getinteger();

    printf("The result is %d", a ^ key);

}

void decrypt(void)
{
    /* һ�ؽ��� */

    int a;
    int key;

    puts("\nNow input 'key'");
    key = getinteger();
    puts("\nNow input 'a'");
    a = getinteger();

    printf("The result is %d", a ^ key);

}

