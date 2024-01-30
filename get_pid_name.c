#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "get_pid_name.h"

char *get_pid_name(int id_process){
    // DIR *dir;
    // dir = opendir("/proc");
    // if (dir == NULL){
    //     perror("Erreur sa s'ouvre pas");
    //     return 1;
    // }

    char *res;
    res = malloc(sizeof(char) * 256);
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/comm", id_process);

    FILE *process = fopen(path, "r");
    if(process != NULL){
        fgets(res, 256, process);
        fclose(process);
        res[strcspn(res, "\n")] = 0;
    }
    else
    {
        res = "aucune valeur";
    }
    return res;
    
}