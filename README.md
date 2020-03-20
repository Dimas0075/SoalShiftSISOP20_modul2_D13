# Praktikum Modul 2 Sistem Operasi 2020
## Kelompok D13
Herri Purba (05111840000056)<br/>
Nugroho Dimas A (05111840000075)

### Nomor 1
#### Soal :
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:

a. Program menerima 4 argumen berupa:
- i. Detik: 0-59 atau * (any value)
- ii. Menit: 0-59 atau * (any value)
- iii. Jam: 0-23 atau * (any value)
- iv. Path file .sh

b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai

c. Program hanya menerima 1 config cron

d. Program berjalan di background (daemon)

e. Tidak boleh menggunakan fungsi system()

Contoh: ./program \* 34 7 /home/somi/test.sh
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.


#### Penyelesaian :
Membuat rangka deamon
```c
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
    sleep(1);
  }
  }
```

Menetukan waktu sekarang dan memilah jam, menit, detik secarang
```c
time_t now = time(NULL);
    struct tm *now_tm = localtime(&sekarang);

    nowS = now_tm->tm_sec;
    nowM = now_tm->tm_min;
    nowH = now_tm->tm_hour;

```

Membuat argumen error jika tidak berjalan sesuai perintah 
```c
if(argc>=5){
        printf("Error\n");
        return 0;
      }

```

Alur yang seperti crontab menjalankan perintah pada jam menit maupun detik tertentu
```c
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
```

### Nomor 2
#### Soal :
 Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia
merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat
sebuah program.
a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat
sebuah program C yang per 30 detik membuat sebuah folder dengan nama
timestamp [YYYY-mm-dd_HH:ii:ss].
b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari
https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap
gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah

detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-
mm-dd_HH:ii:ss].

c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan
folder akan di delete(sehingga hanya menyisakan .zip).

d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-
generate sebuah program "killer" yang siap di run(executable) untuk

menterminasi semua operasi program tersebut. Setelah di run, program yang
menterminasi ini lalu akan mendelete dirinya sendiri.
e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu
MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan
dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen
-b. Ketika dijalankan dalam MODE_A, program utama akan langsung
menghentikan semua operasinya ketika program killer dijalankan. Untuk
MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi
membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua
folder terisi gambar, terzip lalu di delete).

### Nomor 3
#### Soal :
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).
- a. Program buatan jaya harus bisa membuat dua direktori di
“/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.
- b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori
“/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak
hanya itu tugasnya.
- c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di
dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan
pengelompokan, semua file harus dipindahkan ke
“/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke
“/home/[USER]/modul2/indomie/”.
- d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/”
harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu
3 detik kemudian membuat file bernama “coba2.txt”.
(contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).</Br>
Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat
program tersebut.
Catatan :
  - Tidak boleh memakai system().
  - Tidak boleh memakai function C mkdir() ataupun rename().
  - Gunakan exec dan fork
  - Direktori “.” dan “..” tidak termasuk
  
#### Penyelesaian :
##### Nomor 3a.<br/>
```c
if (cid == 0) {
char *argv[] = {"mkdir", "/home/dimas/Documents/Modul2/soal3/indomie", NULL};
execv("/bin/mkdir", argv);
}

if (cid2 == 0) {
sleep(5);
char *argv[] = {"mkdir", "/home/dimas/Documents/Modul2/soal3/sedaap", NULL};
execv("/bin/mkdir", argv);
}
```
Membuat folder dengan menggunakan execv 
##### Nomor 3b.<br/>
```c
if (cid3 == 0) {
char *argv[] = {"unzip", "/home/dimas/Documents/Modul2/soal3/jpg.zip", "-d", "/home/dimas/Documents/Modul2/soal3/", NULL};
execv("/usr/bin/unzip", argv);
}
``` 
Dengan menggunakan comment unzip untuk mengekstrak jpg.zip dari home/dimas/Documents/Modul2/soal3/jpg.zip ke /home/dimas/Documents/Modul2/soal3/
##### Nomor 3c.<br/>
```c
if (cid4 == 0) {

DIR *dp;
struct dirent *entry;
int file = 0;
char dir[50] = "/home/dimas/Documents/Modul2/soal3/jpg/" , dir2[50], dir3[50]="/home/dimas/Documents/Modul2/indomie/";

dp = opendir("/home/dimas/Documents/Modul2/soal3/jpg");
if(dp == NULL)
{
perror("Cannot open directory");
return(1);
}

while( (entry=readdir(dp))){
file++;
printf("File %3d: %d : %s\n",
file,
entry->d_type,entry->d_name
);
if (!strcmp (entry->d_name, "."))
continue;
if (!strcmp (entry->d_name, ".."))
continue;

strcpy(dir2,dir);
strcat(dir2,entry->d_name);
```
Digunakan untuk memfilter folder<br/>
Referensi [Herpur Tampan Menawan](https://stackoverflow.com/questions/8149569/scan-a-directory-to-find-files-in-c)

```c
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
printf("File %3d: %d : %s\n",
file,
entry->d_type,entry->d_name
);
if (!strcmp (entry->d_name, "."))
continue;
if (!strcmp (entry->d_name, ".."))
continue;
```
Digunakan untuk memfilter files

```c
if (cid5 == 0 && entry->d_type == 8) {
char *argv[] = {"mv",dir2,"/home/dimas/Documents/Modul2/soal3/sedaap/", NULL};
execv("/bin/mv", argv);
}

if (cid5 == 0 && entry->d_type == 4) {
char *argv[] = {"mv",dir2,"/home/dimas/Documents/Modul2/soal3/indomie/", NULL};
execv("/bin/mv", argv);
}
```
Perintah untuk memindahkan ke masing-masing direktori. Folder dipindah ke folder indomie sedangkan file-file dipindah ke folder sedaap

##### Nomor 3d.<br/>
```c
if (cid6 == 0) {
strcpy(dir2,dir);
strcat(dir2,entry->d_name);
strcat(dir2,"/coba1.txt");
printf("%s\n",dir2);
char *argv[] = {"echo","$null", ">>", dir2, NULL};
execv("/bin/echo", argv);
}

if (cid7 == 0) {
sleep(3);
strcpy(dir2,dir);
strcat(dir2,entry->d_name);
strcat(dir2,"/coba2.txt");
printf("%s\n",dir2);
char *argv[] = {"echo","$null",">>",dir2, NULL};
execv("/bin/echo", argv);
}
```
Membuat coba1.txt dan coba2.txt. Untuk file coba2.txt akan dibuat setelah 3 detik dengan fungsi **sleep(3)**
