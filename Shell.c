#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<fcntl.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
//#include <editline/readline.h>

#define MAXLIST 100
#define RED printf("\033[1;31m");
#define RESET printf("\033[0m");
#define GREEN printf("\033[1;32m");
#define YELOW printf("\033[1;33m");
#define BLUE printf("\033[1;34m");
#define clear() printf("\033[H\033[J")

void sigintHandler(int sig_num)
{
	signal(SIGINT, sigintHandler); 
}

void sighandler(int sig_num) 
{
    signal(SIGTSTP, sighandler); 
} 

void init_myshell()
{
	clear();
	BLUE
	printf("\n\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
	RED
	// printf("\t\tWelcome to MyShell\n");
	// printf("\t\tMade by:Aditya Bandal");
	printf("\n __  __           ____    _              _   _ \n");
	printf("|  \\/  |  _   _  / ___|  | |__     ___  | | | |\n");
	printf("| |\\/| | | | | | \\___ \\  | '_ \\   / _ \\ | | | |\n");
	printf("| |  | | | |_| |  ___) | | | | | |  __/ | | | |\n");
	//printf("| |  | | | |_| |  ___) | | | | | |  __/ | | | |\n");
	printf("|_|  |_|  \\__, | |____/  |_| |_|  \\___| |_| |_|\n");
	printf("          |___/                                \n");
	BLUE
	printf("\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
	printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n");
	RESET
	// char* uname;
	// uname=getenv("User");
	// printf("\n User:  %s",uname);
	// printf("wdd");
	sleep(2);
	clear();
}
void printDir() 
{ 
    char cwd[1024]; 
    
    char *host=getenv("HOSTNAME");
    char* username = getenv("USER"); 
    GREEN
    printf("%s@%s", username,host);
    YELOW
    getcwd(cwd, sizeof(cwd)); 
    printf(" :\t%s$", cwd);
    RESET 
    //printf(""); 
} 
int takeInput(char *str)
{
	char *buf;
	BLUE
	printf("\n\tThy Command, Our Dearest Lord >>>");
	RESET
	buf=readline(" ");
	if(strlen(buf)!=0)
	{
		strcpy(str,buf);
		return 0;
	}
	else{
		return 1;
	}
}
void parseSpace(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, " "); 
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 
} 
int parselt(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, "<"); 
  
        if (parsed[i] == NULL) 
            break;
    }
    if (parsed[1] == NULL) 
        return 0; // returns zero if no < is found. 
    else { 
        return 1; 
    } 
} 
int parsegt(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, ">"); 
  
        if (parsed[i] == NULL) 
            break;
    } 
    if (parsed[1] == NULL) 
        return 0; // returns zero if no > is found. 
    else { 
        return 1; 
    } 
} 
int parsedand(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, "&&"); 
  
        if (parsed[i] == NULL) 
            break;
    } 
    if (parsed[1] == NULL) 
        return 0; // returns zero if no && is found. 
    else { 
        return 1; 
    } 
}
int parsetand(char* str, char** parsed) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, "###"); 
  
        if (parsed[i] == NULL) 
            break;
    } 
    if (parsed[1] == NULL) 
        return 0; // returns zero if no &&& is found. 
    else { 
        return 1; 
    } 
}
int parse(char* str, char** parsed,char *sp) 
{ 
    int i; 
  
    for (i = 0; i < MAXLIST; i++) { 
        parsed[i] = strsep(&str, sp); 
  
        if (parsed[i] == NULL) 
            break;
    } 
    if (parsed[1] == NULL) 
        return 0; // returns zero if no &&& is found. 
    else { 
        return 1; 
    } 
} 
int run_cmd(char *str)
{
	char *spCmd[MAXLIST];
	if(strcmp(str," ")==0)
	{
		return 0;
	}
	parseSpace(str,spCmd);
	int rc=fork();
	if(rc<0)
	{
		printf("process failed!\n");
	}
	else if(rc==0)
	{
		if(strcmp(spCmd[0],"cd")==0)
		{
			if(chdir(spCmd[1]))
			{
				if(spCmd[1]==NULL)
				{
					chdir("/home/aditya");
					//exit(0);
				}
				else
				{
					RED
					printf("Error!\n");
					RESET
					exit(0);
				}
				//exit(0);
			}
		}
		else{
			if(execvp(spCmd[0],spCmd)==-1)
			{
				RED
				printf("Shell: Incorrect command\n");
				RESET
				exit(0);
			}
		}
		
	}
	else{
		waitpid(rc,NULL,0);
		return 1;
		//sleep(1);
	}
	return 1;
}
int executedand(char **parsed)
{
	//printf("&&&\n");
	int rc=1;
	int pid[MAXLIST];
	int i,j;
	for(i=0;parsed[i]!=NULL && rc!=0;i++)
	{
		rc=pid[i]=fork();
		if(rc<0)
		{
			printf("Failed to create child in function executetand\n");
			exit(0);
		}
		else if(rc==0)
		{
			//printf("%d===\n", i);
			run_cmd(parsed[i]);
			exit(0);   /////???????????????
		}
		else
		{
			wait(NULL);
			//printf("im parent %d\n",i );

		}
	}
	
	return 1;
}
int executetand(char **parsed)
{
	//printf("&&\n");
	int rc=1;
	int pid[MAXLIST];
	int i,j;
	for(i=0;parsed[i]!=NULL && rc!=0;i++)
	{
		rc=pid[i]=fork();
		if(rc<0)
		{
			printf("Failed to create child in function executetand\n");
			exit(0);
		}
		else if(rc==0)
		{
			//printf("%d===\n", i);
			run_cmd(parsed[i]);
			exit(0);   /////???????????????
		}
		// else
		// {
		// 	//wait(NULL);
		// 	//printf("im parent %d\n",i );

		// }
	}
	for(j=0;j<i;j++)
	{
		waitpid(pid[j],NULL,0);
	}
	return 1;
}
int executelt(char *str1,char *str2)
{
	//printf("<\n");
	int rc=fork(),fd;
	if(rc==0)
	{
		close(0);
		fd=open(str2,O_RDONLY,0666);
		run_cmd(str1);
		close(fd);
		exit(0);
	}
	else{
		waitpid(rc,NULL,0);
	}
	
	return 1;
}
int executegt(char *str1,char *str2)
{
	//printf(">\n");
	int rc=fork(),fd;
	if(rc==0)
	{
		close(1);
		fd=open(str2,O_WRONLY | O_APPEND | O_CREAT,0666);
		run_cmd(str1);
		close(fd);
		exit(0);
	}
	else{
		waitpid(rc,NULL,0);
	}
	return 1;
}

int execute(char *str)
{
	if(strcmp(str,"exit")==0)
	{
		return 0;
	}
	char  *split[MAXLIST];
	int x=parsetand(str,split);
	if(x)
	{
		executetand(split);
	}
	else if(x=parsedand(str,split))
	{
		executedand(split);
	}
	else if(x=parse(str,split,">"))
	{
		executegt(split[0],split[1]);
	}
	else if(x=parse(str,split,"<"))
	{
		executelt(split[0],split[1]);
	}
	else
	{
		run_cmd(str);
	}
	return 1;
}
int main()
{
	signal(SIGTSTP, sighandler);
	signal(SIGINT, sigintHandler);
	char input[100];
	init_myshell();
	int x;
	while(1)
	{
		printDir();
		if(takeInput(input))
		{
			continue;
		}
		x=execute(input);
		if(!x)
		{
			break;
		}
	}
	return 0;
}
