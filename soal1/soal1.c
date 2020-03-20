#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(int argc , char *argv[]) {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    // Tulis program kalian di sini
    pid_t chld;
    chld=fork();
    char *bash[]={"bash", argv[4], NULL};

    time_t now = time(NULL);
    struct tm *now_tm = localtime(&sekarang);

    nowS = now_tm->tm_sec;
    nowM = now_tm->tm_min;
    nowH = now_tm->tm_hour;

    if(argc>=5){
        printf("Error\n");
        return 0;
      }


    if(strcmp(argv[1],"*")==0){
        if(strcmp(argv[2],"*")==0){
            if(strcmp(argv[3],"*")==0){         // ***
                while(1){
                   if(chld == 0){
                    execvp("/bin/bash",bash);
                 }
                sleep(1);
                time(&now);
                timeinfo = localtime ( &now );
                }
            }
            else if(atoi(argv[3]) == nowH){         //**A
                while (1) {
                    if(atoi(argv[3]) <24 && atoi(argv[3]) >0 ){
                        if(chld == 0){
                            execvp("/bin/bash",bash);
                        }
                    }
                    sleep(1);
                    time(&now);
                    timeinfo = localtime ( &now );
                }
            }
            else{
                printf("Error\n");
                return 0;
            }
        }else if(atoi(argv[2]) == nowM){
            if(strcmp(argv[3],"*")==0 && atoi(argv[2]) <60 && atoi(argv[2]) >=0){     //*A*
                while(1){
                   if(chld == 0){
                    execvp("/bin/bash",bash);
                 }
                sleep(1);
                time(&now);
                timeinfo = localtime ( &now );
                }
            }
            else if(atoi(argv[3]) == nowH){     //*AA
                while (1) {
                    if(atoi(argv[3]) <24 && atoi(argv[3]) >=0 && atoi(argv[2]) <60 && atoi(argv[2]) >=0 && atoi(argv[1]) <60 && atoi(argv[1]) >=0){
                        if(chld == 0){
                            execvp("/bin/bash",bash);
                        }
                    }
                    sleep(1);
                    time(&now);
                    timeinfo = localtime ( &now );
                }
            }
            else{
                printf("Error\n");
                return 0;
            }
            
        }
        else{
            printf("Error\n");
            return 0;
        }
    }
  
    
    
    else if(atoi(argv[1]) == nowS){
        if(strcmp(argv[2],"*")==0){
            if(strcmp(argv[3],"*")==0 && atoi(argv[1]) <60 && atoi(argv[1]) >=0){         //A**
                while(1){
                   if(chld == 0){
                    execvp("/bin/bash",bash);
                 }
                sleep(1);
                time(&now);
                timeinfo = localtime ( &now );
                }
            }
            else if(atoi(argv[3]) == nowH){     //A*A
                while (1) {
                    if(atoi(argv[3]) <24 && atoi(argv[3]) >=0  && atoi(argv[1]) <60 && atoi(argv[1]) >=0 ){
                        if(chld == 0){
                            execvp("/bin/bash",bash);
                        }
                    }
                    sleep(1);
                    time(&now);
                    timeinfo = localtime ( &now );
                }
            }
            else{
                printf("Error\n");
                return 0;
            }
        }else if(atoi(argv[2]) == nowM){
            if(strcmp(argv[3],"*")==0 && atoi(argv[2]) <60 && atoi(argv[2]) >=0 && atoi(argv[1]) <60 && atoi(argv[1]) >=0){     //AA*
                while(1){
                   if(chld == 0){
                    execvp("/bin/bash",bash);
                 }
                sleep(1);
                time(&now);
                timeinfo = localtime ( &now );
                }
            }
            else if(atoi(argv[3]) == nowH){     //AAA
                while (1) {
                    if(atoi(argv[3]) <24 && atoi(argv[3]) >=0 && atoi(argv[2]) <60 && atoi(argv[2]) >=0 && atoi(argv[1]) <60 && atoi(argv[1]) >=0 ){
                        if(chld == 0){
                            execvp("/bin/bash",bash);
                        }
                    }
                    sleep(1);
                    time(&now);
                    timeinfo = localtime ( &now );
                }
            }
            else{
                printf("Error\n");
                return 0;
            }
        }
        else{
            printf("Error\n");
            return 0;
        }
    }
    else{
        printf("Error\n");
        return 0;
    }
            
    sleep(1);
  }
}
