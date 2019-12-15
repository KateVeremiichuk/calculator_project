#include <exception>
#include <iomanip>
#include <iostream>
#include <string>

#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"

int main()
{
    std::cout << std::setprecision(16);

    while (true)
    {
        std::cout << "$ ";

        std::string line;
        if (!std::getline(std::cin, line))
        {
            break;
        }

        Parser::CParser parser{std::make_unique<Lexer::CLexer>(line)};

        try
        {
            auto node = parser.parse();
            std::cout << node->eval() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "error: " << e.what() << std::endl;
        }
    }

    return 0;
}
