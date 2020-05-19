
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    int choice,fd,n,temp0,l;
    int i=0;
    char x;
    char tt2[50];
    char fname[50];
    char buf[50],chars[100];
  
    do {
    printf("Choose:\n");
    printf("1.create\n2.open\n3.close\n4.write\n5.read\n");
	printf("6.unlink\n7.readIn_reverse\n8.Resource allocation\n");
	printf("9.Exit\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:printf("Enter filename:");
               scanf("%s",fname);              
               fd=creat(fname,0777);
               if(fd==-1)
               {
                printf("Error");
               }
               else
               {
                printf("Created\n");
               } 
	       printf("\nfd=%d\n",fd);
               close(fd);
               break;
        case 2:printf("Enter filename:");
               scanf("%s",fname); 
               fd=open(fname,O_RDONLY,0777);
               if(fd==-1)
               {
                printf("Error");
               }
               else
               {
                printf("Exists\n");
               }
	       printf("\nfd=%d\n",fd);
               close(fd); 
               break;
       case 3: printf("Enter filename:");
               scanf("%s",fname);
	       fd=open(fname,O_RDONLY,0777);
 	       close(fd);
	       printf("\nfd=%d\n",fd);
	       printf("File closed\n");
	       break;
       case 5: printf("Enter filename:");
               scanf("%s",fname); 
               fd=open(fname,O_RDONLY,0777);
               fd=read(fd,buf,5);
               printf("%s",buf);
	       printf("\nfd=%d\n",fd);
               close(fd);
               break;  
       case 4: printf("Enter filename:");
               scanf("%s",fname); 
               fd=open(fname,O_RDWR,0777); 
	       if(fd==-1){
		 printf("Error\n");
               }
		else{
                  printf("fd=%d\n",fd);
                  printf("Enter string:");
               scanf("%s",chars);
		printf("Enter no. of characters to overwrite:\n");
		scanf("%d",&l);
		fd=write(fd,chars,l);
		}
               close(fd);
               break;
       
       case 6: printf("Enter filename:");
               scanf("%s",fname);
	       fd=unlink(fname);
	       printf("\nfd=%d\n",fd);
               printf("Content can't be read since file is deleted\n");
	       if(fd==-1){
		   printf("File doesn't exist\n");
		}
	       break;
	       
       case 8:temp0=getpid();
	      printf("%d",temp0);
	      sprintf(tt2,"ls /proc/%d/fd",temp0);
	      system(tt2);
              printf("\nfd=%d\n",fd);
	      break;        
       case 7: printf("Enter filename:");
               scanf("%s",fname); 
               fd=open(fname,O_RDONLY,0777);
	        
		lseek(fd,0,0);
               n=lseek(fd,0,2);
               printf("bytes=%d\n",n);
	       for(i=1;i<=n;i++){
		   lseek(fd,-i,2);
		   read(fd,&x,1);
		   printf("%c",x);
		}
		printf("\nfd=%d\n",fd);
	       
               break;
       case 9:printf("Exitted\n");
	      break;
        
                
      } 
    }while(choice!=9); 
return 0;                       
    }
/*
Output
Choose:
1.create
2.open
3.close
4.write
5.read
6.unlink
7.readIn_reverse
8.Resource allocation
9.Exit
1
Enter filename:ost.txt
Created

fd=3
Choose:
1.create
2.open
3.close
4.write
5.read
6.unlink
7.readIn_reverse
8.Resource allocation
9.Exit
4
Enter filename:ost.txt
fd=3
Enter string:welcomel
Enter no. of characters to overwrite:
7
Choose:
1.create
2.open
3.close
4.write
5.read
6.unlink
7.readIn_reverse
8.Resource allocation
9.Exit
7
Enter filename:ost.txt
bytes=7
emoclew
fd=4
Choose:
1.create
2.open
3.close
4.write
5.read
6.unlink
7.readIn_reverse
8.Resource allocation
9.Exit
8
0  1  2  3  4
4027
fd=4
Choose:
1.create
2.open
3.close
4.write
5.read
6.unlink
7.readIn_reverse
8.Resource allocation
9.Exit
6
Enter filename:ost.txt

fd=0
Content can't be read since file is deleted
Choose:
1.create
2.open
3.close
4.write
5.read
6.unlink
7.readIn_reverse
8.Resource allocation
9.Exit
9
Exitted

*/

