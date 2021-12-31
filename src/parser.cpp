#include "parser.hpp"

#include <iostream>
#include <optional>
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

std::optional<std::string> Parser::error_check(const std::vector<Token>& tokens)
{
    uint32_t bracket_count = 0;

    for (size_t i = 0; i < tokens.size(); i++)
    {
        const Token& token = tokens[i];

        if (token.Type == TokenType::BRACKET_OPEN || token.Type == TokenType::BRACKET_CLOSE)
            ++bracket_count;
        else if (token.Type == TokenType::ERROR)
            return "Malformed input, expected either a number or mathematical operand, got '" + token.Value + "' instead.";
        else if (token.Type >= TokenType::PLUS)
        {
            if (i == 0)
                return "Expected value before '" + token.Value + "'";
            else if (i + 1 == tokens.size())
                return "Expected value after '" + token.Value + "'";

            const Token& prev_token = tokens[i - 1], next_token = tokens[i + 1];

            if (prev_token.Type != TokenType::NUMBER)
                return "Expected number on left side of '+', got '" + prev_token.Value + "' instead";
            else if (next_token.Type != TokenType::NUMBER)
                return "Expected number on right side of '+', got '" + next_token.Value + "' instead";
        }
    }

    if (bracket_count % 2 != 0)
        return "Unclosed bracket";

    return std::nullopt;
}

std::ostream& Parser::operator<<(std::ostream& os, const std::vector<Token>& tokens)
{
    for (const auto& token : tokens)
        os << "(" << (int)token.Type << ", '" << token.Value << "'), ";

    return os;
}
