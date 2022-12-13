#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	printf("%d\n", time.tv_usec / 1000);
	usleep(200 * 1000);
	gettimeofday(&time, NULL);
	printf("%d\n", time.tv_usec / 1000);
	return (0);
}