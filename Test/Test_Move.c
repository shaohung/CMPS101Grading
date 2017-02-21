#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */

#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

#include<stdio.h>
#include<stdlib.h>
#include "../List.h"

pthread_mutex_t calculating = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t done = PTHREAD_COND_INITIALIZER;

void main1(){
	FILE* out;
	out = fopen("Test_Move.out", "w");
	if( out==NULL ){
		printf("Unable to write to file\n");
		exit(EXIT_FAILURE);
	}
	List a = newList();
	for(int i = 0; i < 5; i++){
		append(a, i);
	}
	printList(out, a);// 0 1 2 3 4
	moveFront(a);
	while(index(a)>-1){
		fprintf(out, "%d ", get(a)); //0 1 2 3 4
		moveNext(a);
	}
	fprintf(out, "\n");

	moveBack(a);
	while(index(a)>-1){
		fprintf(out, "%d ", get(a)); //4 3 2 1 0
		movePrev(a);
	}
	fprintf(out, "\n");

	List b = newList();
	for(int i = 0; i < 5; i++){
		prepend(b, i);
	}
	printList(out, b);// 4 3 2 1 0
	moveFront(b);
	while(index(b)>-1){
		fprintf(out, "%d ", get(b));//4 3 2 1 0
		moveNext(b);
	}
	fprintf(out, "\n");

	moveBack(b);
	while(index(b)>-1){
		fprintf(out, "%d ", get(b));//0 1 2 3 4
		movePrev(b);
	}

	fclose(out);
	freeList(&a);
	freeList(&b);
	//return 0;
}

void *expensive_call(void *data)
{
        int oldtype;

        /* allow the thread to be killed at any time */
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &oldtype);

        /* ... calculations and expensive io here, for example:
         * infinitely loop
         */
        main1();

        /* wake up the caller if we've completed in time */
        pthread_cond_signal(&done);
        return NULL;
}

/* note: this is not thread safe as it uses a global condition/mutex */
int do_or_timeout(struct timespec *max_wait)
{
        struct timespec abs_time;
        pthread_t tid;
        int err;

        pthread_mutex_lock(&calculating);

        /* pthread cond_timedwait expects an absolute time to wait until */
        clock_gettime(CLOCK_REALTIME, &abs_time);
        abs_time.tv_sec += max_wait->tv_sec;
        abs_time.tv_nsec += max_wait->tv_nsec;

        pthread_create(&tid, NULL, expensive_call, NULL);

        /* pthread_cond_timedwait can return spuriously: this should
         * be in a loop for production code
         */
        err = pthread_cond_timedwait(&done, &calculating, &abs_time);

        if (err == ETIMEDOUT)
                fprintf(stderr, "%s: calculation timed out\n", __func__);

        if (!err)
                pthread_mutex_unlock(&calculating);

        return err;
}

int main()
{
        struct timespec max_wait;

        memset(&max_wait, 0, sizeof(max_wait));

        /* wait at most 2 seconds */
        max_wait.tv_sec = 2;
        do_or_timeout(&max_wait);

        return 0;
}
