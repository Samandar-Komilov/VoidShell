#include <iostream>
#include <vector>
#include <string.h>

#include "../include/command_parser.h"

using namespace std;


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