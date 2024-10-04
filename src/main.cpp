#include <iostream>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE 1024

using namespace std;


int main(){
    cout << "🎉 Welcome to VoidShell!\n" << endl;

    /*
    - voidsh> interface
    - command identification strtok(), argument parsing and exit checking
    */
    char commandbuff[BUFFSIZE];

    while (true){
        string input;
        cout << "voidsh> ";

        // getline() - Read the entire line, with spaces and special chars into a single string
        getline(cin, input);

        if (input == "exit"){
            break;
        }

        // Read command and arguments
        

        // fork() a new process

        // execute command in that child process using execvp

        // wait until that process terminates

        // Restart the job, until user enters `exit` or CTRL+C signal
    }

    return EXIT_SUCCESS;
}