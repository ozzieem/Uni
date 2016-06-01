#define _GNU_SOURCE 
#include <pthread.h>

void *func(void *arg)
{
	pthread_t myId = pthread_self();
	char threadName[15];

	pthread_getname_np(myId, threadName, 15);

	while (1) {
		printf("Thread %s is running\n", threadName);

		usleep(100000);
	}
}

int main(int argc, char *argv [])
{
	pthread_t t1, t2, t3;
	pthread_attr_t t1Attr, t2Attr, t3Attr;
	cpu_set_t t1cpus, t2cpus, t3cpus;
    
	CPU_ZERO(&t1cpus);
	CPU_SET(0, &t1cpus);
	
	CPU_ZERO(&t2cpus);
	CPU_SET(1, &t2cpus);

	CPU_ZERO(&t2cpus);
	CPU_SET(0, &t3cpus);
	CPU_SET(1, &t3cpus);

	pthread_attr_setaffinity_np(&t1Attr, sizeof(cpu_set_t), &t1cpus);
	pthread_attr_setaffinity_np(&t2Attr, sizeof(cpu_set_t), &t2cpus);
	pthread_attr_setaffinity_np(&t3Attr, sizeof(cpu_set_t), &t3cpus);

	pthread_create(&t1, &t1Attr, func, NULL);
	pthread_setname_np(t1, "thread1");

	pthread_create(&t2, &t2Attr, func, NULL);
	pthread_setname_np(t2, "thread2");

	pthread_create(&t3, &t3Attr, func, NULL);
	pthread_setname_np(t3, "thread3");

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
}