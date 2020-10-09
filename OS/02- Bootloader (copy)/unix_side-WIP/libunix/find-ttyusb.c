// don't like, can give /dev/ttyACM0 as arg to my-install.c
#define _GNU_SOURCE
#include <assert.h>
#include <fcntl.h>
#include <string.h>

#include "libunix.h"
#include <dirent.h>


// find the TTY-usb device (if any) by using <scandir> to search for
// a device with a prefix given by <ttyusb_prefixes> in /dev
// returns:
//  - device name.
// panic's if 0 or more than 1.
//
char *find_ttyusb(void) {
    int ocurrences = 0;
    // use <alphasort> in <scandir>
    // return a malloc'd name so doesn't corrupt.

    struct dirent **fileList;
    int noOfFiles;
    char* path = "/dev";
    //printf("finde1\n");
    noOfFiles = scandir(path, &fileList, NULL, alphasort);
    //printf("finde2\n");
    if (noOfFiles == -1) {
        panic("scandir error");
    }
    char *p = (char*)malloc(13); 
    *p = '\0';
    for(int i = 0; i < noOfFiles; i++){
        if(strstr(fileList[i]->d_name, "ttyACM") != NULL){ // i use arduino as ttyusb
            ocurrences++;
            //p = (char*)malloc(sizeof(path) + sizeof(fileList[i]->d_name) + 1);
            //p = strdup(fileList[i] -> d_name); forgot the /dev/ part xd
            strcat(p, path);
            strcat(p, "/");
            strcat(p, fileList[i]->d_name); 
        }

        free(fileList[i]);
    }
    free(fileList);

    if(ocurrences != 1){
        panic("#TTY-USB != 1");
    }

    printf("%s\n", p);
    return p;
}
