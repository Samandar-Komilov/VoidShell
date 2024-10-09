#include <gtest/gtest.h>
#include "../include/executor.h"
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

TEST(ShellTest, OutputRedirectionTest){
    vector<char*> args = {(char*)"echo", (char*)"Hello", (char*)">", (char*)"output.txt", nullptr};

    execute_single_command(args);

    ifstream file("output.txt");
    string output;
    getline(file, output);
    
    EXPECT_EQ(output, "Hello");
    file.close();
}

TEST(ShellTest, InputRedirectionTest) {
    // Prepare a file to be used as input
    std::ofstream file("input.txt");
    file << "Hello from file";
    file.close();

    // Prepare arguments
    vector<char*> args = {(char*)"cat", (char*)"<", (char*)"input.txt", nullptr};

    // Redirect stdout to a string for comparison
    int stdout_fd = dup(STDOUT_FILENO);
    int fd[2];
    pipe(fd);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);

    // Run the command
    execute_single_command(args);

    // Restore stdout
    dup2(stdout_fd, STDOUT_FILENO);

    // Read the output from the pipe
    char buffer[128];
    close(fd[1]);

    
    int nbytes = read(fd[0], buffer, sizeof(buffer) - 1);
    buffer[nbytes] = '\0';

    // Verify that the output matches the file contents
    EXPECT_STREQ(buffer, "Hello from file");
}


int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}