
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main(int argc, char **argv) {
    pid_t pid;
    ofstream fout;
    char *args[4];  //arguments for execve with initial counter
    args[0] ="./child";
    args[1] = "0"; //initial counter
    args[2] = "1";  //start identifier
    args[3] = argv[1]; //period of the internal counter(int milliseconds)
    ofstream output_file ("output.txt", ios::out | ios::trunc);
    int status;
    cout << "Starting Parent process (counting period 1 Sec)" << endl;
    cout << "id of the parent: " << getpid() << endl;
    output_file << "Starting Parent process (counting period 1 Sec)" << endl;
    output_file << "id of the parent: " << getpid() << endl;
    output_file.close();
    while (true) {
        switch (pid = fork()) {
            case -1: {
                perror("fork");
                exit(1);
            }
            case 0: {
                execve(args[0], args, NULL);
            }
            default:
                wait(&status);
                args[2] = "0";
                fout.open("output.txt", ios::out | ios::app);
                cout << "\"Child\" process killed by SIGTERM from console and re-started by \"Parent\" process: " << endl;
                fout << "\"Child\" process killed by SIGTERM from console and re-started by \"Parent\" process: " << endl;
                fout.close();

        }
    }
}

