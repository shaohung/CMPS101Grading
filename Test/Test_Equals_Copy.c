#include<stdio.h>
#include<stdlib.h>
#include "../List.h"
int main(){
	FILE* out;
	out = fopen("Test_Equals_Copy.out", "w");
	if( out==NULL ){
		printf("Unable to write to file\n");
		exit(EXIT_FAILURE);
	}
	List a = newList(), b = newList(), c = newList();
	for(int i = 0; i < 5; i++){
		append(a, i*i);
		append(b, i*i);
		if(i == 2) append(c, 99);
		else append(c, i*i);
	}
	printList(out, a);//0 1 4 9 16 
	printList(out, b);//0 1 4 9 16 

	fprintf(out, "%d\n", equals(a, c));//0
	fprintf(out, "%d\n", equals(a, b));//1
	List q = copyList(a);
	fprintf(out, "%d\n", equals(a, q));//1

	fclose(out);
	freeList(&b);
	freeList(&a);
	freeList(&c);
	freeList(&q);
	return 0;
}
