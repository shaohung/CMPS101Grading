
#include<stdio.h>
#include<stdlib.h>
#include "../List.h"
#include "Test.h"
void main1(){
	FILE* out;
	out = fopen("Test_Clear.out", "w");
	if( out==NULL ){
		printf("Unable to write to file\n");
		exit(EXIT_FAILURE);
	}
	List a = newList();
	append(a, 3);
	printList(out, a);//3
	clear(a);
	printList(out, a);//

	List b = newList();
	prepend(b, 6);
	printList(out, b);//6
	prepend(b, 12);
	printList(out, b);//12 6
	clear(b);
	printList(out, b);//

	List c = newList();
	append(c, 5);
	printList(out, c);//5

	fclose(out);
	freeList(&b);
	freeList(&a);
	freeList(&c);
}

