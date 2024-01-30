#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "get_pids.h"
#include "get_pid_name.h"

int main(void){

    initscr();
    raw();
    int height, width, start_x, start_y;
    height = LINES;
    width = COLS;
    start_x = 0;
    start_y = 0;

    WINDOW *win = newwin(height, width, start_x, start_y);
    box(win, ACS_VLINE, ACS_HLINE);
    refresh();

    int *id_process = get_pids();
    if (id_process != NULL)
    {
        for (int i = 0; id_process[i]; i++)
        {
            mvwprintw(win, i, COLS / 2, "%d", id_process[i]);
            mvwprintw(win, i, 0, "%s", get_pid_name(id_process[i]));
        }
        
    }
    
free(id_process);
    
    // printw("Process ID: %d\n", getpid());
    // printw("Parent Process ID: %d\n", getppid());
    mvwprintw(win, 2, 2, "c'est ibrah");
    wrefresh(win);
    getch();
    getch();
    endwin();
    free(win);


    return 0;
}