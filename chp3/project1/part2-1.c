// purpose is to add history feature 
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>


#define MAX_LINE 80
#define ARGNUM MAX_LINE/2+1
#define HISTORY_LIMIT 10



int show_history(char loglist[HISTORY_LIMIT][MAX_LINE]){

	int i;
	for(i=0;i<HISTORY_LIMIT;i++){
		printf("%d: %d %s\n",i,loglist[i],loglist[i]);
	}

	return 0;
	
}

int update_history(char *input,char loglist[HISTORY_LIMIT][MAX_LINE],int *next_replace_index,int *history_count){
	printf("starting update_history\n");
	printf("addr of loglist: %d\n",loglist);
	printf("next_replace_index: %d\n",*next_replace_index);
	printf("value of loglist[i]: %d\n",loglist[*next_replace_index]);
	strcpy(loglist[*next_replace_index],input);
	*next_replace_index=*next_replace_index+1;
	if(*next_replace_index>=HISTORY_LIMIT){
		*next_replace_index=0;
	}
	*history_count=*history_count+1;

	return 0;

}

int main(void){
	char *args[ARGNUM];
	int should_run=1;
	char input[MAX_LINE];
	char *ptr;
	int i,j;
	int runbkg;


	int next_replace_index=0;
	int history_count=0;
	char loglist[HISTORY_LIMIT][MAX_LINE];

//	for(i=0;i<HISTORY_LIMIT;i++){
//		sprintf(loglist[i],"none");
//	}


	while(should_run){
		runbkg=0;
		
		// reset args array
		for(i=0;i<ARGNUM;i++){
			args[i]=NULL;
		}
		
		printf("osh>");
		//fflush(stdout);	
		fgets(input,MAX_LINE,stdin);	// get input. enter(\n) value will be included.


		// removing last newline and replace it with null
		for(i=0;i<ARGNUM;i++){
			if(input[i]=='\n'){
				input[i]='\0';
				break;
			}
		}

		//save input in history log
		update_history(input,loglist,&next_replace_index,&history_count);
		printf("next_replace_index: %d, history_count: %d\n",next_replace_index,history_count);
		show_history(loglist);

		
		ptr=strtok(input," "); // strip input with delimiter
		i=0;
		while(ptr!=NULL){		// convert input to args elements
			args[i]=ptr;
			ptr=strtok(NULL," ");
			i++;
		}

		int k;
		// print all args values
//		for(k=0;k<i;k++){
//			printf("%s\n",args[k]);
//		}
//		printf("searching for exit\n");
		for(j=0;j<i;j++){	// serach for keywords in arguments.
//			printf("j:%d str:%s\n",j,args[j]);
			if(strcmp(args[j],"exit")==0){
				return 0;
			}

			if(strcmp(args[0],"history")==0){
				printf("history detected\n");
			}

			if(strcmp(args[j],"&")==0){	// if & is included, run it in background
				args[j]=NULL;
				runbkg=1;
			}

		}

	i=0;
//	printf("args listing with null ending\n");
//	while(args[i]!=NULL){	// print all args values
//		printf("%d %s\n",i,args[i]);
//		i++;
//	}
//
	pid_t pid;
	pid=fork();		// forking
	if(pid<0){
		printf("error\n");
	}
	else if(pid==0){ //child process
//		printf("child-args: %s\n",args[0]);
		execvp(args[0],args);
		return 0;
	}
	else{	// parent process
//		printf("runbkg: %d\n",runbkg);
//		printf("child pid:%d \n",pid);
		int status;
		if(runbkg==0){	
			waitpid(pid,&status,0);
//			printf("wait executed\n");
		}

		// checking args values at the end.
//		i=0;
//		while(args[i]!=NULL){
//			printf("%d %s\n",i,args[i]);
//			args[i]=NULL;
//			i++;
//		}
	}


	} // end of should run

	return 0;
}
