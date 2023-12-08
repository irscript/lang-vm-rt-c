#ifndef __LEXER__H__
#define __LEXER__H__

#include "CharStream.hpp"

struct Lexer
{
    Lexer(CharStream *ics = nullptr) : line(1), stream(ics) {}

private:
    uint32_t line;      // 行计数
    CharStream *stream; // 输入流
};

#endif //!__LEXER__H__