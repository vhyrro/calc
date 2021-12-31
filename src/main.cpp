#include <iostream>

#include "parser.hpp"

int main()
{
    bool repl_alive = true;

    // Allocate once, be joyful forever
    std::string input;

    while (repl_alive)
    {
        // REPL Loop
        std::cout << "> " << std::flush;
        std::getline(std::cin, input);

        if (input.find("exit") != std::string::npos)
            return 0;

        const auto parsed_text = Parser::scan(input);

        std::cout << parsed_text << '\n'
            << Parser::error_check(parsed_text).value_or("No error")
            << std::endl;
    }

    return 0;
}
