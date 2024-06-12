#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CricketTeam
{
    char name[50];
    int age;
    char type[20];
    int totalmatch;
    int totalrun;
    int hightrun;
};

void PlayerInfermation(struct CricketTeam info[], int n);
void allinfo(struct CricketTeam info[],char name[50], int n);
int MostExperiencedPlayer(struct CricketTeam most[], int n);
void NewPlayer(struct CricketTeam info[], int n);
void topscore(struct CricketTeam info[], int n);
void hardhitter(struct CricketTeam info[], int n);
float averagerate(int totalrun,int totalmatch, int n);
void hightrun(struct CricketTeam info[], int n);
void showmvp(struct CricketTeam info[], int n);
float mvp(int Age,int Totalmatch,int Totalrun, int Hightrun, int n);
void Allrounders(struct CricketTeam info[], int n);


int main()
{
    char choice;
    int N;
    char name[50];
    FILE *file;
    file= fopen("input.txt","r");

    //N=fgetc(file);
    fscanf(file,"%d",&N);
    printf("%d\n",N);
    int n=N;
    N=fgetc(file);
    N=fgetc(file);

    struct CricketTeam player[N];

    for(int i=0; i<N; i++)
    {
        fgets(player[i].name,50,file);
        printf("%s",player[i].name);

        fscanf(file,"%d",&player[i].age);
        printf("%d\n",player[i].age);
        N=fgetc(file);//fflush(file);
        fgets(player[i].type,50,file);
        printf("%s",player[i].type);

        fscanf(file,"%d",&player[i].totalmatch);
        printf("%d\n",player[i].totalmatch);

        fscanf(file,"%d",&player[i].totalrun);
        printf("%d\n",player[i].totalrun);

        fscanf(file,"%d",&player[i].hightrun);
        printf("%d\n",player[i].hightrun);
        printf("\n");
        N=fgetc(file);
        N=fgetc(file);

    }

    while(1)
    {
        printf("A. Show all players\nB. Show a particular player information (Provide Player Name)\n");
        printf("C. Show the most experienced player (MEP)\nD. Show the new commer player (NCP)\n");
        printf("E. Show the top scorer player (TSP)\nF. Show the hard hitter player (HHP)\n");
        printf("G. Show the highest run taker player (HRTP)\nH. Show the most valuable player (MVP)\n");
        printf("I. Show the allrounders\nJ. Exit/Quit\n\n");



        printf("Enter a choice : ");
        scanf("%c",&choice);//printf("%c\n",choice);
        choice = toupper(choice); //printf("%c\n",choice);
        if(choice=='J')break;

        switch(choice)
        {

        case 'A':
            PlayerInfermation(player, n);
            break;
        case 'B':
            printf("Enter player name:");
            scanf(" %[^\n]",&name);
            //printf("%s\n",name);
            allinfo(player,name,n);
            break;
        case 'C':
            printf("Most experiance player name is : %s\n",player[MostExperiencedPlayer(player, n)].name);
            break;
        case 'D':
            NewPlayer(player,n);
            break;
        case 'E':
            topscore(player,n);
            break;
        case 'F':
            hardhitter(player,n);
            break;
        case 'G':
            hightrun(player,n);
            break;
        case 'H':
            showmvp(player,n);
            break;
        case 'I':
            Allrounders(player,n);
            break;
        default :
            printf("Error!!\n\n");
            break;
        }

        //fflush(file);
        scanf("%*c",&choice);
        fclose(file);

    }
    printf("\n\nThank you\n");


    return 0;

}

//A. Show All Players

void PlayerInfermation(struct CricketTeam info[], int n)
{
    int i;
    FILE *file;
    file=fopen("Player_info.txt","w");
    for(i=0; i<n; i++)
    {
        printf("%d %s",i+1,info[i].name);
        fprintf(file,"%d. %s",i+1,info[i].name);
    }
    fclose(file);
    printf("\n");
}

//B. Show A Particular player information (Provide Player Name)

