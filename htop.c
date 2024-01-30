#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void){

    initscr();
    int height, width, start_x, start_y;
    height = 20;
    width = 30;
    start_x = 2;
    start_y = 2;

    WINDOW *win = newwin(height, width, start_x, start_y);
    box(win, 0,0);

    DIR *dir;
    struct dirent *entry;
   // struct stat fileStat;

    // j'ouvre le proc (répertoire des processe)
    dir = opendir("/proc");
    if (dir == NULL){
        perror("Erreur sa s'ouvre pas");
        return 1;
    }
    // ont lit les entrée du repertoire
    while ((entry = readdir(dir)) != NULL)
    {
        // on ignore les entrée qui ne sont pas des répertoire
        if (entry->d_type == DT_DIR){
            // on convertit le nom du dossier en nombre pour filtrer le process
            int pid = atoi(entry->d_name);

            // on ignore les process non valide
            if(pid > 0){
                printw("Process trouvé : %d\n", pid);
            }
        }
    }
    
    // printw("Process ID: %d\n", getpid());
    // printw("Parent Process ID: %d\n", getppid());
    refresh();
    getch();
    endwin();


    return 0;
}