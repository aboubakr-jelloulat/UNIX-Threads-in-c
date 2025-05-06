/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:19:12 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/06 14:49:24 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> // For Threads
#include <time.h>

// void *routine()
// {
//     printf("Test from threads\n");
//     sleep(3);
//     printf ("Ending Thread\n");
//     return NULL;
// }

// int main(int ac, char **av)
// {
//     pthread_t   t1, t2;
//     pthread_create(&t1, NULL, &routine, NULL);
//     pthread_create(&t2, NULL, &routine, NULL);

//     pthread_join(t1, NULL);

//     pthread_join(t2, NULL);

//     return 0;
// }

// int x = 0;

// void *routine2()
// {

//     sleep(2);
//     printf ("Value of x routine 2 : %d\n", x);
//     //printf ("Hello from Threads : process id : %d\n", getpid());

//     return NULL;
// }

// void *routine()
// {
//     x = 42; // 🟢 Objective: Show that threads share memory, so a change in one affects the other.
//     sleep(2);
//     printf ("Value of x routine 1 : %d\n", x);
//     //printf ("Hello from Threads : process id : %d\n", getpid());

//     return NULL;
// }

// int main(int ac, char **av)
// {
//    pthread_t   t1, t2;
//     pthread_create(&t1, NULL, &routine, NULL);
//     pthread_create(&t2, NULL, &routine2, NULL);

//     pthread_join(t1, NULL);

//     pthread_join(t2, NULL);

//     return 0;
// }

/* ************* A Practical Example of Threads ***************** */

// #define NC "\e[0m"
// #define YELLOW "\e[1;33m"

// void *thread_routine(void *data)
// {
//     pthread_t tid;

//     tid = pthread_self();

//     printf("%sThread [%ld]: The heaviest burden is to exist without living.%s\n", YELLOW, tid, NC);
//     return (NULL);
// }

// int main(void)
// {

//     pthread_t tid1;
//     pthread_t tid2;

//     pthread_create(&tid1, NULL, thread_routine, NULL);
//     printf("Main: Created first thread (Main thread) [%ld]\n", tid1);

//     pthread_create(&tid2, NULL, thread_routine, NULL);
//     printf("Main: Created second thread [%ld]\n", tid2);

//     // The main thread waits for the new threads to end
//     // with pthread_join.
//     pthread_join(tid1, NULL);
//     printf("Main: Joining first thread [%ld]\n", tid1);
//     pthread_join(tid2, NULL);
//     printf("Main: Joining second thread [%ld]\n", tid2);

//     return 0;
// }

/*      **************  Synchronization Errors  ****************** */

// #define TIMES_TO_COUNT 21000

// #define NC "\e[0m"
// #define YELLOW "\e[33m"
// #define BYELLOW "\e[1;33m"
// #define RED "\e[31m"
// #define GREEN "\e[32m"

// void *thread_routine(void *data)
// {
//     // Each thread starts here
//     pthread_t tid;
//     unsigned int *count; // pointer to the variable created in main
//     unsigned int i;

//     tid = pthread_self();
//     count = (unsigned int *)data;
//     // Print the count before this thread starts iterating:
//     printf("%sThread [%ld]: Count at thread start = %u.%s\n", YELLOW, tid, *count, NC);

//     i = 0;
//     while (i < TIMES_TO_COUNT)
//     {
//         // Iterate TIMES_TO_COUNT times && Increment the counter at each iteration
//         (*count)++;
//         i++;
//     }
//     // Print the final count when this thread

//     printf("%sThread [%ld]: Final count = %u.%s\n", BYELLOW, tid, *count, NC);

//     return (NULL);
// }

// int main(void)
// {
//     pthread_t tid1;
//     pthread_t tid2;
//     // Variable to keep track of the threads' counts:
//     unsigned int count;

//     count = 0;
//     // Since each thread counts TIMES_TO_COUNT times and that
//     // we have 2 threads, we expect the final count to be
//     // 2 * TIMES_TO_COUNT:
//     printf("Main: Expected count is %s%u%s\n", GREEN, 2 * TIMES_TO_COUNT, NC);

//     pthread_create(&tid1, NULL, thread_routine, &count);
//     printf("Main: Created first thread [%ld]\n", tid1);

//     pthread_create(&tid2, NULL, thread_routine, &count);
//     printf("Main: Created second thread [%ld]\n", tid2);

//     pthread_join(tid1, NULL);
//     printf("Main: Joined first thread [%ld]\n", tid1);
//     sleep(2);
//     pthread_join(tid2, NULL);
//     printf("Main: Joined second thread [%ld]\n", tid2);

//     if (count != (2 * TIMES_TO_COUNT))
//         printf("%sMain: ERROR ! Total count is %u%s\n", RED, count, NC);
//     else
//         printf("%sMain: OK. Total count is %u%s\n", GREEN, count, NC);
//     return (0);
// }
/*
    The failure occurs because multiple threads are concurrently modifying the count variable,
    but without synchronization. This means both threads are reading and writing to the same count variable at the same time,
    which leads to race conditions.

*/

