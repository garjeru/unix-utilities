#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/types.h>
#include<stdlib.h>

void fileTree(char *path, const int dirRoot);

int main(int argc, char *argv[]){
        char cwd[256];

        /* finds current directory if path is not provided in command */
        if(argc == 1){
                getcwd(cwd, sizeof(cwd));
                printf("current directory %s\n", cwd);
                fileTree(cwd, 0);
        }
        /* error on more than one path provided */
        else if(argc > 2){
                printf("Usage: a.out directory or a.out\n");
                exit(0);
        }
        else{
                fileTree(argv[1], 0);
        }
        return 0;
}
/* dirRoot is used to add indentation */
void fileTree(char *path, const int dirRoot){
        struct dirent *de;
        char newPath[2000];

        /* Opens directory stream and it's reference is stored in *direct */
        DIR *direct = opendir(path);
        int n;

        if(!direct){
               return;
        }

         /* read the next element using readdir(direct) */
         while((de = readdir(direct)) != NULL){
                if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){

                        for(n = 0; n < dirRoot; n++){
                                if(n % 2 == 0 || n == 0){
                                        printf("|");
                                }else {
                                        printf(" ");
                                }

                        }
                        printf("%s%s%s\n", "|", "-", de->d_name);

                        strcpy(newPath, path);

                        strcat(newPath, "/");

                        strcat(newPath, de->d_name);

                        fileTree(newPath, dirRoot + 2);
                }
        }
        closedir(direct);
}
