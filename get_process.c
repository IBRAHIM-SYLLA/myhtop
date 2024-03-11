#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "get_process.h"
#include "split.h"


double get_cpu_usage() {
    double res = 0;

    char* path = "/proc/stat";
    // FILE* out = fopen("cpu.txt", "w+");
    FILE* f = fopen(path, "r");
    if(f == NULL) {
        fprintf(stderr, "Error: Cannot load file %s\n", path);
        // exit(EXIT_FAILURE);
    }

    char* content = malloc(sizeof(char) * 1024);

    int i = 0;
    char c;
    while(i < 1023 && (c = fgetc(f)) != EOF) {
        // fputc(c, out);
        content[i] = c;
        i++;
    }
    content[i] = '\0';

    char** words = split(content);
    res = atof(words[1]);
    

    fclose(f);
    // fclose(out);

    return res; 
}


proces get_process(int pid) {
    proces res;

    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/stat", pid);

    FILE* f = fopen(path, "r");
    // FILE* out = fopen("output.txt", "w");
    if(f == NULL) {
        fprintf(stderr, "Error: Cannot load file %s\n", path);
        exit(EXIT_FAILURE);
    }

    char* content = malloc(sizeof(char) * 1024);

    int i = 0;
    char c;
    while((c = fgetc(f)) != EOF) {
        if(i >= 1024 - 1) {
            fprintf(stderr, "Error: File too large\n");
            exit(EXIT_FAILURE); 
        }
        // fputc(c, out);
        content[i] = c;
        i++;
    }
    content[i] = '\0';

    fclose(f);
    // fclose(out);

    char** words = split(content);
    for(int j = 0; words[j] != NULL; j++) {
        res.name = words[1];
        res.ppid = atoi(words[0]);
        res.ppid = atoi(words[3]);
        res.state = words[2];
        res.threads = atoi(words[19]);
        res.virtualSize = atoi(words[22]);
    }

    return res;
}