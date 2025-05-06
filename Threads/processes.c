#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

// int main(void)
// {
//     int x = 0;
//     int pid = fork();
//     if (pid == -1)
//         perror("fork");
//     printf("Hello from processes\n");
//     printf ("Process id %d\n", getpid());

//     if (!pid)
//     {
//         x++;
//     }
//     sleep(2);
//     printf ("Value of x : %d\n", x); //🟢 Objective: Show that parent and child do not share memory.

//     if (pid != 0)
//         wait(NULL);

//     return 0;
// }
