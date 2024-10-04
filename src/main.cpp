#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <csignal>

#define BUFFSIZE 1024

using namespace std;


// Signal handlers
void sigint_handler(int sig); // CTRL+C handler

// Function prototypes
vector<char*> parseInput(string input);


int main(){
    signal(SIGINT, sigint_handler);

    cout << "🎉 Welcome to VoidShell!\n" << endl;

    while (true){
        string input;
        cout << "voidsh> ";

        // getline() - Read the entire line, with spaces and special chars into a single string
        getline(cin, input);

        if (input == "exit"){
            break;
        }

        // Read command and arguments
        vector<char*> args = parseInput(input);

        // fork() a new process
        pid_t pid = fork();
        if (pid < 0){
            cerr << "Fork failed!" << endl;
            continue;
        }
        else if (pid == 0){
            // execute command in that child process using execvp
            if (execvp(args[0], &args[0]) < 0){
                cerr << "Command execution failed: No such command or argument exist." << endl;
            }
            cout << "DEBUG: " << &args[1] << endl;
            exit(1);
        }
        else {
            // wait until that process terminates
            waitpid(pid, nullptr, 0);
        }

        // Restart the job, until user enters `exit` or CTRL+C signal
    }

    return EXIT_SUCCESS;
}

vector<char*> parseInput(string input){
    vector<char*> args;
    char* token = strtok(&input[0], " ");
    while (token != nullptr){
        args.push_back(token);
        token = strtok(nullptr, " ");
    }
    args.push_back(nullptr);

    return args;
}

void sigint_handler(int sig){
    cout << "\n⛔️ Shell terminated using CTRL+C signal." << endl;
    exit(EXIT_SUCCESS);
}