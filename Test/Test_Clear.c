
#include<stdio.h>
#include<stdlib.h>
#include "../List.h"
int main(){
	FILE* out;
	out = fopen("Test_Clear.out", "w");
	if( out==NULL ){
		printf("Unable to write to file\n");
		exit(EXIT_FAILURE);
	}
	List a = newList();
	append(a, 3);
	printList(out, a);
	clear(a);
	printList(out, a);

	List b = newList();
	prepend(b, 6);
	printList(out, b);
	prepend(b, 12);
	printList(out, b);
	clear(b);
	printList(out, b);

	List c = newList();
	append(c, 5);
	printList(out, a);

	fclose(out);
	freeList(&b);
	freeList(&a);
	freeList(&c);
	return 0;
}
