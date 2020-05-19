#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<linux/unistd.h>
#include<sys/syscall.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
int sum=0,sum1;
void *runner(void *param);
int main(int argc,char *argv[])
{
	pthread_t threads[2];
	pthread_attr_t attr1;
	
	pthread_attr_t attr2;
	int mid=argc/2;
	if(argc!=2)
	{
		fprintf(stderr,"usage: a.out<integer value>\n");
		return -1;
	}
	if(atoi(argv[1])<0)
	{
		fprintf(stderr,"%d must be >=0\n",atoi(argv[1]));
		return -1;
	}
	pthread_attr_init(&attr1);
	pthread_create(&threads[0],&attr1,runner,argv[1]);
	pthread_join(threads[0],NULL);
	printf("Sum of first half is %d\n",sum);
	sum1=sum;
	
	pthread_attr_init(&attr2);
	pthread_create(&threads[1],&attr2,runner,argv[1]);
	pthread_join(threads[1],NULL);
	printf("Sum of second half is %d\n",sum);
	printf("TOtal sum is %d\n",sum1+sum);
}
void *runner(void * param)
{
	int i,upper=atoi(param);
	if(sum==0)
	{
		for(i=1;i<=upper/2;i++)
		{
			sum=sum+i;
		}
		//printf("thread id is %d\n",syscall(__NR_gettid ));
	}
	else
	{
		sum=0;
		for(i=upper/2+1;i<=upper;i++)
		{
			sum=sum+i;
		}
		//printf("thread id is %d\n",syscall(__NR_gettid ));
	}
	pthread_exit(0);
		
}
