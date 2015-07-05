#include <stdio.h>
#include <string.h>

int main(void){
	char *arr1[5];

	printf("size: %d\n",sizeof(arr1[0]));

	int i;
	for(i=0;i<5;i++){
		printf("%d: value contained:%d\n",i,arr1[i]);
	}
	char*	tempstr="tempstr";
	printf("ptr of tempstr: %d\n",tempstr);
	arr1[0]=tempstr;
	arr1[1]="string2";

	printf("addr of arr1[i]: %d , value contained: %d, string value:%s\n",&arr1[0],arr1[0],arr1[0]);

	return 0;
}
