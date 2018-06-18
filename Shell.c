#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "signal.h"
#include "unistd.h"

void executer(char *);
char** parser (char *);
void in_out_Mess(char *); 

int main(int ac, char* arg[])
{
	char user_input[300];
	while(1)
	{
		in_out_Mess(user_input);
		executer(user_input);		
	}
	perror("Error ");
};

void in_out_Mess(char * user_input)
{
	int pid;
	pid = getpid();
	printf("Pid ID:%d \n sh:");
	fgets(user_input,300,stdin);
	user_input[strlen(user_input)-1] = '\0';
	if(strcmp(user_input, "END") == 0)
	exit(0);
}
void executer(char *string)
{
	char **arg = parser(string);
	int ifork;
	int stat;
	int i = 0;
	ifork = fork();
	if(ifork == -1)
	{
		perror("Fork Failure\n");
		exit(1);
	}
	if(ifork == 0)
	{
		execvp(arg[0],arg);
		perror("Execute Failure\n");
		exit(2);
	}
	else
	{
		wait(&stat);
		free(arg);
	}
}
char** parser(char *string)	
{
	char ** arg = malloc(300);
	int i = 0;
	arg[i] = strtok(string, " ");
	while(arg[i])
	{
		i++;
		arg[i] = strtok(NULL," ");
	}
	return arg;
}
