#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "get_pids.h"

int *get_pids(){
     DIR *dir;
    struct dirent *entry;
    int pid = 0;
    int *res;
    res = malloc(sizeof(int) * 256);
    int i = 0;
   // struct stat fileStat;

    // j'ouvre le proc (répertoire des processe)
    dir = opendir("/proc");
    if (dir == NULL){
        perror("Erreur sa s'ouvre pas");
        return NULL;
    }
   // ont lit les entrée du repertoire
    while ((entry = readdir(dir)) != NULL)
    {
        // on ignore les entrée qui ne sont pas des répertoire
        if (entry->d_type == DT_DIR){
            // on convertit le nom du dossier en nombre pour filtrer le process
            pid = atoi(entry->d_name);

            // on ignore les process non valide
            if(pid > 0){
                res[i] = pid;
                i++;
            }
        }
    }

    return res;
}