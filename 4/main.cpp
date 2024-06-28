#include <iostream>
#include <pthread.h>
#include <stdlib.h>
using namespace std;
typedef struct argument{
    FILE* file;
    char* estr;
}args;
void* start_routine (void* tmp_arg){
    args* arg = (args*) tmp_arg;
    if(fputs(arg->estr, arg->file) == EOF){
        perror("write file error...");
        pthread_exit(nullptr);
    }
    pthread_exit(nullptr);
}
int main(){
    FILE* file = nullptr;
    pthread_t thread1, thread2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    args arg1, arg2;
    if ((file = fopen("testFolder/t2.txt", "r")) == nullptr ||
    (arg1.file = fopen("testFolder/first.txt", "w")) == nullptr ||
    (arg2.file = fopen("testFolder/second.txt", "w")) == nullptr)
    perror("open file error...");
    char line1[256], line2[256];
    while (true){
        if ((arg1.estr = fgets(line1, sizeof(line1), file))){
            pthread_create(&thread1, &attr, &start_routine, (void*)&arg1);
        }
        if ((arg2.estr = fgets(line2, sizeof(line2), file))){
            pthread_create(&thread2, &attr, &start_routine, (void*)&arg2);
        }
        pthread_join(thread1, nullptr);
        pthread_join(thread2, nullptr);
        if (arg1.estr == nullptr || arg2.estr == nullptr){
            if (feof(file) != 0){
            cout << "read finish!" << endl;
            break;
            }
            else {
            cout << "error when read..." << endl;
            break;
            }
        }
    }
    pthread_attr_destroy(&attr);
    fclose(file);
    fclose(arg1.file);
    fclose(arg2.file);
    return 0;
}
