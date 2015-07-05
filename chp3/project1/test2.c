#include <stdio.h>
#include <string.h>

int main(void){

	char log[5][100];
	char input[80];

	int i;
	int count;
	printf("00\n");
	for(i=0;i<5;i++){	// initializing process
		sprintf(log[i],"none");
	}

	fgets(input,80,stdin); // get input
	for(i=0;i<80;i++){	// remove newline at the end and replace it with null
		if(input[i]=='\n' || i==79){
			input[i]='\0';
			break;
		}
	}

	count=0;

	strcpy(log[count],input);

	for(i=0;i<5;i++){	// print updated log
		printf("%d %s\n",i,log[i]);	
	}
}
