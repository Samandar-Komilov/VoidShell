#include <iostream>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "../include/executor.h"

using namespace std;

void execute_single_command(vector<char*> args){
    int stdout_fd = dup(STDOUT_FILENO);
    int stdin_fd = dup(STDIN_FILENO);
    int flag = 0;

    for (int i=0; args[i] != nullptr; ++i){
        if (strcmp(args[i], ">") == 0){
            // Output redirection
            int fd = open(args[i+1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            flag = 1;
            args[i] = nullptr;
            args[i+1] = nullptr;
            break;
        }
        else if (strcmp(args[i], "<") == 0){
            // Input redirection
            int fd = open(args[i+1], O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
            flag = -1;
            args[i] = nullptr;
            args[i+1] = nullptr;
            break;
        }
    }

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
        if (flag>0){
            dup2(stdout_fd, STDOUT_FILENO);
        }
        else if (flag<0){
            dup2(stdin_fd, STDIN_FILENO);
        }
        close(stdout_fd);
        close(stdin_fd);
    }
}