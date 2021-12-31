#include "parser.hpp"

#include <iostream>
#include <sstream>

using namespace Parser;

const std::vector<Token> Parser::scan(const std::string& input)
{
    std::vector<Token> resulting_symbols;
    std::ostringstream ss;
    TokenType resulting_token = TokenType::ERROR;

    auto end_token = [&]
    {
        resulting_symbols.emplace_back(resulting_token, ss.str());
        ss.str("");
    };

    for (char c : input)
    {
        if ((c >= '0' && c <= '9') || c == '.')
        {
            resulting_token = TokenType::NUMBER;
            ss << c;
            continue;
        }
        else if (resulting_token == TokenType::NUMBER)
            end_token();

        switch(c)
        {
        case '+':
            resulting_token = TokenType::PLUS;
            break;
        case '-':
            resulting_token = TokenType::MINUS;
            break;
        case '*':
            resulting_token = TokenType::MULTIPLY;
            break;
        case '/':
            resulting_token = TokenType::DIVIDE;
            break;
        case '(':
            resulting_token = TokenType::BRACKET_OPEN;
            break;
        case ')':
            resulting_token = TokenType::BRACKET_CLOSE;
            break;
        case ' ':
        case '\t':
            resulting_token = TokenType::NONE;
            continue;
        }

        ss << c;
        end_token();
    }

    end_token();

    return resulting_symbols;
}

std::optional<std::string_view> Parser::error_check(const std::vector<Token>& tokens)
{
    return std::nullopt;
}

std::ostream& Parser::operator<<(std::ostream& os, const std::vector<Token>& tokens)
{
    for (const auto& token : tokens)
        os << "(" << (int)token.Type << ", '" << token.Value << "'), ";

    return os;
}
