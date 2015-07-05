#include <stdio.h>
#include <string.h>

#define ARGNUM 10
#define MAX_LINE 80

void split_input(char *input,char *args[ARGNUM]){
	int i;
	char *ptr;
	
	printf("input from split_input: %s\n",input);


	ptr=strtok(input," ");
	while(ptr!=NULL){
		args[i]=ptr;
		ptr=strtok(NULL," ");
		i++;
	}
}

void init_args(char *args[ARGNUM]){
	int i;
	for(i=0;i<ARGNUM;i++){
		args[i]=NULL;
	}
}

int main(void){
	char *args[ARGNUM];
	char input[MAX_LINE];
	int i;

	init_args(args);

	printf("cmd:");
	fgets(input,MAX_LINE,stdin);

	for(i=0;i<MAX_LINE;i++){
		if(input[i]=='\n'){
			input[i]='\0';
		}
	}

	printf("input: %s\n",input);

	split_input(input,args);
	
	printf("finished split\n");

	i=0;
	while(args[i]!=NULL){
		printf("%d %s\n",i,args[i]);
		i++;
	}
	
	return 0;	
}
