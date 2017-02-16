#include<stdio.h>
#include<stdlib.h>
#include "../List.h"
int main(){
	FILE* out;
	out = fopen("Test_Insert.out", "w");
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
	return 0;
}
