#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <csignal>

#include "../include/command_parser.h"
#include "../include/executor.h"
#include "../include/signal_handlers.h"

using namespace std;


int main(){
    signal(SIGINT, sigint_handler);
    vector<char*> args;

    cout << "🎉 Welcome to VoidShell!\n" << endl;

    while (true){
        string input;
        cout << "voidsh> ";

        getline(cin, input);
        if (input == "exit"){
            break;
        }

        args = parseInput(input);
        
        execute_single_command(args);

        // Restart the job, until user enters `exit` or CTRL+C signal
    }

    return EXIT_SUCCESS;
}