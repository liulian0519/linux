#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(void)
{
	pid_t pid;
	printf("process creation study\n");
	pid=fork();
	switch(pid){
	case 0:
		printf("child process is running,curpid is %d,parentpid is %d\n",pid,getppid());
		break;
	case -1:
		perror("process creation failed\n");
		break;
	default:
		printf("parent process is running,childpid is %d,parentpid is %d\n",pid,getpid());
		break;

	}
	exit(0);
}

