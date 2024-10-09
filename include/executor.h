#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <vector>
#include <string>

using namespace std;

void execute_single_command(vector<char*> args);
int redirect_io_if_exist(vector<char*> args);

#endif