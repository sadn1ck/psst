#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define TRUE 1
#define FALSE 0
#define BUF_SIZE 1000
#define num long long int

typedef struct proc_display_details {
    num pid;
    char tcomm[PATH_MAX];
    char state;
    num ppid;
} pdd;

// helper functions to read a single unit at a time
void
readone(num* x, FILE* input)
{
    fscanf(input, "%lld ", x);
}
void
readstr(char* x, FILE* input)
{
    fscanf(input, "%s ", x);
}
void
readchar(char* x, FILE* input)
{
    fscanf(input, "%c ", x);
}

// check if /proc/[id] id is a number, then its a process
int
is_process(char* str)
{
    int j = 0;
    while (str[j] != '\0') {
        if (!isdigit(str[j])) {
            return FALSE;
        }
        j++;
    }
    return TRUE;
}

// string slice: https://stackoverflow.com/a/63990303/13162096
// pretty table print process details
void
print_proc_details(pdd proc)
{
    size_t len = strlen(proc.tcomm);
    char clean_name[len];
    memset(clean_name, '\0', sizeof(clean_name));
    strncpy(clean_name, proc.tcomm + (size_t)1, len - 2);
    printf("%20s | %6llu | %6llu | %5c \n", clean_name, proc.pid, proc.ppid, proc.state);
}

pdd
get_proc_details(char* stat_path, struct dirent* process)
{
    strcpy(stat_path, "/proc/");
    strcat(stat_path, process->d_name);
    strcat(stat_path, "/stat");

    FILE* fp;

    fp = fopen(stat_path, "r");
    if (fp == NULL) {
        perror("fopen");
    }
    
    pdd read_proc;
    readone(&(read_proc.pid), fp);
    readstr(read_proc.tcomm, fp);
    readchar(&(read_proc.state), fp);
    readone(&(read_proc.ppid), fp);
    fclose(fp);
    return read_proc;
}

int
main()
{
    DIR* procdir;
    struct dirent* process;
    procdir = opendir("/proc");
    if (procdir == NULL) {
        perror("opendir");
        return 1;
    }
    char stat_path[BUF_SIZE];
    // process /proc/[pid]/stat details
    // https://man7.org/linux/man-pages/man5/proc.5.html
    printf("%20s | %6s | %6s | %5s \n", "PROC", "PID", "PPID", "STATE");
    while ((process = readdir(procdir)) != NULL) {
        if (is_process(process->d_name)) {
            pdd read_proc = get_proc_details(stat_path, process);
            print_proc_details(read_proc);
        }
    }
    closedir(procdir);
}
