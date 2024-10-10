#pragma once

#include <string>
#include <vector>

class Transition {
public:
    Transition();
    Transition(std::string line);

private:
    std::string from_state;
    char input_read;
    char stack_read;
    std::string to_state;
    std::vector<char> stack_write;
};