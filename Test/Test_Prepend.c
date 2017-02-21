
#include<stdio.h>
#include<stdlib.h>
#include "../List.h"
int main(){
	FILE* out;
	out = fopen("Test_Prepend.out", "w");
	if( out==NULL ){
		printf("Unable to write to file\n");
		exit(EXIT_FAILURE);
	}
	List a = newList();
	append(a, 3);
	printList(out, a);//3
	prepend(a, 4);
	printList(out, a);//4 3
	List b = newList();
	prepend(b, 6);
	printList(out, b);//6
	prepend(b, 12);
	printList(out, b);// 12 6
	fclose(out);
	freeList(&b);
	freeList(&a);
	return 0;
}
