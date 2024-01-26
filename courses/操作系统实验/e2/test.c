#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#define __NR_get_mm_by_pid 436

int main()
{
	pid_t pid;
	unsigned long user_mm_info[11];
	long ret;

	printf("Enter the PID: ");
	scanf("%d", &pid);

	ret = syscall(__NR_get_mm_by_pid, pid, &user_mm_info, sizeof(user_mm_info));

	if (ret == 0)
	{
		printf("Process Memory Information for PID %d:\n", pid);
		printf("Start Code:\t%lx\n", user_mm_info[0]);
		printf("End Code:\t%lx\n", user_mm_info[1]);
		printf("Start Data:\t%lx\n", user_mm_info[2]);
		printf("End Data:\t%lx\n", user_mm_info[3]);
		printf("Start Brk:\t%lx\n", user_mm_info[4]);
		printf("Brk:\t%lx\n", user_mm_info[5]);
		printf("Start Stack:\t%lx\n", user_mm_info[6]);
		printf("Arg Start:\t%lx\n", user_mm_info[7]);
		printf("Arg End:\t%lx\n", user_mm_info[8]);
		printf("Env Start:\t%lx\n", user_mm_info[9]);
		printf("Env End:\t%lx\n", user_mm_info[10]);
	}
	else
	{
		perror("Error retrieving memory information");
	}

	return 0;
}
