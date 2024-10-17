#pragma once

#include <string>

class Transition {
public:
    Transition(std::string line);

    friend std::ostream& operator<<(std::ostream& out, const Transition& transition);

private:
    std::string from_state;
    char input_read;
    char stack_read;
    std::string to_state;
    std::string stack_write;
};
