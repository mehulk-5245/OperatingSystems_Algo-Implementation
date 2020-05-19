
#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#define MAX 25
void *customerf(void *param);
void *barber(void *param);
void *customerm(void *param);
sem_t chairs;
sem_t cust;
sem_t bar;
int no_of_chairs;
int wait;
int counter=0;

int main(){
int runtime=0,custom,i,fcount=0,mcount=0;
int seq[2*MAX];
pthread_t barid;
pthread_t custid[MAX];
printf("\n||---------CUT69 SALON OPEN---------||\n");
printf("\nNo of Customers:");
scanf("%d",&custom);
printf("\nEnter the Sequence of entering shop");
printf("\n<1 for female and 0 for male,with a space> :-");
for(int j = 0; j < custom ; j++){
scanf("%d",&seq[j]);
if(seq[j]==1){
fcount++ ;
}
else{
mcount++ ;
}
}
if(seq[0]==1){
custom = fcount;
}
else{
custom = mcount;
}
runtime = custom*5;
printf("\nRun time: %d ",runtime);
printf("\nNo. of chairs: ");
scanf("%d",&no_of_chairs);
printf("\nWait time: ");
scanf("%d",&wait);
sem_init(&chairs,0,1);
sem_init(&cust,0,0);
sem_init(&bar,0,0);
pthread_create(&barid,NULL,barber,NULL);
printf("\nTHe barber id is %ld\n",barid);
for(i=0;i<custom;i++){
if(seq[0]==1){
printf("\nFemale Customer will be entertained.\n");
pthread_create(&custid[i],NULL,customerf,NULL);
}
else if(seq[0]==0){
printf("\nMale Customer will be entertained.\n");
pthread_create(&custid[i],NULL,customerm,NULL);
}
}
sleep(custom*5);
exit(0);
}
void *barber(void *param){
int time;
while(1){
sem_wait(&cust);
sem_wait(&chairs);
no_of_chairs = no_of_chairs + 1;
printf("\nCustomer %d is having Salon Service.\n",counter);
counter++;
sem_post(&bar);
sem_post(&chairs);
time = 5;
printf("\nBarber takes %d secs ...\n",time);
sleep(time);
}
}
void *customerf(void *param){
printf("\nFemale Customer in....\n");
while(1){
sem_wait(&chairs);
if(no_of_chairs<=0){
sem_post(&chairs);
}
else{
no_of_chairs = no_of_chairs - 1;
sem_post(&cust);
sem_post(&chairs);
sem_wait(&bar);
}
sleep(5);
}
}
void *customerm(void *param){
while(1){
printf("\nMale Customer in....\n");
sem_wait(&chairs);
if(no_of_chairs<=0){
sem_post(&chairs);
}
else{
no_of_chairs = no_of_chairs - 1;
sem_post(&cust);
sem_post(&chairs);
sem_wait(&bar);
}
sleep(5);
}
}
/*
Output->
No of Customers:3

Enter the Sequence of entering shop 
<1 for female and 0 for male,with a space> :-0 0 0

Run time: 15
No. of chairs: 3

Wait time: 2

THe barber id is 140163906901760

Male Customer will be entertained.

Male Customer will be entertained.

Male Customer will be entertained.

Male Customer in....

Male Customer in....

Customer 0 is having Salon Service.

Barber takes 5 secs ...

Male Customer in....

Male Customer in....

Customer 1 is having Salon Service.

Barber takes 5 secs ...

Male Customer in....

Customer 2 is having Salon Service.

Barber takes 5 secs ...
*/
