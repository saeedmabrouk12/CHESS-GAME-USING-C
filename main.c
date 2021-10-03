#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include<conio.h>
#define length 8
//save all moves to undo , save the old place for moved piece and the new one
//3 bools to check theres kil or promote or housing in the move
struct allmoves
{
    int a; int b; int c ; int d;
    bool ifkill;
    bool ifpromote;
    bool ifhousing;
};
struct allmoves movements[120];
//player tell who should play if even black if odd white it increase every play
int player=0;
// to make sure no one moved to make a good housing
bool housing[2][3]={true,true,true,true,true,true};
char chessboard[length][length],killed[30];
// using pointer because some time we need to return killed piece to play
char *numofkilled=killed;
// fun to full chessboard array with  peices  and replace white places with '.' and black with '-' and print white team
//with small caracters and black with capital.
void fullchess();
//print the chessboard array every single play and take the new play if the player need to play or undo or redo
void printchessboard ();
//check if the player determine to play a piece belongs to him and if the position he need to move is full make sure
//it is not full with his pieces
void checkmove (int a,int b,int c,int d);

void movewithoutkill (int a,int b,int c,int d);
void movewithkill (int a,int b,int c,int d);
bool isempty (int c, int d);
void checkhousing (int a,int b,int c,int d);
void promotion (int c , int d);
bool checkwhitebowns (int a,int b,int c,int d);
bool checkblackbowns (int a,int b,int c,int d);
bool checkrooks (int a,int b,int c,int d);
bool checkknights (int a,int b,int c,int d);
bool checkbishops (int a,int b,int c,int d);
bool checkqueen (int a,int b,int c,int d);
bool checkking (int a,int b,int c,int d);
int main(void)
{
    fullchess();
    printchessboard();
}
void fullchess()
{
    for (int i=0;i<length;i++)
    {
            for (int j=0;j<length;j++)
            {
                if ((i-j)%2==0) chessboard[i][j]='.';
                else chessboard[i][j]='-';
            }
    }
    for (int j=0;j<length;j++) chessboard[1][j]='p';
    for (int j=0;j<length;j++) chessboard[6][j]='P';
    chessboard[0][0]=chessboard[0][7]='r';
    chessboard[7][0]=chessboard[7][7]='R';
    chessboard[0][1]=chessboard[0][6]='n';
    chessboard[7][1]=chessboard[7][6]='N';
    chessboard[0][2]=chessboard[0][5]='b';
    chessboard[7][2]=chessboard[7][5]='B';
    chessboard[0][4]='q';
    chessboard[7][4]='Q';
    chessboard[0][3]='k';
    chessboard[7][3]='K';
    return;
}
void printchessboard ()
{
    system("cls");
    printf(".................................\n..............CHESS..............\n.................................\n");
    for (int i=0;i<length;i++) printf("   %c",'a'+i);
    printf("\n");
    for (int i=0;i<length;i++)
    {
        printf(" %d",abs(8-i));
        for (int j=0;j<length;j++)
        {
            printf("[%c] ",chessboard[i][j]);
        }
        printf("\n");
    }
    printf(" KILLED : ");
    for (int i=0;killed[i]!=*numofkilled;i++)   printf("%c",killed[i]);
    printf("\n");
    printf("Make sure u don't open caps lock\n");
    printf("For undo click u for redo click r for play click n\n");
    if (player%2==0)printf("White Should Play\n");
    else printf("Black Should Play\n");
    char choise;
    scanf(" %c",&choise);
    switch(choise)
    {
        case 'u':
            if (player==0)
            {
                printf("hnhzr.. ?");
                while (getchar()!='\n');
                while (getchar()!='\n');
                printchessboard();
            }
            int a=movements[player-1].a;
            int b=movements[player-1].b;
            int c=movements[player-1].c;
            int d=movements[player-1].d;
            chessboard[a][b]=chessboard[c][d];
            if (movements[player-1].ifpromote)
            {
                chessboard[a][b]='p';
            }
            else if (movements[player-1].ifhousing)
            {
                if (a==0)
                {
                    if (d==1)
                    {
                        chessboard[0][0]='r';
                        clearcell(0,2);
                    }
                    else
                    {
                        chessboard[0][7]='r';
                        clearcell(0,4);
                    }
                }
                else
                {
                    if (d==1)
                    {
                        chessboard[7][0]='R';
                        clearcell(7,2);
                    }
                    else
                    {
                        chessboard[7][7]='R';
                        clearcell(7,4);
                    }
                }
            }
            clearcell(c,d);
            if (movements[player-1].ifkill)
            {
                *numofkilled--;
                chessboard[c][d]=*numofkilled;
            }
            player--;
            printchessboard();
            break;
            case 'r':
                checkmove(movements[player].a,movements[player].b,movements[player].c,movements[player].d);
                break;
            case 'n':
                {
                char x1,x2;
                int y1,y2;
                printf("From ?");
                while (getchar()!='\n');
                scanf(" %c %d",&x1,&y1);
                printf("To?");
                scanf(" %c %d",&x2,&y2);
                checkmove(y1,x1,y2,x2);
                break;
            default:
                printf("NOT Valid. You Have To Chose u , r or n");
                        while (getchar()!='\n');
                        while (getchar()!='\n');
                        printchessboard();
                }
        }
}
void checkmove (int a,int b,int c,int d)
{
    if (b>30)
    {
        a=abs(8-a);
        b=b-97;
        c=abs(8-c);
        d=d-97;
    }
    //cheak who play white or black
    if (player%2==0&&chessboard[a][b]>65&&chessboard[a][b]<83)
    {
            printf("NOT Valid. White Should Play");
                while (getchar()!='\n');
                while (getchar()!='\n');
                printchessboard();
    }
    else if(player%2==1&&chessboard[a][b]>97&&chessboard[a][b]<115)
    {
                    printf("NOT Valid. black Should Play");
                    while (getchar()!='\n');
                    while (getchar()!='\n');
                    printchessboard();
    }
    if (player%2==0&&chessboard[c][d]>97&&chessboard[c][d]<115)
    {
        printf("NOT Valid. hanhzr ?");
                while (getchar()!='\n');
                while (getchar()!='\n');
                printchessboard();
    }
    else if (player%2==1&&chessboard[c][d]>65&&chessboard[c][d]<83)
    {
        printf("NOT Valid. hanhzr ?");
                while (getchar()!='\n');
                while (getchar()!='\n');
                printchessboard();
    }
    switch (chessboard[a][b])
    {
        case 'p':
            if (checkwhitebowns(a,b,c,d)){
                if (isempty(c,d))movewithoutkill(a,b,c,d);
                else movewithkill(a,b,c,d);
                printchessboard();
            }
            else {
                    printf("NOT Valid.You can't Use This Place");
                    while (getchar()!='\n');
                    while (getchar()!='\n');
                    printchessboard();
                }
            break;
        case 'P':
            if (checkblackbowns(a,b,c,d)){
                if (isempty(c,d))movewithoutkill(a,b,c,d);
                else movewithkill(a,b,c,d);
                    printchessboard();
            }
            else {
                    printf("NOT Valid.You can't Use This Place");
                    while (getchar()!='\n');
                    while (getchar()!='\n');
                    printchessboard();
                }
            break;
        case 'R' : case 'r':
               if (checkrooks(a,b,c,d)){
                if (isempty(c,d))movewithoutkill(a,b,c,d);
                else movewithkill(a,b,c,d);
                printchessboard();
            }
            else {
                    printf("NOT Valid.You can't Use This Place");
                    while (getchar()!='\n');
                    while (getchar()!='\n');
                    printchessboard();
                }
            break;
        case 'N' : case 'n' :
               if (checkknights(a,b,c,d)){
                if (isempty(c,d))movewithoutkill(a,b,c,d);
                else movewithkill(a,b,c,d);
                printchessboard();
            }
            else {
                    printf("NOT Valid.You can't Use This Place");
                    while (getchar()!='\n');
                    while (getchar()!='\n');
                    printchessboard();
                }
            break;
        case 'B': case 'b':
               if (checkbishops(a,b,c,d)){
                if (isempty(c,d))movewithoutkill(a,b,c,d);
                else movewithkill(a,b,c,d);
                printchessboard();
            }
            else {
                    printf("NOT Valid.You can't Use This Place");
                    while (getchar()!='\n');
                    while (getchar()!='\n');
                    printchessboard();
                }
            break;
        case 'Q': case 'q':
               if (checkqueen(a,b,c,d)){
                if (isempty(c,d))movewithoutkill(a,b,c,d);
                else movewithkill(a,b,c,d);
                printchessboard();
            }
            else {
                    printf("NOT Valid.You can't Use This Place");
                    while (getchar()!='\n');
                    while (getchar()!='\n');
                    printchessboard();
                }
            break;
        case 'K': case 'k':
            if (checkking(a,b,c,d)){
                if (isempty(c,d))movewithoutkill(a,b,c,d);
                else movewithkill(a,b,c,d);
                printchessboard();
            }
            else {
                    printf("NOT Valid.You can't Use This Place");
                    while (getchar()!='\n');
                    while (getchar()!='\n');
                    printchessboard();
                }
            break;
    }
    printchessboard();
}
void movewithoutkill (int a,int b,int c,int d)
{

    if (chessboard[a][b]=='p'&&c==7)                   movements[player].ifpromote=true;
    else if  (chessboard[a][b]=='P'&&c==0)           movements[player].ifpromote=true;
    else                                                              movements[player].ifpromote=false;


    if ((chessboard[a][b]=='k'||chessboard[a][b]=='K')&&abs(d-b)==2)            movements[player].ifhousing=true;
    else                                                                                                    movements[player].ifhousing=false;

    movements[player].ifkill=false;
    movements[player].a=a;
    movements[player].b=b;
    movements[player].c=c;
    movements[player].d=d;
    player++;
    chessboard[c][d]=chessboard[a][b];
     clearcell(a,b);
    promotion (c,d);
    checkhousing(a,b,c,d);
}
void movewithkill (int a,int b,int c,int d)
{
     if (chessboard[a][b]=='p'&&c==7)             movements[player].ifpromote=true;
    else if  (chessboard[a][b]=='P'&&c==0)     movements[player].ifpromote=true;
    else                                                            movements[player].ifpromote=false;

    movements[player].ifkill=true;
    movements[player].a=a;
    movements[player].b=b;
    movements[player].c=c;
    movements[player].d=d;
    *numofkilled=chessboard[c][d];
    numofkilled++;
    chessboard[c][d]=chessboard[a][b];
    clearcell(a,b);
    checkhousing(a,b,c,d);
    player++;
}
bool isempty (int c, int d)
{
    if (chessboard[c][d]=='-'||chessboard[c][d]=='.') return true;
    return false;
}
void checkhousing (int a,int b,int c,int d)
{
    if (chessboard[c][d]=='r'&&b==0)            housing[0][0]=true;
    else if (chessboard[c][d]=='k')                 housing[0][1]=true;
    else if (chessboard[c][d]=='r'&&b==7)      housing[0][2]=true;
    else if (chessboard[c][d]=='R'&&b==0)     housing[1][0]=true;
    else if (chessboard[c][d]=='K')                 housing[1][1]=true;
    else if (chessboard[c][d]=='R'&&b==7)     housing[1][2]=true;
}
void promotion (int c , int d)
{
    if (chessboard[c][d]=='p'&&c==7)
    {
        system("cls");
        char t;
        printf("PROMOTE TO ?  choose   r   b   n   or  q ");
        do {scanf(" %c",&t);}
        while (!(t=='r'||t=='b'||t=='n'||t=='q'));
        chessboard[c][d]=t;
    }
    else if  (chessboard[c][d]=='P'&&c==0)
    {
        system("cls");
        char t;
        printf("PROMOTE TO ?  choose   R   B   N   or  Q ");
        do {scanf(" %c",&t);}
        while (!(t=='R'||t=='B'||t=='N'||t=='Q'));
        chessboard[c][d]=t;
    }
}
bool checkwhitebowns (int a,int b,int c,int d)
{
    if (c-a==2)
    {
        if (d==b)
        {
            if (a==1) return true;
            else return false;
        }
        else return false;
    }
    else if (c-a==1)
    {
        if (d==b)
        {
            if (isempty(c,d)) return true;
            else return false;
        }
        else if (abs(d-b)==1)
        {
            if (!isempty(c,d))
            {
                return true;
            }
        }
        else return false;
    }
    else return false;
}
bool checkblackbowns (int a,int b,int c,int d)
{
    if (a-c==2)
    {
        if (d==b)
        {
            if (a==6) return true;
            else return false;
        }
        else return false;
    }
    else if (a-c==1)
    {
        if (d==b)
        {
            if (isempty(c,d)) return true;
            else return false;
        }
        else if (abs(d-b)==1)
        {
            if (!isempty(c,d))
            {
                return true;
            }
        }
        else return false;
    }
    else return false;
}
bool checkrooks (int a,int b,int c,int d)
{
    if (a==c&&d!=b)
    {
        for (int i=d>b?b+1:b-1;i!=d;d>b?i++:i--){
            if (!(chessboard[a][i]=='.'||chessboard[a][i]=='-')) return false;
        }
        return true;
    }
    else if (a!=c&&d==b)
    {
          for (int i=c>a?a+1:a-1 ; i!=c ; c>a?i++:i--)
          {
            if (!(chessboard[i][b]=='.'||chessboard[i][b]=='-')) return false;
          }
          return true;
    }
    else return false;
}
bool checkknights (int a,int b,int c,int d)
{
    if (abs(a-c)==1&&abs(d-b)==2) return true;
    else if (abs(a-c)==2&&abs(d-b)==1)  return true;
    else return false;
}
bool checkbishops (int a,int b,int c,int d)
{
    if (abs(a-c)==abs(d-b))
    {
        for (int i=c>a?a+1:a-1, j=d>b?b+1:b-1  ; i!=c ; c>a?i++:i--,d>b?j++:j--)
        {
            if (!(chessboard[i][j]=='.'||chessboard[i][j]=='-')) return false;
        }
        return true;
    }
    else return false;
}
bool checkqueen (int a,int b,int c,int d)
{
    if (checkrooks(a,b,c,d)||checkbishops(a,b,c,d)) return true;
    else return false;
}
bool checkking (int a,int b,int c,int d)
{
    int index=1?a==7:0;
    if (abs(a-c)==1&&abs(d-b)==1)  return true;
    else if (a==c&&abs(d-b)==1) return true;
    else if (abs(a-c)==1&&d==b)  return true;
    else if (d-b==2&&a==c&&housing[index][1]&&housing[index][2])
    {
        if (a==0) {
            chessboard[a][4]='r';
            clearcell(a,7);
        }
        else {
            chessboard[a][4]='R';
            clearcell(a,7);
        }
        return true;
    }
    else if (b-d==2&&a==c&&housing[index][1]&&housing[index][0])
    {
        if (a==0)
         {
            chessboard[a][2]='r';
            clearcell(a,0);
        }
        else
        {
            chessboard[a][2]='R';
            clearcell(a,0);
        }
        return true;
    }
    return false;
}
void clearcell (int a,int b)
{
    if ((a-b)%2==0) chessboard[a][b]='.';
    else chessboard[a][b]='-';
}
