#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(void)
{
	pid_t pid;
	int i=5;
	pid=fork();
	switch(pid){
		case 0:
			while(i--){
				printf("A background process,PID:%d\n,ParentID:%d\n",getpid(),getppid());
				sleep(3);
			}
		case -1:
			perror("Process creation failed\n");
			exit(-1);
		default:
			printf("I am parent process,my pid is %d\n",getpid());
			exit(0);
	}
	return 0;
}
