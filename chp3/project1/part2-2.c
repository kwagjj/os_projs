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

int show_history_proper(char loglist[HISTORY_LIMIT][MAX_LINE],int *next_replace_index,int *history_count){
	int i;
	int hist_num=*history_count-1;
	int logindex=*next_replace_index+HISTORY_LIMIT-1;

	printf("hist_num: %d, logindex: %d\n",hist_num,logindex);

	for(i=0;i<HISTORY_LIMIT;i++){

		if(hist_num<0){
			break;
		}
		printf("%d: %s\n",hist_num,loglist[logindex%HISTORY_LIMIT]);
		hist_num--;
		logindex--;
	}
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
	char input_buffer[MAX_LINE];
	char *ptr;
	int i,j;
	int runbkg;


	int history_mode=0;
	int next_replace_index=0;
	int history_count=0;
	char loglist[HISTORY_LIMIT][MAX_LINE];

	for(i=0;i<HISTORY_LIMIT;i++){	// reseting loglist
		sprintf(loglist[i],"");
	}


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

		strcpy(input_buffer,input);	// make copy of input for later use with history

		//save input in history log
//		update_history(input,loglist,&next_replace_index,&history_count);
//		printf("next_replace_index: %d, history_count: %d\n",next_replace_index,history_count);
//		show_history(loglist);
//
//
		printf("before input: %s\n",input);
		
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
				history_mode=1;
				printf("history detected\n");
				show_history_proper(loglist,&next_replace_index,&history_count);
			}

			if(strcmp(args[0],"!!")==0){
				history_mode=1;
				// get input value of previous, ptrtok that again, search for keywords again, then fork & execute

			}

			if(strcmp(args[j],"&")==0){	// if & is included, run it in background
				args[j]=NULL;
				runbkg=1;
			}

		}
		
		printf("input buffer: %s\n",input_buffer);	
	

		if(history_mode==1){	// used just for skipping remainder
			history_mode=0;
			continue;	// skip the executing part below since history command is not a proper command
		}

			// history mode will not increment next_replace_index, history_count.


		update_history(input_buffer,loglist,&next_replace_index,&history_count);
//		printf("next_replace_index: %d, history_count: %d\n",next_replace_index,history_count);
//		show_history(loglist);


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