/*  ******************      The Danger of Data Races     ********************** */

// int mails = 0;

// void *routine()
// {
//     // for (int i = 0; i < 100; i++) it's fun
//     //     mails++;

//     for (int i = 0; i < 10000000; i++)
//         mails++;

//     return NULL;
// }

// int main(int ac, char **av)
// {
//     pthread_t t1, t2;

//     pthread_create(&t1, NULL, &routine, NULL);
//     pthread_create(&t2, NULL, &routine, NULL);

//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);

//     printf("numbers of mails : %d\n", mails);

//     return 0;
// }

/* ******************  🤝 What is a Mutex ? ******************* */

/*
    A mutex (short for " mut ual ex clusion") is a synchronization primitive.
    It is essentially a lock that allows us to regulate access to data and prevent shared resources being used at the same time.

    We can think of a mutex as the lock of a bathroom door.
    One thread locks it to indicate that the bathroom is occupied.
    The other threads will just have to patiently stand in line until the door is unlocked before they can take their turn in the bathroom.

*/

// int mails = 0;
// pthread_mutex_t mutex;

// void *routine()
// {
//     for (int i = 0; i < 10000000; i++)
//     {
//         pthread_mutex_lock(&mutex);
//         mails++;
//         pthread_mutex_unlock(&mutex);
//     }

//     return NULL;
// }

// int main(int ac, char **av)
// {
//     pthread_t t1, t2, t3;

//     pthread_mutex_init(&mutex, NULL);

//     pthread_create(&t1, NULL, &routine, NULL);
//     pthread_create(&t2, NULL, &routine, NULL);
//     pthread_create(&t3, NULL, &routine, NULL);

//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);
//     pthread_join(t3, NULL);

//     printf("numbers of mails : %d\n", mails);

//     pthread_mutex_destroy(&mutex); // free / destroy memory allocate    Destroying a Mutex

//     return 0;
// }

/*          ************  How to create threads in a loop (pthread_create)   ***************** */

// int mails = 0;
// pthread_mutex_t mutex;

// void *routine()
// {
//     for (int i = 0; i < 10000000; i++)
//     {
//         pthread_mutex_lock(&mutex);
//         mails++;
//         pthread_mutex_unlock(&mutex);
//     }

//     return NULL;
// }

// int main(void)
// {
//     pthread_t th[4];
//     pthread_mutex_init(&mutex, NULL);

//     for (int i = 0; i <= 8; ++i)
//     {
//         pthread_create(&th[i], NULL, &routine, NULL);
//         printf("\033[32mThread %d has started\033[0m\n", i);

//     }

//     for (int i = 0; i <= 8; ++i)
//     {
//         pthread_join(th[i], NULL);
//         printf("\033[31mThread %d has finished execution\033[0m\n\n", i);
//     }

//     printf("\nNumber of mails is : %d\n", mails);

//     pthread_mutex_destroy(&mutex);

//     return 0;
// }

/*
    if we use only one for loop for creat and join that mean is : no synchronization

*/

/*  ****************** Get return value from a thread (pthread_join) *******************/

// void *roll_dice()
// {
//     int value = (rand() % 6) + 1;
//     int *result = malloc(sizeof(int));

//     *result = value;

//    return (void *) result;
// }

// int main(void)
// {
//     srand(time(NULL));
//     pthread_t   th;
//     int *res;

//     pthread_create(&th, NULL, &roll_dice, NULL);

//     pthread_join(th, (void **) &res);

//     printf("Result : %d\n", *res);

//     return 0;
// }

/*  ****************   What is pthread_t?    **************************/

// The ID of new thread

// #define THREAD_NUM 8

// pthread_mutex_t mutexFuel;
// int fuel = 50;
// pthread_mutex_t mutexWater;
// int water = 10;

// void *routine(void *args)
// {
//     if (rand() % 2 == 0)
//     {
//         pthread_mutex_lock(&mutexFuel);
//         sleep(1);
//         pthread_mutex_lock(&mutexWater);
//     }
//     else
//     {
//         pthread_mutex_lock(&mutexWater);
//         sleep(1);
//         pthread_mutex_lock(&mutexFuel);
//     }

//     fuel += 50;
//     water = fuel;
//     printf("Incremented fuel to: %d set water to %d\n", fuel, water);
//     pthread_mutex_unlock(&mutexFuel);
//     pthread_mutex_unlock(&mutexWater);
// }

int main(int argc, char *argv[])
{
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexFuel, NULL);
    pthread_mutex_init(&mutexWater, NULL);
    int i;
    for (i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
        {
            perror("Failed to create thread");
        }
    }

    for (i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread");
        }
    }
    printf("Fuel: %d\n", fuel);
    printf("Water: %d\n", water);
    pthread_mutex_destroy(&mutexFuel);
    pthread_mutex_destroy(&mutexWater);
    return 0;
}

