/****************************************************************************************
*  ListClient.c
*  Test client for List ADT
*****************************************************************************************/

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
#include"../List.h"

void main1(){
	FILE* f;
	f = fopen("ListClient.out", "w");
	if( f==NULL ){
		printf("Unable to write to file\n");
		exit(EXIT_FAILURE);
	}
   List A = newList();
   List B = newList();
   List C = NULL;
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   }

   printList(f,A);
   fprintf(f, "\n");
   printList(f,B);
   fprintf(f, "\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      fprintf(f, "%d ", get(A));
   }
   fprintf(f,"\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      fprintf(f, "%d ", get(B));
   }
   fprintf(f,"\n");

   C = copyList(A);
   fprintf(f,"%s\n", equals(A,B)?"true":"false");
   fprintf(f, "%s\n", equals(B,C)?"true":"false");
   fprintf(f, "%s\n", equals(C,A)?"true":"false");


   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);            // at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); // at index 10
   delete(A);
   printList(f,A);
   fprintf(f,"\n");
   fprintf(f,"%d\n", length(A));
   clear(A);
   fprintf(f,"%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);
	fclose(f);
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
21
0
*/

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
