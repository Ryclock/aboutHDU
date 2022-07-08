#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

typedef char *string;

void printNChar(char ch, int num);

void printNSpace(int num);

void printBodyOfOptionsLine(char *leftOption, char *rightOption);

void printBodyOfBlankLine(void);

void printBodyOfInfoLine(char ch, char *pch);

void printEndOfLine(char ch);

void printHeadOfLine(char ch);

void printOptionLine(char ch, char *leftOption, char *rightOption);

void printBlankLine(char ch);

void printInfoLine(char ch, char *pch);

void printMenuTail(char *tail);

void printMenuBody(string options[], int num);

void printMenuHead(char *top, char *head);

void printEnglishMenu(void);

void printChineseMenu(void);

void Menu(char lang);

int inputChoice(void);

void switchlanguage(char *pLanguage);

#endif
