#include <iostream>
#include "../include/signal_handlers.h"

using namespace std;


void sigint_handler(int sig){
    cout << "\n⛔️ Shell terminated using CTRL+C signal." << endl;
    exit(EXIT_SUCCESS);
}