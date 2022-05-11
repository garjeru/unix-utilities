#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<time.h>
#include<math.h>

void fileModTime(char *path, const int dirRoot, int timeSlot[24][2], time_t curr);

int main(int argc, char *argv[]){
        struct stat statbuf;
        int timeSlot[24][2] = {0};
        time_t now;
        time_t curr = time(&now);

        char cwd[256];
        char mtime1[80];

        /* finds current directory if path is not provided in command */
        if(argc == 1){
                getcwd(cwd, sizeof(cwd));
                printf("current directory %s\n", cwd);
                fileModTime(cwd, 0, timeSlot, curr);
        }
        /* error on more than one path provided */
        else if(argc > 2){
                printf("Usage: a.out directory or a.out\n");
                exit(0);
        }
        else{
                fileModTime(argv[1], 0, timeSlot, curr);
        }

        int i = 0;
        int j = 1;

        struct tm localtime_c;

        localtime_c = *localtime(&curr);
        localtime_c.tm_mday -= 1;
        for(i = 23; i >= 0; i--){
                localtime_c.tm_hour += 1;
                time_t newTime = mktime(&localtime_c);
                printf("%s: %d\n", ctime(&newTime), timeSlot[i][1]);
        }
        return 0;
}

/* dirRoot is used to add indentation */
void fileModTime(char *path, const int dirRoot, int timeSlot[24][2], time_t curr){
        struct dirent *de;
        char newPath[2000];
        struct stat statbuf;
        /* Opens directory stream and it's reference is stored in *direct */
        DIR *direct = opendir(path);
        int n;
        char mtime[80];

        if(!direct){
               return;
        }

         /* read the next element using readdir(direct) */
         while((de = readdir(direct)) != NULL){
                if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
                        if(stat(de->d_name, &statbuf) == -1){
                                continue;
                        }
                        time_t m_t = statbuf.st_mtime;

                        struct tm m_tm = *localtime(&m_t);

                        time_t file_mtime = mktime(&m_tm);
                        printf("%s - %s\n", de->d_name, ctime(&file_mtime));

                        float hour = (curr - m_t)/3600;
                        int hour_i = (int)ceil(hour);
                        printf("Modified in last  = %d\n",(int) ceil(hour)%24);

                        if(hour <= 23){
                                timeSlot[(int)hour%24][1] += 1;
                        }

                        strcpy(newPath, path);

                        strcat(newPath, "/");

                        strcat(newPath, de->d_name);

                        fileModTime(newPath, dirRoot + 2, timeSlot, curr);
                }
        }
        closedir(direct);
}