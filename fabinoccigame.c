#include<stdio.h>
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
int  makemove(char selectedmove,int a[5][5],long int *fab,int size,int winscore)
{
    int success=0;
    if(selectedmove=='w')
        success=moveup(a,fab,size,winscore);
      else if(selectedmove=='a')
        success=moveleft(a,fab,size,winscore);
      else if(selectedmove=='s')
        success=movedown(a,fab,size,winscore);
      else if(selectedmove=='d')
        success=moveright(a,fab,size,winscore);
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
int main()
{
    int x;
    long int *fab=(long int *)malloc(1500000*sizeof(long int *));
    int a[5][5]={0},i,index,emptytile=1,win=0,moves=0,success,winscore;
    char selectedmove;
    scanf("%d",&x);
    winscore=setfabchain(fab,x);
    generatetile(a,x);
    generatetile(a,x);
    displayboard(a,x);
    while(checkfornomove(a,fab,x,winscore))
    {
      printf("enter move\n");
      scanf(" %c",&selectedmove);
      success=makemove(selectedmove,a,fab,x,winscore);
      if(success==1)
        generatetile(a,x);
      if(success==2)
      {
        win=1;
        break;
      }
      system("cls");
      displayboard(a,x);
      printf("your moves:%d\n",moves);
      moves++;
    }
    displayboard(a,x);
    if(win==1)
        printf("you win\n");
    else
        printf("sry try again\n");
}
