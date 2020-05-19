#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
struct mesgq
{
	long type;
	char text[200];
}mq;

void main()
{
	int msgid5,len;
	key_t key5=1004;
	if((msgid5=msgget(key5,0644))==-1)
	{
		printf("server not active\n");
		exit(1);
	}
	printf("client 5 is ready:\n");
	while(msgrcv(msgid5,&mq,sizeof(mq.text),1,0)!=-1)
	{
		printf("from server :\"%s\"\n",mq.text);
		fgets(mq.text,sizeof(mq.text),stdin);
		len=strlen(mq.text);
		if(mq.text[len-1]=='\n')
		{
			mq.text[len-1]=='\0';
		}
		msgsnd(msgid5,&mq,len+1,0);
	}
	printf("server disconnected\n");
}

