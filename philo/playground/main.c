#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <limits.h>
#include <stdlib.h>
// int main(void)
// {
//     struct timeval time;
//     long time2;
//     long time3;
//     int time4;
//     int time5;

//     gettimeofday(&time, NULL);
//     printf("time : %ld %d\n", time.tv_sec, time.tv_usec);
//     time2 = time.tv_sec;
//     time3 = time.tv_usec;
//     printf("time2 : %ld %ld\n", time2, time3);
//     time4 = time.tv_sec;
//     time5 = time.tv_usec;
//     printf("time3 : %d %d\n", time4, time5);
//     printf("%ld\n", LONG_MAX + 1);
//     return (0);
// }

// void *test(void *arg)
// {
//     pthread_t *th;

//     th = (pthread_t *)arg;
//     printf("hello\n");
//     return (NULL);
// }

// int main()
// {
//     pthread_t *th;
//     int i = 0;

//     th = (pthread_t *)malloc(sizeof(pthread_t) * 3);
//     while (i < 3)
//     {
//         pthread_create(&th[i], NULL, &test, &th[i]);
//         printf("%d\n", i);
//         i++;
//     }
//     i = 0;
//     while (i < 3)
//     {
//         pthread_detach(th[i]);
//         i++;
//     }
//     return (0);
// }

int main(void)
{
    pthread_mutex_t *th;

    th = 
    pthread_mutex_init(th, NULL);
    pthread_mutex_lock(th);
    free(th);
}