void allinfo(struct CricketTeam info[],char name[50], int n)
{
    int i;
    //printf("in allinfo\n");
    int strlength = strlen(name);
    //printf("String length: %d\n",strlength);
    for(i=0; i<n; i++)
    {
        if(strncmp(name,info[i].name,strlength) == 0)
        {
            //printf("Name : %s",info[i].name);
            printf("Age : %d\n",info[i].age);
            printf("Type : %s",info[i].type);
            printf("Total match : %d\n",info[i].totalmatch);
            printf("Total run : %d\n",info[i].totalrun);
            printf("Hight run : %d\n",info[i].hightrun);

        }
    }
    printf("\n");
}

//C. Show the MOST Experienced Player (MEP)

int MostExperiencedPlayer(struct CricketTeam most[], int n)
{
    int index,max,i;
    index=0;
    max=most[0].totalmatch;
    for (i=1; i<n; i++)
    {
        if(max<most[i].totalmatch)
        {
            index=i;
            max=most[i].totalmatch;
        }
    }
    return index;
}

//D. Show the New Commer Player (NCP)

void NewPlayer(struct CricketTeam info[], int n )
{

    int i,index=info[0].age,indexage=0;

    for(i=1; i<n; i++)
    {
        if(index>info[i].age)
        {

            index=info[i].age;
            indexage=i;
        }

    }
    printf("New commer player name is : %s\n",info[indexage].name);
}

//E. Show the Top Scorer Player (TSP)

void topscore(struct CricketTeam info[],int n)
{

    int i,index=0,indextotal=info[0].totalrun;
    for (i=1; i<n; i++)
    {
        if(indextotal<info[i].totalrun)
        {
            index=i;
            indextotal=info[i].totalrun;

        }
    }
    printf("Top score player name is : %s\n",info[index].name);
}

//F. Show the Hard Hitter Player (HHP)


void hardhitter(struct CricketTeam info[],int n)
{

    int i,index=0;
    float indexrate=averagerate(info[0].totalrun,info[0].totalmatch,n);
    for(i=1; i<n; i++)
    {

        if(indexrate<averagerate(info[i].totalrun,info[i].totalmatch,n))
        {

            index=i;
            indexrate=averagerate(info[i].totalrun,info[i].totalmatch,n);

        }
    }
    printf("Hard hitter player name is : %s\n",info[index].name);
}

float averagerate(int totalrun,int totalmatch,int n  )
{

    float avg;

    avg= (totalrun*1.0)/(totalmatch);

    return avg;
}


//G. Show the Highest Run Taker Player (HRTP)

void hightrun(struct CricketTeam info[],int n)
{

    int i,index=0,indexhightrun=info[0].hightrun;
    for (i=1; i<n; i++)
    {
        if(indexhightrun<info[i].hightrun)
        {
            index=i;
            indexhightrun=info[i].hightrun;

        }
    }
    printf("Highest run taker player is : %s\n",info[index].name);

}


//H. Show the MOST Valuable Player (MVP)

void showmvp(struct CricketTeam info[],int n)
{
    int i, index=0;
    float indexmvp=mvp( info[0].age, info[0].totalmatch, info[0].totalrun, info[0].hightrun,n);

    for(i=1; i<n; i++)
    {
        if(indexmvp<mvp( info[i].age, info[i].totalmatch, info[i].totalrun, info[i].hightrun,n ))
        {
            index=i;
            indexmvp=mvp( info[i].age, info[i].totalmatch, info[i].totalrun, info[i].hightrun,n);
        }
    }
    printf("MVP : %s\n",info[index].name);
}

float mvp(int Age,int Totalmatch,int Totalrun, int Hightrun,int n)
{

    float rate;
    rate = Age + Totalmatch + Totalrun + Hightrun + (Totalrun*1.0)/(Totalmatch) + (Hightrun*1.0)/(Age) ;
    return rate;
}


// I. Show the Allrounders

void Allrounders(struct CricketTeam info[],int n)
{

    int i;
    int A,x=1;
    for(i=0; i<n; i++)
    {
        A =  strncmp(info[i].type,"Allrounder",10);
        if(A==0)
        {
            printf("%d %s",x++,info[i].name);
        }
    }
    printf("\n");
}

//end
