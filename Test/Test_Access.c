
#include<stdio.h>
#include<stdlib.h>
#include "../List.h"
int main(){
	FILE* out;
	out = fopen("Test_Access.out", "w");
	if( out==NULL ){
		printf("Unable to write to file\n");
		exit(EXIT_FAILURE);
	}
	List a = newList();
	append(a, 3);
	printList(out, a); fprintf(out, "\n");
	prepend(a, 4);
	printList(out, a); fprintf(out ,"\n");
	fprintf("%d\n", length(a));
	append(a, 5);
	printList(out, a); 	fprintf(out, "\n");
	fprintf("%d\n", length(a));
	fprintf("%d\n", front(a));
	fprintf("%d\n", back(a));

	fclose(out);
	freeList(&a);
	return 0;
}
