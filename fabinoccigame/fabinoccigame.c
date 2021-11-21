  #include<stdio.h>
  #include<stdlib.h>
#include<time.h>

int checkemptycell(int a[5][5],int i,int size)
{
    for(int j=0;j<size;j++)
    {
        if(a[i][j]==0)
            return 1;
    }
    return 0;
}
int getemptycellsofrow(int a[5][5],int empty[5],int row,int size)
{
    int temp=0,i;
    for(i=0;i<size;i++)
    {
        if(a[row][i]==0)
            empty[temp++]=i;
    }
    return temp;
}
void displayboard(int a[5][5],int dim)
{
    for(int i=0;i<dim;i++)
     {
        for(int j=0;j<dim;j++)
        {
            printf("%d   ",a[i][j]);
        }
        printf("\n");
     }
}
int setfabchain(long int *fab,int size)
{
    int i=1,j=1,temp,n=(2*size*size)-2;
    while(n--)
    {
        fab[i]=j;
        temp=i;
        i=i+j;
        j=temp;
    }
    return temp;
}
int getrowwithemptycells(int a[5][5],int rows[5],int size)
{
    int temp=0,i=0;
    while(i<size)
    {
        if(checkemptycell(a,i,size))
        {
        rows[temp]=i;
        temp=temp+1;
        }
        i++;
    }
    return temp;
}
int moveright(int a[5][5],long int *fab,int size,int winscore)
{
 int i,j,k,x,flag=0,win=0;
 for(i=0;i<size;i++)
 {
     j=size-1;
     while(j>0)
     {
         k=j-1;
         x=j;
         while(a[i][k]==0 && k>=0)
            k--;
         if(k<0)
            break;
         if(a[i][j]!=0)
            j--;
         int current=a[i][x],target=a[i][k];
         if(fab[current]==target || fab[target]==current || a[i][x]==0)
        {
            flag=1;
            a[i][x]=a[i][x]+a[i][k];
            if(a[i][x]==winscore)
                win=2;
            a[i][k]=0;
        }
     }
 }
 if(win)
    return win;
 else
 return flag;
}
int  moveleft(int a[5][5],long int *fab,int size,int winscore)
{
int i,j,k,x,flag=0,win=0;
 for(i=0;i<size;i++)
 {
     j=0;
     while(j<size-1)
     {
         k=j+1;
         x=j;
         while(a[i][k]==0 && k>=0)
            k++;
         if(k>size-1)
            break;
         if(a[i][j]!=0)
            j++;
         int current=a[i][x],target=a[i][k];
         if(fab[current]==target || fab[target]==current || a[i][x]==0)
        {
            flag=1;
            a[i][x]=a[i][x]+a[i][k];
            if(a[i][x]==winscore)
                win=2;
            a[i][k]=0;
        }
     }
 }
 if(win)
    return win;
 else
 return flag;
}
int moveup(int a[5][5],long int *fab,int size,int winscore)
{
   int i,j,k,x,flag=0,win=0;
 for(j=0;j<size;j++)
 {
     i=0;
     while(i<size-1)
     {
         k=i+1;
         x=i;
         while(a[k][j]==0 && k>=0)
            k++;
         if(k>size-1)
            break;
         if(a[i][j]!=0)
            i++;
         int current=a[x][j],target=a[k][j];
         if(fab[current]==target || fab[target]==current || a[x][j]==0)
        {
            flag=1;
            a[x][j]=a[x][j]+a[k][j];
            if(a[x][j]==winscore)
                win=2;
            a[k][j]=0;
        }
     }
 }
 if(win)
 return win;
 else
    return flag;
 return flag;
}
struct info{
    char *name;
    char *date;
    int size;
    int moves;
};
char *getdate()
{
    char *today=(char *)malloc(11*sizeof(char));
    time_t t = time(0);
    struct tm* lt = localtime(&t);
    sprintf(today, "%02d/%02d/%04d", lt->tm_mday, lt->tm_mon + 1, lt->tm_year +1900);
    return today;
}
struct info* storeinfo(char* name,int size,int moves)
{
    struct info* new=(struct info*)malloc(sizeof(struct info));
    new->name=(char *)malloc(30*sizeof(char));
    new->date=(char*)malloc(11*sizeof(char));
    new->size=size;
    new->name=name;
    new->moves=moves;
    new->date=getdate();
};
int movedown(int a[5][5],long int *fab,int size,int winscore)
{
    int i,j,k,x,flag=0,win=0;
 for(j=0;j<size;j++)
 {
     i=size-1;
     while(i>0)
     {
         k=i-1;
         x=i;
         while(a[k][j]==0 && k>=0)
            k--;
         if(k<0)
            break;
         if(a[i][j]!=0)
            i--;
         int current=a[x][j],target=a[k][j];
         if(fab[current]==target || fab[target]==current || a[x][j]==0)
        {
            flag=1;
            a[x][j]=a[x][j]+a[k][j];
            if(a[x][j]==winscore)
                win=2;
            a[k][j]=0;
        }
     }
 }
 if(win)
 return win;
 else
 return flag;
}
void generatetile(int a[5][5],int size)
{
    int rows[5],cols[5],row,col,index,temp;
    srand(time(NULL));
    temp=getrowwithemptycells(a,rows,size);
    index=rand()%temp;
    row=rows[index];
    temp=getemptycellsofrow(a,cols,row,size);
    index=rand()%temp;
    col=cols[index];
    a[row][col]=1;
}
void storestate(struct info *playerinfo,int a[5][5])
{
    FILE *q=fopen("replay.txt","r+");
    char *ding=(char *)malloc(100*sizeof(char));
    fprintf(q,"%d\n%s--%d--%d--\n",1,playerinfo->name,playerinfo->size,playerinfo->moves);
    int size,i,j;
    size=playerinfo->size;
    for(i=0;i<size;i++)
    for(j=0;j<size;j++)
    fprintf(q,"%d--",a[i][j]);
    fprintf(q,"\noverr");
}
int  makemove(char selectedmove,int a[5][5],long int *fab,int size,int winscore,struct info *playerinfo)
{
    int success=0;
    if(selectedmove=='w' || selectedmove=='W')
        success=moveup(a,fab,size,winscore);
      else if(selectedmove=='a' || selectedmove=='A')
        success=moveleft(a,fab,size,winscore);
      else if(selectedmove=='s' || selectedmove=='S')
        success=movedown(a,fab,size,winscore);
      else if(selectedmove=='d' || selectedmove=='D')
        success=moveright(a,fab,size,winscore);
      else if(selectedmove=='z' || selectedmove=='Z')
      {
        storestate(playerinfo,a);
        return -1;
      }
      else
        printf("please enter right choice\n");
    return success;
}
int checkfornomove(int a[5][5],long int *fab,int x,int winscore)
{
    int b[5][5]={0};
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<x;j++)
        {
            b[i][j]=a[i][j];
        }
    }
    if(moveup(b,fab,x,winscore)||movedown(b,fab,x,winscore)||moveleft(b,fab,x,winscore)|| moveright(b,fab,x,winscore))
        return 1;
    return 0;
}
int getmoves(char *line)
{
    int i=0,moves=0,count=0;
    while(line[i])
        {
            if(line[i++]=='-')
                count++;
            if(count>=6)
                break;
        }
        while(line[i+1])
        {
            moves=moves*10+(line[i]-'0');
            i++;
        }
    return moves;
}
void writetofile(struct info* playerinfo)
{
    FILE *p,*q;
    char *line;
    line=(char *)malloc(100*sizeof(char));
    p=fopen("leaderboard.txt","r+");
    q=fopen("temp.txt","r+");
    while(fgets(line,100,p)!=NULL)
    {
        int moves=(getmoves(line));
        if(moves>playerinfo->moves)
            break;
        fputs(line,q);
    }
    fprintf(q,"%s--%s--%d*%d--%d",playerinfo->date,playerinfo->name,playerinfo->size,playerinfo->size,playerinfo->moves);
    fprintf(q,"\n");
    fputs(line,q);
    while(fgets(line,100,p)!=NULL)
    {
        fputs(line,q);
    }
    fclose(p);
    fclose(q);
    p=fopen("leaderboard.txt","r+");
    q=fopen("temp.txt","r");
    while(fgets(line,100,q)!=NULL)
    {
        fputs(line,p);
    }
    fclose(p);
    fclose(q);
}
void viewleaderboard()
{
    int sno=1;
    FILE *p=fopen("leaderboard.txt","r");
    char *line=(char *)malloc(100*sizeof(char));
    printf("sno    date        name               size      moves\n\n");
    while(fgets(line,100,p)!=NULL)
    {
        int i=0,count=0,size=0;
        if(line[1]!=NULL)
        printf("%d   ",sno++);
        while(line[i]!=NULL)
        {
            if(line[i]!='-')
            {
                printf("%c",line[i]);
                size++;
            }
            else
            {
                count++;
                if(count==3)
                {
                    for(int z=0;z<30-size;z++)
                    printf(" ");
                    i=i+1;
                }
                else
                printf("  ");
            }
            i++;
        }
        printf("\n");
    }
}
int playgame(struct info *playerinfo,int a[5][5])
{
    int x,winscore,success,selectedmove;
    x=playerinfo->size;
    long int *fab=(long int *)malloc(1500000*sizeof(long int *));
    displayboard(a,x);
    winscore=setfabchain(fab,x);
    while(checkfornomove(a,fab,x,winscore))
    {
      printf("enter move\n");
      scanf(" %c",&selectedmove);
      success=makemove(selectedmove,a,fab,x,winscore,playerinfo);
      if(success==1)
        generatetile(a,x);
      if(success==2)
        return 1;
      system("cls");
      displayboard(a,x);
      if(success==-1)
      return -1;
      printf("your moves:%d\n",++playerinfo->moves);
    }
    displayboard(a,x);
    return 0;
}
struct info* restorePlayerInfo(char *temp)
{
    struct info *playerinfo=(struct info*)malloc(sizeof(struct info*));
    playerinfo->name=(char *)malloc((100*sizeof(char)));
    playerinfo->date=(char *)malloc(11*sizeof(char));
    int i=0,moves=0;
    printf("%s",temp);
    while(temp[i]!='-')
    {
        playerinfo->name[i]=temp[i];
        i++;
    }
    playerinfo->name[i]='\0';
    i=i+2;
    playerinfo->size=temp[i]-'0';
    printf("i:%d",i);
    i=i+3;
    while(temp[i]!='-')
    {
        moves=moves*10+temp[i]-'0';
        i++;
    }
    playerinfo->moves=moves;
    playerinfo->date=getdate();
}
void restoreGameState(char *temp,int a[5][5],int size)
{
    int i,j,k=0,num=0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            num=0;
            while(temp[k]!='-')
            {
                num=num*10+temp[k]-'0';
                k++;
            }
            a[i][j]=num;
            k=k+2;
        }
    }
}
int main()
{
    char *replay=(char*)malloc(5*sizeof(char));
    char *temp=(char*)malloc(100*sizeof(char));
    char *temp2=(char*)malloc(100*sizeof(char));
    struct info *playerinfo;
    FILE *p=fopen("replay.txt","r+");
    int a[5][5]={0},x,win=2,moves=0,success,winscore,option;
    char selectedmove;
    fgets(replay,100,p);
    printf("select\n 1:playgame \t 2:view leaderboard");
    if(replay[0]=='1')
        printf("\t 3:resume the game");
    printf("\n");
    scanf("%d",&option);
    if(option==2)
        viewleaderboard();
    else if(option==3)
    {
     fgets(temp,100,p);
     playerinfo=restorePlayerInfo(temp);
     fgets(temp2,100,p);
     restoreGameState(temp2,a,playerinfo->size);
     displayboard(a,playerinfo->size);
     win=playgame(playerinfo,a);
    }
    else
    {
        char *name=(char*)malloc(50*sizeof(char));
        printf("please enter your info\n");
        printf("enter name:");
        fflush(stdin);
        gets(name);
        printf("enter size:");
        scanf(" %d",&x);
        printf("to move up:press W or w\nto move down:press S OR s\nto move left:press a or A\nto move right:press d OR D\n");
        playerinfo=storeinfo(name,x,moves);
        generatetile(a,x);
        generatetile(a,x);
        displayboard(a,x);
        win=playgame(playerinfo,a);
    }
    fclose(p);
    FILE *q=fopen("replay.txt","r+");
    if(win==1)
    {
        fprintf(q,"%d\n",0);
        printf("%s ,you win with %d moves\n",playerinfo->name,playerinfo->moves);
        writetofile(playerinfo);
    }
    else if(win==0)
    {
        fprintf(q,"%d\n",0);
        printf("sry try again\n");
    }
    else if(win==-1)
    {
        displayboard(a,x);
        printf("your game is successfully saved\n");
    }
    fclose(q);
    return 0;
}
