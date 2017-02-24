

#include<stdio.h>
#include<stdlib.h>
#include "../List.h"
#include "Test.h"
void main1(){
	FILE* out;
	out = fopen("Test_Append.out", "w");
	if( out==NULL ){
		printf("Unable to write to file\n");
		exit(EXIT_FAILURE);
	}
	List a = newList();
	append(a, 3);
	printList(out, a);//3
	append(a, 4);
	printList(out, a);//3 4
	fclose(out);
	freeList(&a);
}

