#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <limits.h>

int main(void)
{
    struct timeval time;
    long time2;
    long time3;
    int time4;
    int time5;

    gettimeofday(&time, NULL);
    printf("time : %ld %d\n", time.tv_sec, time.tv_usec);
    time2 = time.tv_sec;
    time3 = time.tv_usec;
    printf("time2 : %ld %ld\n", time2, time3);
    time4 = time.tv_sec;
    time5 = time.tv_usec;
    printf("time3 : %d %d\n", time4, time5);
    return (0);
}