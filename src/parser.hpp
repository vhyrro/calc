#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>

namespace Parser
{
    enum class TokenType
    {
        NONE,
        ERROR,
        NUMBER,

        BRACKET_OPEN,
        BRACKET_CLOSE,

        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
    };

    struct Token
    {
        Token(TokenType type, const std::string& value) : Type(type), Value(value) {}

        TokenType Type;
        const std::string Value;
    };

    struct BinaryOperation
    {
        Token Left, Operator, Right;
    };

    /* struct PrecedentedBinaryOperation
    {
        Token Left, Operator, Right;
    };

    union Expression
    {
        BinaryOperation Operation;
    }; */

    const std::vector<Token> scan(const std::string& input);
    std::optional<std::string_view> error_check(const std::vector<Token>& tokens);

    std::ostream& operator<<(std::ostream& os, const std::vector<Token>& tokens);
}
