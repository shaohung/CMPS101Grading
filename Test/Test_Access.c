
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
	printList(out, a); fprintf(out, "\n"); //3
	prepend(a, 4);
	printList(out, a); fprintf(out ,"\n");//4 3
	fprintf(out, "%d\n", length(a));
	append(a, 5);
	printList(out, a); 	fprintf(out, "\n");//4 3 5
	fprintf(out, "%d\n", length(a)); //3
	fprintf(out, "%d\n", front(a)); // 4
	fprintf(out, "%d\n", back(a));//5

	fclose(out);
	freeList(&a);
	return 0;
}
