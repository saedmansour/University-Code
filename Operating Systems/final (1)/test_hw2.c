#include <errno.h>
#include <stdlib.h>
#include <sched.h>

#define IS_NEXT 1
#define IS_PREV 0
#define SCHED_PRIO  3


struct switch_info
{
	int previous_pid;
	int next_pid;
	int previous_policy;
	int next_policy;
	unsigned long time;
	int time_slice;
	int reason;
};

void  print_policy(int is_next, int policy_number);
void print_reason(int reason_number);


int main(int argc, char* argv[])
{
	int nices[100];
	int son_pid;
	int i, j, k, pid, number_of_elements, status;
	int l;

	struct switch_info arr[100];
	struct sched_param temp;
	
	if((argc - 1 ) % 2 != 0)	//even arguments
	{
		return -1;
	}
	
	
	for(i = 1; i < argc; ++i)
	{
		nices[i-1] = atoi(argv[i]);
	}

	pid = getpid();
	temp.sched_priority = 0;
	
	syscall(156, pid, SCHED_PRIO, &temp);	//sys_setscheduler
	
	for(l = 1 ; l < argc; l++)
	{	
		pid = fork();
		if (pid == 0)	//son
		{
			syscall(34,nices[l-1]);	//sys_nice

			// run for 20 seconds
			for (i = 0; i < 5500; i++)
			{
				for (j = 0; j < 1000; j++)
				{
					for (k = 0; k < 1000; k++){}
				}
			}
			goto out_son;
		}
	}
	

	while (wait(&status) != -1);
 
	number_of_elements = syscall(243, arr);

	if (number_of_elements == -1) //error
	{
		return -1;
	}

	//<output>
	printf("Number of elements: %d\n",number_of_elements);
	for(i = 0; i < number_of_elements; i++)
	{
		printf("index: %d\n", i);
		printf("**************\n");
		printf("Previous pid: %d\n", arr[i].previous_pid);
		printf("Next Pid: %d\n", arr[i].next_pid);
		
		print_policy(IS_PREV, arr[i].previous_policy);
		print_policy(IS_NEXT, arr[i].next_policy);

		printf("Switch Time: %ul\n", arr[i].time);
		printf("Time Slice: %d\n", arr[i].time_slice);

		print_reason(arr[i].reason);

		printf("**************\n\n\n");
	}
	//</output>

out_son:
	return 0;
}




void print_reason( int reason_number)
{
	switch (reason_number)
	{
		case 1: 
			printf("Reason: TIME_SLICE_OVER\n");
			break;
		case 2: 
			printf("Reason: PREVIOUS_GOES_WAITING\n");
			break;
		case 3: 
			printf("Reason: HIGHER_PRIORITY_WAKES\n");
			break;
		case 4: 
			printf("Reason: TASK_CREATED\n");
			break;
		case 5: 
			printf("Reason: TASK_ENDED\n");
			break;
		case 6: 
			printf("Reason: TASK_YIELDS\n");
			break;
		default:
			printf("Reason: PREVIOUS_GOES_WAITING\n");
			break;
	}
	return;
}



void print_policy(int is_next,int policy_number)
{
	if(is_next)
	{
		printf("Next Policy: ");
	}
	else
	{
		printf("Previous Policy: ");
	}

	switch(policy_number){
		case 0: 
			printf("SCHED_OTHER\n");
			break;
		case 1: 
			printf("SCHED_FIFO\n");
			break;
		case 2: 
			printf("SCHED_RR\n");
			break;
		case 3: 
			printf("SCHED_PRIO\n");
			break;
		default:
			printf("UNKNOWN_POLICY\n");
			break;
	}
	return;
}

