#include <sstream>

#include "Transition.hpp"

Transition::Transition(std::string line) {
    std::stringstream line_stream(line);
    line_stream >> from_state;
    line_stream >> input_read;
    line_stream >> stack_read;
    line_stream >> to_state;
    line_stream >> stack_write;
}
