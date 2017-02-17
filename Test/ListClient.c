/****************************************************************************************
*  ListClient.c
*  Test client for List ADT
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"../List.h"

int main(int argc, char* argv[]){
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
   return(0);
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
