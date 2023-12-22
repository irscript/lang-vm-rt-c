#ifndef __LEXER__H__
#define __LEXER__H__

#include "CharStream.hpp"
#include "Token.hpp"

namespace air
{
    struct Lexer
    {
        Lexer(CharStream &ics) : pos(0, 1), stream(ics) {}

        // 获取词元
        Token getNext();
        // 退回词元
        inline void backToken(Token &tok)
        {
            stream.back(Char(tok.pos.pos, 0));
            pos = tok.pos;
        }
        inline TokPos getPos() const { return pos; }
        // 跳过空白字符
        inline void SkipWhiteSpaces()
        {
            Char ch = stream.next();
            while (ch.isWhiteSpace())
            {
                if (ch.val == '\n')
                    pos.line++;
                ch = stream.next();
            }
            stream.back(ch);
        }
        // 获取字符串
        inline std::string getSub(uint32_t start, uint32_t end) { return stream.getSbu(start, end); }
        inline std::string getLineTxt(uint32_t line, uint32_t start, uint32_t end) { return stream.getLineTxt(line, start, end); }

    private:
        // 解析一个单词
        Token GetToken();

        // 解析标识符和普通关键字
        Token GetIdent();
        // 解析注解关键字
        Token GetAnnotate();
        // 解析字符常量
        Token GetChar();
        // 解析字符串常量
        Token GetString(bool escape);
        // 解析整数或者浮点常量
        Token GetDigit();
        // 解析浮点数
        Token GetFltNumber(Token &tok);
        // 解析操作符或者分隔符
        Token GetOperator();
        // 解析分隔符
        Token GetSeparator(Token &tok, uint32_t val);
        // 解析一个单行注释
        Token GetSinglineComment(Token &tok);
        // 解析多行注释
        Token GetMultilineComment(Token &tok);

    private:
        TokPos pos;         // 当前解析位置
        CharStream &stream; // 输入流
    };
}

#endif //!__LEXER__H__