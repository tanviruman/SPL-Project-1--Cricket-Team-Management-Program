# Cricket Team Management Program Documentation

## Introduction
This document provides a detailed explanation of the code that implements a cricket team management program in C. The program reads data about cricket players from a file, stores it in a structure, and allows the user to perform various operations such as displaying player information, identifying top performers, and more.

## Code Explanation

### Includes and Structures
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CricketTeam {
    char name[50];
    int age;
    char type[20];
    int totalmatch;
    int totalrun;
    int hightrun;
};
```
- Standard libraries are included for input/output operations, memory management, and string manipulation.
- A structure `CricketTeam` is defined to hold information about each player.

### Function Prototypes
```c
void PlayerInfermation(struct CricketTeam info[], int n);
void allinfo(struct CricketTeam info[], char name[50], int n);
int MostExperiencedPlayer(struct CricketTeam most[], int n);
void NewPlayer(struct CricketTeam info[], int n);
void topscore(struct CricketTeam info[], int n);
void hardhitter(struct CricketTeam info[], int n);
float averagerate(int totalrun, int totalmatch, int n);
void hightrun(struct CricketTeam info[], int n);
void showmvp(struct CricketTeam info[], int n);
float mvp(int Age, int Totalmatch, int Totalrun, int Hightrun, int n);
void Allrounders(struct CricketTeam info[], int n);
```
- Function prototypes are declared for various operations performed by the program.

### Main Function
```c
int main()
{
    char choice;
    int N;
    char name[50];
    FILE *file;
    file = fopen("input.txt", "r");

    fscanf(file, "%d", &N);
    printf("%d\n", N);
    int n = N;
    N = fgetc(file);
    N = fgetc(file);

    struct CricketTeam player[N];

    for(int i = 0; i < N; i++)
    {
        fgets(player[i].name, 50, file);
        printf("%s", player[i].name);

        fscanf(file, "%d", &player[i].age);
        printf("%d\n", player[i].age);
        N = fgetc(file);
        fgets(player[i].type, 50, file);
        printf("%s", player[i].type);

        fscanf(file, "%d", &player[i].totalmatch);
        printf("%d\n", player[i].totalmatch);

        fscanf(file, "%d", &player[i].totalrun);
        printf("%d\n", player[i].totalrun);

        fscanf(file, "%d", &player[i].hightrun);
        printf("%d\n", player[i].hightrun);
        printf("\n");
        N = fgetc(file);
        N = fgetc(file);
    }

    while(1)
    {
        printf("A. Show all players\nB. Show a particular player information (Provide Player Name)\n");
        printf("C. Show the most experienced player (MEP)\nD. Show the new comer player (NCP)\n");
        printf("E. Show the top scorer player (TSP)\nF. Show the hard hitter player (HHP)\n");
        printf("G. Show the highest run taker player (HRTP)\nH. Show the most valuable player (MVP)\n");
        printf("I. Show the allrounders\nJ. Exit/Quit\n\n");

        printf("Enter a choice : ");
        scanf("%c", &choice);
        choice = toupper(choice);
        if(choice == 'J') break;

        switch(choice)
        {
            case 'A':
                PlayerInfermation(player, n);
                break;
            case 'B':
                printf("Enter player name:");
                scanf(" %[^\n]", &name);
                allinfo(player, name, n);
                break;
            case 'C':
                printf("Most experienced player name is : %s\n", player[MostExperiencedPlayer(player, n)].name);
                break;
            case 'D':
                NewPlayer(player, n);
                break;
            case 'E':
                topscore(player, n);
                break;
            case 'F':
                hardhitter(player, n);
                break;
            case 'G':
                hightrun(player, n);
                break;
            case 'H':
                showmvp(player, n);
                break;
            case 'I':
                Allrounders(player, n);
                break;
            default:
                printf("Error!!\n\n");
                break;
        }

        scanf("%*c", &choice);
    }
    fclose(file);
    printf("\n\nThank you\n");

    return 0;
}
```
- The main function reads player data from a file, stores it in an array of `CricketTeam` structures, and provides a menu for the user to perform various operations.

### Functions

#### Show All Players
```c
void PlayerInfermation(struct CricketTeam info[], int n)
{
    int i;
    FILE *file;
    file = fopen("Player_info.txt", "w");
    for(i = 0; i < n; i++)
    {
        printf("%d %s", i + 1, info[i].name);
        fprintf(file, "%d. %s", i + 1, info[i].name);
    }
    fclose(file);
    printf("\n");
}
```
- Displays information about all players and writes it to a file.

#### Show Particular Player Information
```c
void allinfo(struct CricketTeam info[], char name[50], int n)
{
    int i;
    int strlength = strlen(name);
    for(i = 0; i < n; i++)
    {
        if(strncmp(name, info[i].name, strlength) == 0)
        {
            printf("Age : %d\n", info[i].age);
            printf("Type : %s", info[i].type);
            printf("Total match : %d\n", info[i].totalmatch);
            printf("Total run : %d\n", info[i].totalrun);
            printf("Highest run : %d\n", info[i].hightrun);
        }
    }
    printf("\n");
}
```
- Displays information about a specific player.

#### Most Experienced Player
```c
int MostExperiencedPlayer(struct CricketTeam most[], int n)
{
    int index = 0, max = most[0].totalmatch;
    for (int i = 1; i < n; i++)
    {
        if(max < most[i].totalmatch)
        {
            index = i;
            max = most[i].totalmatch;
        }
    }
    return index;
}
```
- Returns the index of the most experienced player based on the number of matches played.

#### New Comer Player
```c
void NewPlayer(struct CricketTeam info[], int n)
{
    int index = 0, min_age = info[0].age;
    for(int i = 1; i < n; i++)
    {
        if(min_age > info[i].age)
        {
            min_age = info[i].age;
            index = i;
        }
    }
    printf("New comer player name is : %s\n", info[index].name);
}
```
- Identifies and displays the newest player based on age.

#### Top Scorer Player
```c
void topscore(struct CricketTeam info[], int n)
{
    int index = 0, max_run = info[0].totalrun;
    for (int i = 1; i < n; i++)
    {
        if(max_run < info[i].totalrun)
        {
            index = i;
            max_run = info[i].totalrun;
        }
    }
    printf("Top scorer player name is : %s\n", info[index].name);
}
```
- Identifies and displays the top scorer player based on total runs.

#### Hard Hitter Player
```c
void hardhitter(struct CricketTeam info[], int n)
{
    int index = 0;
    float max_rate = averagerate(info[0].totalrun, info[0].totalmatch, n);
    for(int i = 1; i < n; i++)
    {
        if(max_rate < averagerate(info[i].totalrun, info[i].totalmatch, n))
        {
            index = i;
            max_rate = averagerate(info[i].totalrun, info[i].totalmatch, n);
        }
    }
    printf("Hard hitter player name is : %s\n", info[index].name);
}

