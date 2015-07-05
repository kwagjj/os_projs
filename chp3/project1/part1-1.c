#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>


#define MAX_LINE 80
#define ARGNUM MAX_LINE/2+1


int main(void){
	char *args[ARGNUM];
	int should_run=1;
	char input[MAX_LINE];
	char *ptr;
	int i,j;
	int runbkg;
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
		for(j=0;j<i;j++){	// serach for exit and end program
//			printf("j:%d str:%s\n",j,args[j]);
			if(strcmp(args[j],"exit")==0){
				return 0;
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
