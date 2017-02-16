
#include<stdio.h>
#include<stdlib.h>
#include "../List.h"
int main(){
	List a = newList();
	freeList(&a);
	return 0;
}
