#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>
using namespace std;
void print_info(const char* path, FILE* file){
    pid_t pid = getpid();
    fprintf(file, "%s:\n PID: %d\n parent PID: %d\n", path, pid, getppid());
    fprintf(file, "ID process session: %d\n", getsid(pid));
    fprintf(file, "ID group of processes: %d\n", getpgid(pid));
    fprintf(file, "Real user ID: %d\n", getuid());
    fprintf(file, "effective user ID: %d\n", geteuid());
    fprintf(file, "real group ID: %d\n", getgid());
    fprintf(file, "effective group ID: %d\n", getegid());
    fprintf(file, "-------\n");
}
int main(int argc, char* argv[]){
    const char* path = argv[0];
    FILE* file = fopen(path, "a");
    pid_t pid = getpid();
    file = fopen(path , "a");
    print_info("child2 ", file);
    fprintf(file, "untitled programm. My PID: %d\n", pid);
    fprintf(file, "-------\n");
    fclose(file);
    return 0;
}
