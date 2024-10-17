#pragma once

#include <string>

class Transition {
public:
    Transition(std::string line);

    const std::string& get_from_state() const { return from_state; }
    const char& get_input_read() const { return input_read; }
    const char& get_stack_read() const { return stack_read; }
    const std::string& get_to_state() const { return to_state; }
    const std::string& get_stack_write() const { return stack_write; }

    friend std::ostream& operator<<(std::ostream& out, const Transition& transition);

private:
    std::string from_state;
    char input_read;
    char stack_read;
    std::string to_state;
    std::string stack_write;
};
