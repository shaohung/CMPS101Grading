#if __STDC_VERSION__ >= 199901L
#define _XOPEN_SOURCE 600
#else
#define _XOPEN_SOURCE 500
#endif /* __STDC_VERSION__ */

#include <time.h>
#include <pthread.h>
/* for ETIMEDOUT */
#include <errno.h>
#include <string.h>

#include<stdio.h>
#include<stdlib.h>
#include "../List.h"
void main1(){
	FILE* out;
	out = fopen("Test_Insert_Index.out", "w");
	if( out==NULL ){
		printf("Unable to write to file\n");
		exit(EXIT_FAILURE);
	}
	List a = newList(), b = newList();
	for(int i = 0; i < 5; i++){
		append(a, i*i);
		prepend(b, 2*i*i);
	}
	printList(out, a);//0 1 4 9 16
	printList(out, b);//32 18 8 2 0
	moveFront(a);
	while(index(a)>=0){
		fprintf(out, "%d %d ", index(a), get(a)); // 0 0 1 1 2 4 3 9 4 16
		moveNext(a);
	}
	fprintf(out, "\n");

	moveFront(a);
	fprintf(out, "%d\n", index(a));//0
	insertBefore(a, 99);
	printList(out, a);//99 0 1 4 9 16
	fprintf(out, "%d\n", index(a));//1
	insertAfter(a, 100);
	printList(out, a);//99 0 100 1 4 9 16
	fprintf(out, "%d\n", index(a));//1

	moveBack(b);
	fprintf(out, "%d\n", index(b));//4
	insertBefore(b, 99);
	printList(out, b);//32 18 8 2 99 0
	fprintf(out, "%d\n", index(b));//5
	insertAfter(b, 100);
	printList(out, b);//32 18 8 2 99 0 100
	fprintf(out, "%d\n", index(b));//5

	moveFront(a);moveNext(a);moveNext(a);
	insertBefore(a, 49);
	insertAfter(a, 50);
	printList(out, a); // 99 0 49 100 50 1 4 9 16
	fprintf(out, "%d\n", index(a));//3

	fclose(out);
	freeList(&b);
	freeList(&a);
}

pthread_mutex_t calculating = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t done = PTHREAD_COND_INITIALIZER;

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
