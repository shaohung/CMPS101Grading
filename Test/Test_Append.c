
#include<stdio.h>
#include<stdlib.h>
#include "../List.h"
int main(){
	FILE* out;
	out = fopen("Test_Append.out", "w");
	if( out==NULL ){
		printf("Unable to write to file\n");
		exit(EXIT_FAILURE);
	}
	List a = newList();
	append(a, 3);
	printList(out, a);
	fprintf(out, "\n");
	fprintf(out, "\n");
	append(a, 4);
	printList(out, a);
	fclose(out);
	freeList(&a);
	return 0;
}
