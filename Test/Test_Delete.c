#include<stdio.h>
#include<stdlib.h>
#include "../List.h"
int main(){
	FILE* out;
	out = fopen("Test_Delete.out", "w");
	if( out==NULL ){
		printf("Unable to write to file\n");
		exit(EXIT_FAILURE);
	}
	List a = newList(), b = newList();
	for(int i = 0; i < 5; i++){
		append(a, i*i);
		prepend(b, i*i);
	}
	printList(out, a);//0 1 4 9 16 
	printList(out, b);//16 9 4 1 0

	for(int i = 0; i < 5; i++){
		deleteFront(a);
		printList(out, a);//1 4 9 16 
						//4 9 16 
						//9 16 
						//16 
						//
	}
	fprintf(out, "\n");

	for(int i = 0; i < 5; i++){
		deleteBack(b);
		printList(out, b);//16 9 4 1
						// 16 9 4
						// 16 9
						// 16
						//
	}
	fprintf(out, "\n");

	for(int i = 0; i < 5; i++){
		append(a, i*i);
		prepend(b, i*i);
	}
	printList(out, a);//0 1 4 9 16 
	printList(out, b);//16 9 4 1 0
	moveFront(a); moveNext(a); moveNext(a);
	delete(a);
	fprintf(out, "%d\n", index(a));//-1
	printList(out, a);//0 1 9 16 
	moveFront(b);
	delete(b);
	printList(out, b);//9 4 1 0
	moveBack(b);
	delete(b);
	printList(out, b);//9 4 1

	fclose(out);
	freeList(&b);
	freeList(&a);
	return 0;
}
