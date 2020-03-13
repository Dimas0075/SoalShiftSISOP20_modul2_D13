#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

// void printdir(char *dir, int depth)
// {
//     DIR *dp;
//     struct dirent *entry;
//     struct stat statbuf;
//     if((dp = opendir(dir)) == NULL) {
//         fprintf(stderr,"cannot open directory: %s\n", dir);
//         return;
//     }
//     chdir(dir);
//     while((entry = readdir(dp)) != NULL) {
//         lstat(entry->d_name,&statbuf);
//         if(S_ISDIR(statbuf.st_mode)) {
//             /* Found a directory, but ignore . and .. */
//             if(strcmp(".",entry->d_name) == 0 ||
//                 strcmp("..",entry->d_name) == 0)
//                 continue;
//             printf("%*s%s/\n",depth,"",entry->d_name);
//             /* Recurse at a new indent level */
//             printdir(entry->d_name,depth+4);
//         }
//         else printf("%*s%s\n",depth,"",entry->d_name);
//     }
//     chdir("..");
//     closedir(dp);
// }

int main() {
pid_t cid, cid2, cid3, cid4, cid5, cid6,cid7, cid8;
int status;
char destination[100];
FILE *tmptFile;

cid = fork();

if (cid < 0) {
exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
}

if (cid == 0) {
char *argv[] = {"mkdir", "/home/dimas/Documents/Modul2/soal3/indomie", NULL};
execv("/bin/mkdir", argv);
} else {
// this is parent
while ((wait(&status)) > 0);
int status2;
cid2 = fork();

if (cid2 < 0) {
exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
}

if (cid2 == 0) {
sleep(5);
char *argv[] = {"mkdir", "/home/dimas/Documents/Modul2/soal3/sedaap", NULL};
execv("/bin/mkdir", argv);
} else {
// this is parent
while ((wait(&status2)) > 0);
int status3;
cid3 = fork();

if (cid3 < 0) {
exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
}

if (cid3 == 0) {
char *argv[] = {"unzip", "/home/dimas/Documents/Modul2/soal3/jpg.zip", "-d", "/home/dimas/Documents/Modul2/soal3/", NULL};
execv("/usr/bin/unzip", argv);
// printdir("/home/dimas/Documents/Modul2/soal3/jpg",0);
} else {
// this is parent
while ((wait(&status3)) > 0);
int status4;
cid4 = fork();

if (cid4 < 0) {
exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
}

if (cid4 == 0) {

DIR *dp;
struct dirent *entry;
int file = 0;
char dir[50] = "/home/dimas/Documents/Modul2/soal3/jpg/" , dir2[50], dir3[50]="/home/dimas/Documents/Modul2/indomie/";
dp = opendir("/home/dimas/Documents/Modul2/soal3/jpg");
if(dp == NULL)
{
    puts("Cannot open directory");
    return(1);
}

while( (entry=readdir(dp))){
file++;
printf("File %d: %d : %s\n",
file,
entry->d_type,entry->d_name
);
if (!strcmp (entry->d_name, "."))
continue;
if (!strcmp (entry->d_name, ".."))
continue;

strcpy(dir2,dir);
strcat(dir2,entry->d_name);

cid5 = fork();

if (cid5 < 0) {
exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
}

if (cid5 == 0 && entry->d_type == 8) {
char *argv[] = {"mv",dir2,"/home/dimas/Documents/Modul2/soal3/sedaap/", NULL};
execv("/bin/mv", argv);
}

if (cid5 == 0 && entry->d_type == 4) {
char *argv[] = {"mv",dir2,"/home/dimas/Documents/Modul2/soal3/indomie/", NULL};
execv("/bin/mv", argv);
}
}
} else {
// this is parent
while ((wait(&status4)) > 0);
cid8 = fork();

if (cid8 < 0) {
exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
}

if (cid8 == 0) {
DIR *dp;
struct dirent *entry;
int file = 0;
char dir[50] = "/home/dimas/Documents/Modul2/soal3/indomie/" , dir2[50];

dp = opendir("/home/dimas/Documents/Modul2/soal3/indomie");
if(dp == NULL){
perror("Cannot open directory");
return(1);
}

while( (entry=readdir(dp))){
file++;
printf("File %d: %d : %s\n",
file,
entry->d_type,entry->d_name
);
if (!strcmp (entry->d_name, "."))
continue;
if (!strcmp (entry->d_name, ".."))
continue;

int status5;
cid6 = fork();

if (cid6 < 0) {
exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
}

if (cid6 == 0) {
strcpy(dir2,dir);
strcat(dir2,entry->d_name);
strcat(dir2,"/coba1.txt");
char *argv[] = {"echo", "$null", ">>", dir2, NULL};
execv("/bin/echo", argv);
}

else {
while ((wait(&status5)) > 0);
cid7 = fork();

if (cid7 < 0) {
exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
}

if (cid7 == 0) {
sleep(3);
strcpy(dir2,dir);
strcat(dir2,entry->d_name);
strcat(dir2,"/coba2.txt");
char *argv[] = {"echo","$null",">>", dir2, NULL};
execv("/bin/echo", argv);
}
}
}
}
}
}
}
}
}
