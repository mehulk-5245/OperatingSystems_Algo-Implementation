#include<stdio.h>
#define SIZE 3
//function prototypes
int display();
int Pagerep(int);
int Pagefault(int);
int Search(int );

int full=0;//To check whether all frames are filled
int a[21];
int ref[SIZE];//reference bits for each frame
int frame[SIZE];
int repptr=0;//Initialised to first frame
int count=0;
int main()
	{
	int n,i;
	FILE *fp;
	fp=fopen("input.txt","r");	
	printf("The number of elements in the reference string are :");
	fscanf(fp,"%d",&n);//18
	printf("%d",n);
	for(i=0;i<n;i++)
	{
	fscanf(fp,"%d",&a[i]);
	}
	printf("\nThe elements present in the string are\n");
	for(i=0;i<n;i++)
	{
	printf("%d ",a[i]);
	}
	printf("\n\n");
	for(i=0;i<n;i++)
	{
	if(Search(a[i])!=1)
	{
	Pagefault(a[i]);
	display();
	count++;
	}
	}
	printf("\nThe number of page faults are %d\n",count);
	return 0;
	}
//display function
int display()
{
	int i;
	printf("\nThe elements in the frame are\n");
	for(i=0;i<full;i++)
	{
	printf("%d\n",frame[i]);
	}
	}
//pagereplacement fucntion
int Pagerep(int ele)
{
	int temp;

	while(ref[repptr]!=0)
	{
	ref[repptr++]=0;
	if(repptr==SIZE)
	{
	repptr=0;
	}
	}
	temp=frame[repptr];
	frame[repptr]=ele;
	ref[repptr]=1;//The latest page reference, hence it is set to 1
	return temp;
}
//page fault
int Pagefault(int ele)
{
	if(full!=SIZE)
	{
	ref[full]=1;
	frame[full++]=ele;
	}
	else
	{
	printf("The page replaced is %d",Pagerep(ele));
	}
	}
//search in the frame
	int Search(int ele)
	{
	int i,flag;
	flag=0;
	if(full!=0)
	{
	for(i=0;i<full;i++)
	{
	if(ele==frame[i])
	{
		flag=1;
		ref[i]=1;
		break;
	}
	}
	}
	return flag;
	}
/*
output
-----------------------------------
The number of elements in the reference string are :18
The elements present in the string are
0 4 1 4 2 4 3 4 2 4 0 4 1 4 2 4 3 4


The elements in the frame are
0

The elements in the frame are
0
4

The elements in the frame are
0
4
1
The page replaced is 0
The elements in the frame are
2
4
1
The page replaced is 1
The elements in the frame are
2
4
3
The page replaced is 3
The elements in the frame are
2
4
0
The page replaced is 2
The elements in the frame are
1
4
0
The page replaced is 0
The elements in the frame are
1
4
2
The page replaced is 1
The elements in the frame are
3
4
2

The number of page faults are 9


*/
