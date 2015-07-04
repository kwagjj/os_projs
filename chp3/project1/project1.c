#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>


#define MAX_LINE 80


int main(void){
	char *args[MAX_LINE/2+1];
	int should_run=1;
	char input[MAX_LINE];
	char *ptr;
	int i,j;
	int runbkg;
	while(should_run){
		runbkg=0;

		
		printf("osh>");
		//fflush(stdout);	
		gets(input);
		
		ptr=strtok(input," ");
		i=0;
		while(ptr!=NULL){
			args[i]=ptr;
			ptr=strtok(NULL," ");
			i++;
		}

		for(j=0;j<i;j++){
			if(strcmp(args[j],"exit")==0){
				return 0;
			}

			if(strcmp(args[j],"&")==0){
				args[j]=NULL;
				runbkg=1;
			}

		}

	i=0;
	while(args[i]!=NULL){
		printf("%d %s\n",i,args[i]);
		i++;
	}

	pid_t pid;
	pid=fork();
	if(pid<0){
		printf("error\n");
	}
	else if(pid==0){
		execvp(args[0],args);
		return 0;
	}
	else{
		printf("runbkg: %d\n",runbkg);
		printf("child pid:%d \n",pid);
		int status;
		if(runbkg==0){	
			waitpid(pid,&status,0);
			printf("wait executed\n");
		}
		i=0;
		while(args[i]!=NULL){
			printf("%d %s\n",i,args[i]);
			args[i]=NULL;
			i++;
		}
	}


	} // end of should run

	return 0;
}
