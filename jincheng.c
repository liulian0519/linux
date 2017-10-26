#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<ctype.h>
#define MAX_CHILD_NUMBER 10
#define SLEEP_INTERVAL 2
int proc_number=0;
void do_something();
main(int argc,char* argv[])
{
	int child_proc_number=MAX_CHILD_NUMBER;
	int i,ch;
	pid_t child_pid;
	pid_t pid[10]={0};
	if(argc>1)
	{
		child_proc_number=atoi(argv[1]);
		child_proc_number=(child_proc_number>10)?10:child_proc_number;
	}
	for(i=0;i<child_proc_number;i++)
	{/**/
		child_pid=fork();
		proc_number=i;
		if(child_pid==0)
		{
			do_something();
		}
		else if(child_pid>0)
		{
			pid[i]=child_pid;
		}
	}
	printf("input the number you want to kill:");
	while((ch=getchar())!='q')
	{
		if(isdigit(ch))
		{
			ch=(int)ch - 48;
			if(kill(pid[ch],SIGKILL)<0)
			{
				perror("kill");
				exit(1);
			}
			else
			{
				printf("process %d has been killed!\n\n",pid[ch]);
			}

		}
		else
		{
			printf("is not digit\n");
		}
		getchar();
		printf("input the number you want to kill:");

	}
	kill(0,SIGTERM);
	return 0;


}
void do_something()
{

	for(;;)
	{
		printf("This is process No.%d and its pid is %d\n",proc_number,getpid());
		sleep(SLEEP_INTERVAL);
	}
}