float averagerate(int totalrun, int totalmatch, int n)
{
    return (totalrun * 1.0) / totalmatch;
}
```
- Identifies and displays the hard hitter player based on average run rate.

#### Highest Run Taker Player
```c
void hightrun(struct CricketTeam info[], int n)
{
    int index = 0, max_hightrun = info[0].hightrun;
    for (int i = 1; i < n; i++)
    {
        if(max_hightrun < info[i].hightrun)
        {
            index = i;
            max_hightrun = info[i].hightrun;
        }
    }
    printf("Highest run taker player is : %s\n", info[index].name);
}
```
- Identifies and displays the player with the highest individual run.

#### Most Valuable Player
```c
void showmvp(struct CricketTeam info[], int n)
{
    int index = 0;
    float max_mvp

 = mvp(info[0].age, info[0].totalmatch, info[0].totalrun, info[0].hightrun, n);

    for(int i = 1; i < n; i++)
    {
        if(max_mvp < mvp(info[i].age, info[i].totalmatch, info[i].totalrun, info[i].hightrun, n))
        {
            index = i;
            max_mvp = mvp(info[i].age, info[i].totalmatch, info[i].totalrun, info[i].hightrun, n);
        }
    }
    printf("MVP : %s\n", info[index].name);
}

float mvp(int Age, int Totalmatch, int Totalrun, int Hightrun, int n)
{
    return Age + Totalmatch + Totalrun + Hightrun + (Totalrun * 1.0) / Totalmatch + (Hightrun * 1.0) / Age;
}
```
- Identifies and displays the most valuable player based on a custom metric.

#### Allrounders
```c
void Allrounders(struct CricketTeam info[], int n)
{
    int x = 1;
    for(int i = 0; i < n; i++)
    {
        if(strncmp(info[i].type, "Allrounder", 10) == 0)
        {
            printf("%d %s", x++, info[i].name);
        }
    }
    printf("\n");
}
```
- Displays the names of all players who are allrounders.

## Conclusion
This program provides a comprehensive way to manage and analyze a cricket team. It reads player data from a file, stores it in a structured format, and allows various operations such as displaying player information, identifying top performers, and more.
