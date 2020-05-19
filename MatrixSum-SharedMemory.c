#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<sys/stat.h>
int main(){
	int r,c,i,j,sum=0,sum1=0;
	char *shared_memory;
	printf("Enter no. of rows:\n");
	scanf("%d",&r);
	printf("Enter no. of cols:\n");
	scanf("%d",&c);
	int arr[r][c];
	for(i=0;i<r;++i){
		for(j=0;j<c;++j){	
			printf("Enter the value:");
			scanf("%d",& arr[i][j]);
			}
			}
	int segment_id= shmget(IPC_PRIVATE,r*c*sizeof(int),IPC_CREAT|
	SHM_R|SHM_W);
	int *row=shmat(segment_id,NULL,0);
	if(row<(int*)NULL){
	perror("shmat");
	return 1;
	}
	for(i=0;i<r;++i){
	if(!fork()){
		for(j=row[i]=0;j<c;++j){
			row[i]+=arr[i][j];
		}
		printf("Child process id :%d\n",getpid());	
    	return 0;
	}}
	for(i=0;i<r;++i){
		wait(&j);
		}
		for(i=sum1=0;i<r;++i){
			sum1+=row[i];
		}
		printf("Parent process id :%d\n",getpid());	
		printf("Total sum:%d\n",sum1);	
	return 0;
}
