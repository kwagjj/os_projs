#include <stdio.h>
#include <string.h>


int update_history(char *input,char log[5][100],int *count,int *next_index){

	strcpy(log[*next_index],input);
	*count=*count+1;
	*next_index=*next_index+1;
	return 0;
}

int main(void){

	char log[5][100];
	char input[80];

	int i;
	int count,next_index;
	count=0;
	next_index=0;
	printf("00\n");
	for(i=0;i<5;i++){	// initializing process
		sprintf(log[i],"none");
	}
	while(1){
		printf("cmd:");
		fgets(input,80,stdin); // get input
		for(i=0;i<80;i++){	// remove newline at the end and replace it with null
			if(input[i]=='\n' || i==79){
				input[i]='\0';
				break;
			}
		}

		update_history(input,log,&count,&next_index);

		for(i=0;i<5;i++){	// print updated log
			printf("%d %s\n",i,log[i]);	
		}

		if(next_index>=5){
			next_index=0;
		}

	}
}
