#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std;
typedef struct fork_delay{
    int parent;
    int childfork;
    int childvfork;
} delay;
delay input_delays(){
    delay del;
    cout << "Input delays..." << endl;
    cout << "parent: "; cin >> del.parent;
    cout << "\nchild1: "; cin >> del.childfork;
    cout << "\nchild2: "; cin >> del.childvfork;
    return del;
}
void print_pid(const char* path, FILE* file){
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

int main(int argc, char *argv[]){
    FILE* file = nullptr;
    delay del;
    char path[256];
    cout << "File: "; cin >> path; cout << endl;
    //const char* path = "testFolder/t2.txt";
    del = input_delays();
    if ((file = fopen(path, "w")) == nullptr){
        perror("open file");
    }
    cout << "opened..." << endl;
    fprintf(file, "Delays\n Parent: %d sec, Child 1 fork: %d sec, Child 2 vfork: %d sec\n\n",
    del.parent, del.childfork, del.childvfork);
    fclose(file);
    int child1 = fork();
    if (child1 == -1) {return errno;}
    else if (child1 == 0) {
        sleep(del.childfork);
        file = fopen(path , "a");
        print_pid("child1 ", file);
        fclose(file);
        exit(EXIT_SUCCESS);
    }
    else{
        int child2;
        child2 = vfork();
        if (child2 == -1) {return errno;}
        else if (child2 == 0){
            sleep(del.childvfork);
            if (execl("untitled", path, NULL) < 0){
                perror("file 'untitled'...");
                exit(2);
            }
        }
        else{
            sleep(del.parent);
            file = fopen(path, "a");
            print_pid("parent ", file);
            fclose(file);
            waitpid(child1, 0, 0);
            waitpid(child2, 0, 0);
            cout << "DONE" << endl;
        }
    }
    return 0;
}
