/**
	Author: Farhang Nemati
*/

#include <time.h>
#include <pthread.h>
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define TOTAL_MSG 100
#define QUEUE_NAME "/myqueue"
#define MAX_MSG_NUM 10
#define MAX_MSG_SIZE 20

void * task1(void *args)
{
	mqd_t q1;
	struct mq_attr q1Attr;	
	char message[MAX_MSG_SIZE - 1];
	int msgs = 0;
	struct timespec ts1, ts2;
	
	q1Attr.mq_msgsize = MAX_MSG_SIZE;
	q1Attr.mq_maxmsg = MAX_MSG_NUM;
	
	ts1.tv_sec = 0;
	ts1.tv_nsec = 100000000;
	
	q1 = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0700, &q1Attr);
	if (q1 == -1)
	{
		printf("Task1 couldn't create/open the queue, error: %d\n", errno);
		exit(1);
	}
	
	while (msgs++ != TOTAL_MSG)
	{	
		sprintf(message, "%d", msgs);
		
		if (mq_send(q1, message, strlen(message), 0) < 0)
		{
			printf("Task1 couldn't send the message, error: %d\n", errno);
			mq_close(q1);
			exit(1);
		}
		
		nanosleep(&ts1, &ts2);
	}
	
	strcpy(message, "STOP");
	if (mq_send(q1, message, strlen(message), 0) < 0)
	{
		printf("Task1 couldn't send the message, error: %d\n", errno);
		mq_close(q1);
		exit(1);
	}
	
	mq_close(q1);
}

void * task2(void *args)
{
	mqd_t q2;
	struct mq_attr q1Attr;
	char message[MAX_MSG_SIZE + 1] = "";
	struct timespec ts1, ts2;
	unsigned int prio;
		
	q1Attr.mq_msgsize = MAX_MSG_SIZE;
	q1Attr.mq_maxmsg = MAX_MSG_NUM;
	
	ts1.tv_sec = 0;
	ts1.tv_nsec = 50000000;
	
	q2 = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0700, &q1Attr);
	if (q2 == -1)
	{
		printf("Task2 couldn't open the queue, error: %d\n", errno);
		exit(1);
	}
	
	while (1)
	{	
		if (mq_receive(q2, message, MAX_MSG_SIZE, &prio) < 0)
		{
			printf("Task2 couldn't receive the message %d\n", errno);
			mq_close(q2);
			exit(1);
		}
		
		printf("Received message: %s\n", message);
		
		if (strcmp(message, "STOP") == 0)
		{
			printf("Received Stop Message\n");
			mq_close(q2);
			break;
		}

		nanosleep(&ts1, &ts2);
	}
}

int main(int argc, char *argv[])
{
	pthread_t thread1, thread2;
	
	mq_unlink(QUEUE_NAME);
	
	pthread_create(&thread1, NULL, task1, NULL);
	pthread_create(&thread2, NULL, task2, NULL);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	mq_unlink(QUEUE_NAME);	
	
	return 0;
}