#include <iostream>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../include/executor.h"

using namespace std;

void execute_command(const vector<char*> args){
    // fork() a new process
    pid_t pid = fork();
    if (pid < 0){
        cerr << "Fork failed!" << endl;
    }
    else if (pid == 0){
        // execute command in that child process using execvp
        if (execvp(args[0], &args[0]) < 0){
            cerr << "Command execution failed: No such command or argument exist." << endl;
        }
        exit(1);
    }
    else {
        // wait until that process terminates
        waitpid(pid, nullptr, 0);
    }
}