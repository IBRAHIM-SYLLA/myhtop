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
#include "get_process.h"

int main(void){

            
    initscr();
    raw();
    int height, width, start_x, start_y;
    height = LINES;
    width = COLS;
    start_x = 0;
    start_y = 0;
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Définition de la paire de couleurs pour le texte vert

    WINDOW *win = newwin(height, width, start_x, start_y);
    box(win, ACS_VLINE, ACS_HLINE);
    refresh();

    // Créez une sous-fenêtre pour le tableau
    int column_height = height - 3;  // Ajustez la hauteur de la column
    int column_width = width / 6.5;
    int column_start_y = 2;
    int column_start_x = 1;

    WINDOW *win_cpu;
    WINDOW *win_pid;
    WINDOW *win_ppid;
    WINDOW *win_p_name;
    WINDOW *win_p_virtualsize;
    WINDOW *win_p_thread;
    WINDOW *win_p_state;

    
    win_cpu = subwin(win, 3, COLS / 3, 1, 1);
    win_pid = subwin(win, column_height, column_width, column_start_y + 1, column_start_x);
    win_ppid = subwin(win, column_height, column_width, column_start_y + 1, 1 * (column_start_x + (column_width + 1)));
    win_p_name = subwin(win, column_height, column_width, column_start_y + 1, 2 * (column_start_x + (column_width + 1)));
    win_p_virtualsize = subwin(win, column_height, column_width, column_start_y + 1, 3 * (column_start_x + (column_width + 1)));
    win_p_thread = subwin(win, column_height, column_width, column_start_y + 1, 4 * (column_start_x + (column_width + 1)));
    win_p_state = subwin(win, column_height, column_width, column_start_y + 1, 5 * (column_start_x + (column_width + 1)));



        mvwprintw(win_pid, 1, 1, "%s", "Id Processe");
        mvwprintw(win_ppid, 1, 1, "%s", "PPID");
        mvwprintw(win_p_name, 1, 1, "%s", "Name");
        mvwprintw(win_p_virtualsize, 1, 1, "%s", "VirtualSize");
        mvwprintw(win_p_thread, 1, 1, "%s", "Threads");
        mvwprintw(win_p_state, 1, 1, "%s", "State");

         int *id_process = get_pids();
        if (id_process != NULL)
        {
            // Affichage du nom en vert
            attron(COLOR_PAIR(1)); // Activation de la couleur verte
            for (int i = 0; id_process[i]; i++)
            {
                proces processus = get_process(id_process[i]);
                mvwprintw(win_pid, i + 2, 1, "%d", id_process[i]);
                mvwprintw(win_ppid, i + 2, 1, "%d", processus.ppid);
                mvwprintw(win_p_name, i + 2, 1, "%s", processus.name);
                mvwprintw(win_p_virtualsize, i + 2, 1, "%f", processus.virtualSize);
                mvwprintw(win_p_thread, i + 2, 1, "%d", processus.threads);
                mvwprintw(win_p_state, i + 2, 1, "%s", processus.state);
                
            }
            attroff(COLOR_PAIR(1)); // Désactivation de la couleur verte
        }



    bool is_running = true;
    while (is_running) {
        double cpu_usage = get_cpu_usage();
        mvwprintw(win_cpu, 1, 1, "CPU: %f", cpu_usage);
        wrefresh(win);
        wrefresh(win_pid);
        wrefresh(win_ppid);
        wrefresh(win_p_name);
        wrefresh(win_p_virtualsize);
        wrefresh(win_p_thread);
        wrefresh(win_p_state);


       // int *id_process = get_pids();
        if (id_process != NULL)
        {
            // Affichage du nom en vert
            attron(COLOR_PAIR(1)); // Activation de la couleur verte
            for (int i = 0; id_process[i]; i++)
            {
                proces processus = get_process(id_process[i]);
                mvwprintw(win_pid, i + 2, 1, "%d", id_process[i]);
                mvwprintw(win_ppid, i + 2, 1, "%d", processus.ppid);
                mvwprintw(win_p_name, i + 2, 1, "%s", processus.name);
                mvwprintw(win_p_virtualsize, i + 2, 1, "%f", processus.virtualSize);
                mvwprintw(win_p_thread, i + 2, 1, "%d", processus.threads);
                mvwprintw(win_p_state, i + 2, 1, "%s", processus.state);
                
            }
            attroff(COLOR_PAIR(1)); // Désactivation de la couleur verte
        }

        int ch = getch();  // Attendre une touche
        if (ch == 'r' || ch == 'R') {  // Si la touche 'R' est pressée
            // Rafraîchir la fenêtre
            wrefresh(win_cpu);
            wrefresh(win_p_name);
            wrefresh(win_p_state);
            wrefresh(win_p_thread);
            wrefresh(win_p_virtualsize);
            wrefresh(win_pid);
            wrefresh(win_ppid);
        } else if (ch == 'q' || ch == 'Q') {  // Si la touche 'Q' est pressée
            endwin();
            is_running = false;
        }
        
    }

    return 0;
}