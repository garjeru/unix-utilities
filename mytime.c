#include<stdio.h>
#include<sys/resource.h>
#include<sys/times.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
        struct tms start_tms;
        struct tms end_tms;
        int stat;
        struct rusage usage;
        int pid;
        struct timeval utime;

        if(argc < 2){
                printf("Usage: a.out command\n");
                exit(0);
        }
        time_t start = time(NULL);
        if(fork() == 0){
                if(execv(argv[1], &argv[1]) == -1){
                        printf("Command execution failed.\n");
                }
        }else {
                pid = wait3(&stat, 0, &usage);
                printf("User CPU time :  %ld.%06ld\n", usage.ru_utime);
                printf("System CPU time :  %ld.%06ld\n", usage.ru_stime);
        }

        printf("Elapsed walk-clock time :  %f\n", (double)(time(NULL) - start));

        return 0;
}