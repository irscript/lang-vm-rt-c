#include "Lexer.hpp"
#include "utils/errorWhat.hpp"
namespace air
{
    Token Lexer::getNext()
    {
        // return GetToken();
        while (true)
        {
            auto tok = GetToken();
            if (tok.kind == TkKind::SingleComments || tok.kind == TkKind::MultipleComments)
                continue;
            pos = tok.pos;
            return tok;
        }
        return Token();
    }

    Token Lexer::GetToken()
    {
        SkipWhiteSpaces();

        Char ch = stream.next();

        // 解析结束
        if (ch.isNull())
            return Token(TkKind::EOS);

        // 标识符
        if (ch.isalpha_())
        {
            stream.back(ch);
            return GetIdent();
        }
        // 数字常量
        if (ch.isalnum())
        {
            stream.back(ch);
            return GetDigit();
        }

        switch (ch.val)
        {
            // 标注关键字
        case '@':
        {
            Char ch2 = stream.next();
            if (ch2.val == '"')
                return GetString(true);
            stream.back(ch);
            return GetAnnotate();
        }

            // 字符常量
        case '\'':
            return GetChar();

        // 字符串常量
        case '"':
            return GetString(false);
        }
        // 分隔符和操作符
        stream.back(ch);
        return GetOperator();
    }

    Token Lexer::GetIdent()
    {
        Token tok;
        tok.pos.pos = stream.getpos();
        tok.pos.line = pos.line;
        Char ch(0, 0);
        while (true)
        {
            ch = stream.next();
            if (ch.isalnum_() == false)
            {
                stream.back(ch);
                break;
            }
            tok.addchar(ch.val);
        }
        tok.checkKeyword();
        return tok;
    }

    Token Lexer::GetAnnotate()
    {
        Token tok;
        Char ch = stream.next();
        tok.pos.pos = ch.pos;
        tok.pos.line = pos.line;
        tok.addchar(ch.val);
        while (true)
        {
            ch = stream.next();
            if (ch.isalnum_() == false)
            {
                stream.back(ch);
                break;
            }
            tok.addchar(ch.val);
        }
        if (false == tok.checkAnnword())
        {
            throw ErrorWhat::fmt("%u:%u: 未知标注：%s\n", tok.pos.line, tok.pos.pos, tok.txt.c_str());
        }
        return tok;
    }

    Token Lexer::GetChar()
    {
        Token tok(TkKind::CharLiteral);
        Char ch = stream.next();
        tok.pos.pos = ch.pos;
        tok.pos.line = pos.line;
        tok.addchar(ch.val);
        // 转义字符
        if (ch.val == '\\')
        {
            ch = stream.next();
            tok.addchar(ch.val);
            /* // 单字节字符
             if (ch.val == 'x' || ch.val == 'X')
             {
                 throw ErrorWhat::fmt("%u:%u: 暂不支持 unicode 转义\n", tok.pos.line, tok.pos.pos);
             }
             // unicode转义
             else if (ch.val == 'u' || ch.val == 'U')
             {
                 throw ErrorWhat::fmt("%u:%u: 暂不支持 unicode 转义\n", tok.pos.line, tok.pos.pos);
             }
             else*/
            // 普通转义字符
            {
                tok.val.i32 = ch.escape();
                if (-1 == tok.val.i32)
                    throw ErrorWhat::fmt("%u:%u: 未知转义字符 '\\%s'\n", tok.pos.line, tok.pos.pos, tok.txt.c_str());
            }
            return tok;
        }
        // 普通字符
        tok.val.i32 = ch.val;
        ch = stream.next();
        if (ch.val != '\'')
            throw ErrorWhat::fmt("%u:%u: 缺少符号 ‘'’\n", tok.pos.line, tok.pos.pos);
        return tok;
    }
    Token Lexer::GetString(bool escape)
    {
        Token tok(escape == true ? TkKind::StringLiteral2 : TkKind::StringLiteral);
        Char ch = stream.next();
        tok.pos.pos = ch.pos - (escape == true ? 2 : 1);
        tok.pos.line = pos.line;
        if (escape == false)
        {
            while (true)
            {
                if (ch.isNull())
                    throw ErrorWhat::fmt("%u:%u: 文件意外结束！缺少符号 ‘\"’\n",
                                         tok.pos.line, tok.pos.pos);

                // 转义字符
                if (ch.val == '\\')
                {
                    Char ch2 = stream.next();
                    if (ch2.val == '"')
                    {
                        tok.addchar(ch2.val);
                        continue;
                    }
                    stream.back(ch2);
                }
                // 是否结束
                else if (ch.val == '"')
                    break;
                tok.addchar(ch.val);
                ch = stream.next();
            }
        }
        else
        {
            while (true)
            {
                if (ch.isNull())
                    throw ErrorWhat::fmt("%u:%u: 文件意外结束！缺少符号 ‘\"’\n",
                                         tok.pos.line, tok.pos.pos);
                // 是否结束
                else if (ch.val == '"')
                    break;
                tok.addchar(ch.val);
                ch = stream.next();
            }
        }

        return tok;
    }
    Token Lexer::GetDigit()
    {
        Token tok(TkKind::UIntLiteral);
        Char ch = stream.next();
        tok.pos.pos = ch.pos;
        tok.pos.line = pos.line;
        tok.addchar(ch.val);

        if (ch.val == '0')
        {
            Char ch2 = stream.next();
            switch (ch2.val)
            {
            // 16进制
            case 'X':
            case 'x':
            {
                tok.addchar(ch2.val);
                while (true)
                {
                    ch2 = stream.next();
                    if (ch2.isHex() == false)
                    {
                        stream.back(ch2);
                        break;
                    }
                    tok.addchar(ch2.val);
                }

                if (tok.txt.empty())
                    throw ErrorWhat::fmt("%u:%u: 不完整的 16 进制数：%s\n",
                                         tok.pos.line, tok.pos.pos, tok.txt.c_str());
                tok.val.i64 = std::strtoull(&tok.txt[2], nullptr, 16);
                tok.kind = TkKind::UIntLiteral;
                return tok;
            }
            break;
                // 2进制
            case 'B':
            case 'b':
            {
                tok.addchar(ch2.val);
                while (true)
                {
                    ch2 = stream.next();
                    if (ch2.isBin() == false)
                    {
                        stream.back(ch2);
                        break;
                    }
                    tok.addchar(ch2.val);
                }
                if (tok.txt.empty())
                    throw ErrorWhat::fmt("%u:%u: 不完整的 2 进制数：%s\n",
                                         tok.pos.line, tok.pos.pos, tok.txt.c_str());
                tok.val.i64 = std::strtoull(&tok.txt[2], nullptr, 2);
                tok.kind = TkKind::UIntLiteral;
                return tok;
            }
            break;
            // 浮点数
            case '.':
            {
                tok.addchar(ch2.val);
                return GetFltNumber(tok);
            }
            break;
            // 8 进制
            default:
            {
                while (true)
                {
                    if (ch2.isOct() == false)
                    {
                        stream.back(ch2);
                        break;
                    }
                    tok.addchar(ch2.val);
                    ch2 = stream.next();
                }
                tok.val.i64 = std::strtoull(&tok.txt[1], nullptr, 8);
                tok.kind = TkKind::UIntLiteral;
                return tok;
            }
            break;
            }
        }

        // 10进制或者浮点数
        while (true)
        {
            ch = stream.next();
            if (ch.isdigit() == false)
                break;
            tok.addchar(ch.val);
        }
        // 浮点数
        if (ch.val == '.')
        {
            tok.addchar(ch.val);
            return GetFltNumber(tok);
        }
        stream.back(ch);
        // 10进制
        tok.val.i64 = std::strtoull(tok.txt.c_str(), nullptr, 10);
        return tok;
    }

    Token Lexer::GetFltNumber(Token &tok)
    {
        tok.kind = TkKind::Flt64Literal;
        Char ch = stream.next();
        while (true)
        {
            if (ch.isdigit() == false)
                break;
            tok.addchar(ch.val);
            ch = stream.next();
        }
        // 普通浮点数
        if (ch.val != 'E' && ch.val != 'e')
        {
            // 32位浮点
            if (ch.val == 'F' || ch.val == 'f')
            {
                tok.addchar(ch.val);
                tok.kind = TkKind::Flt32Literal;
                tok.val.f32 = std::strtof(tok.txt.c_str(), nullptr);
                return tok;
            }
            // 64位浮点
            stream.back(ch);
            tok.val.f64 = std::strtod(tok.txt.c_str(), nullptr);
            return tok;
        }
        // 科学计数法
        tok.addchar(ch.val);
        ch = stream.next();
        // 查看符号位
        if (ch.val == '+' || ch.val == '-')
            tok.addchar(ch.val);
        else if (ch.isdigit() == false)
            throw ErrorWhat::fmt("%u:%u: 不完整的科学计数法：%s\n",
                                 tok.pos.line, tok.pos.pos, tok.txt.c_str());
        while (true)
        {
            ch = stream.next();
            if (ch.isdigit() == false)
            {
                stream.back(ch);
                break;
            }
            tok.addchar(ch.val);
        }
        tok.val.f64 = std::strtod(tok.txt.c_str(), nullptr);
        return tok;
    }

    Token Lexer::GetOperator()
    {
        Token tok(TkKind::Operator);
        Char ch = stream.next();
        tok.pos.pos = ch.pos;
        tok.pos.line = pos.line;
        tok.addchar(ch.val);
        // 操作符
        switch (ch.val)
        {
            // 匹配 ?
        case '?':
        {
            tok.code.op = TkOpEnum::Ques;
            return tok;
        }
        break;
            // 匹配 . 、 ...
        case '.':
        {
            if (stream.match('.', 0) == true && stream.match('.', 1) == true)
            {
                tok.kind = TkKind::Separator;
                ch = stream.next();
                tok.addchar(ch.val);
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.sp = TkSpEnum::Ellipsis;
                return tok;
            }
            tok.code.op = TkOpEnum::Dot;
            return tok;
        }
        break;
        // 匹配 + 、++、+=
        case '+':
        {
            if (stream.match('+', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::Plus2;
            }
            else if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::PlusAssign;
            }
            else
                tok.code.op = TkOpEnum::Plus;
            return tok;
        }
        break;
        // 匹配 - 、--、-=、->>、->>=
        case '-':
        {
            if (stream.match('-', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::Minus2;
            }
            else if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::MinusAssign;
            }
            else if (stream.match('>', 0) == true && stream.match('>', 1) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                ch = stream.next();
                tok.addchar(ch.val);
                if (stream.match('=', 0) == true)
                {
                    ch = stream.next();
                    tok.addchar(ch.val);
                    tok.code.op = TkOpEnum::ShrAAssign;
                }
                else
                    tok.code.op = TkOpEnum::ShrA;
            }
            else
            {
                Char ch2 = stream.next();
                stream.back(ch2);
                if (ch2.isdigit() == true)
                {
                    Token tok2 = GetDigit();
                    tok.txt += tok2.txt;
                    tok.kind = tok2.kind;
                    switch (tok.kind)
                    {
                    case TkKind::UIntLiteral:
                    {
                        tok.kind = TkKind::SIntLiteral;
                        tok.val.i64 = -((int64_t)tok2.val.i64);
                    }
                    break;
                    case TkKind::Flt32Literal:
                    {
                        tok.val.f32 = -tok2.val.f32;
                    }
                    break;
                    case TkKind::Flt64Literal:
                    {
                        tok.val.f64 = -tok2.val.f64;
                    }
                    break;
                    default:
                        assert(0);
                        break;
                    }
                }
                else
                {
                    tok.code.op = TkOpEnum::Minus;
                }
            }

            return tok;
        }
        break;
        // 匹配 *、*=
        case '*':
        {
            if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::MultiplyAssign;
            }
            else
                tok.code.op = TkOpEnum::Multiply;
            return tok;
        }
        break;
        // 匹配 /、/=、单行注释、多行注释
        case '/':
        {
            // 单行注释
            if (stream.match('/', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                return GetSinglineComment(tok);
            } // 多行注释
            else if (stream.match('*', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                return GetMultilineComment(tok);
            }
            else if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::DivideAssign;
            }
            else
                tok.code.op = TkOpEnum::Divide;
            return tok;
        }
        break;
        // 匹配 %、%=
        case '%':
        {
            if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::ModulusAssign;
            }
            else
                tok.code.op = TkOpEnum::Modulus;
            return tok;
        }
        break;
        // 匹配 &、&=、&&
        case '&':
        {
            if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::BitAndAssign;
            }
            else if (stream.match('&', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::LogicalAnd;
            }
            else
                tok.code.op = TkOpEnum::BitAnd;
            return tok;
        }
        break;
        // 匹配 |、|=、||
        case '|':
        {
            if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::BitOrAssign;
            }
            else if (stream.match('|', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::LogicalOr;
            }
            else
                tok.code.op = TkOpEnum::BitOr;
            return tok;
        }
        break;
        // 匹配 ~、~=
        case '~':
        {
            if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::BitNotAssign;
            }
            else
                tok.code.op = TkOpEnum::BitNot;
            return tok;
        }
        break;
        // 匹配 ^、^=
        case '^':
        {
            if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::BitXOrAssign;
            }
            else
                tok.code.op = TkOpEnum::BitXOr;
            return tok;
        }
        break;

        // 匹配 <、<=、<<、<<=、<<)、<<)=
        case '<':
        {
            if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::LE;
            }
            else if (stream.match('<', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                if (stream.match('=', 0) == true)
                {
                    ch = stream.next();
                    tok.addchar(ch.val);
                    tok.code.op = TkOpEnum::ShlAssign;
                }
                else if (stream.match(')', 0) == true)
                {
                    ch = stream.next();
                    tok.addchar(ch.val);
                    if (stream.match('=', 0) == true)
                    {
                        ch = stream.next();
                        tok.addchar(ch.val);
                        tok.code.op = TkOpEnum::ShlRAssign;
                    }
                    else
                        tok.code.op = TkOpEnum::ShlR;
                }
                else
                    tok.code.op = TkOpEnum::Shl;
            }
            else
                tok.code.op = TkOpEnum::LT;
            return tok;
        }
        break;

        // 匹配 >、>=、>>、>>=、>>(、>>(=
        case '>':
        {
            if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::GE;
            }
            else if (stream.match('>', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                if (stream.match('=', 0) == true)
                {
                    ch = stream.next();
                    tok.addchar(ch.val);
                    tok.code.op = TkOpEnum::ShrLAssign;
                }
                else if (stream.match('(', 0) == true)
                {
                    ch = stream.next();
                    tok.addchar(ch.val);
                    if (stream.match('=', 0) == true)
                    {
                        ch = stream.next();
                        tok.addchar(ch.val);
                        tok.code.op = TkOpEnum::ShrRAssign;
                    }
                    else
                        tok.code.op = TkOpEnum::ShrR;
                }
                else
                    tok.code.op = TkOpEnum::ShrL;
            }
            else
                tok.code.op = TkOpEnum::GT;
            return tok;
        }
        break;

        // 匹配 !、!=
        case '!':
        {
            if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::NE;
            }
            else
                tok.code.op = TkOpEnum::LogicalNot;
            return tok;
        }
        break;
        // 匹配 =、==
        case '=':
        {
            if (stream.match('=', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                tok.code.op = TkOpEnum::EQ;
            }
            else
                tok.code.op = TkOpEnum::Assign;
            return tok;
        }
        break;

        } // 当作分隔符处理
        return GetSeparator(tok, ch.val);
    }
    Token Lexer::GetSeparator(Token &tok, uint32_t val)
    {
        tok.kind = TkKind::Separator;
        switch (val)
        {
            // 匹配 [
        case '[':
        {
            tok.code.sp = TkSpEnum::OpenBracket;
            return tok;
        }
        break;
        // 匹配 ]
        case ']':
        {
            tok.code.sp = TkSpEnum::CloseBracket;
            return tok;
        }
        break;
        // 匹配 (
        case '(':
        {
            tok.code.sp = TkSpEnum::OpenParen;
            return tok;
        }
        break;
        // 匹配 )
        case ')':
        {
            tok.code.sp = TkSpEnum::CloseParen;
            return tok;
        }
        break;
        // 匹配 {
        case '{':
        {
            tok.code.sp = TkSpEnum::OpenBrace;
            return tok;
        }
        break;
        // 匹配 }、};
        case '}':
        {
            if (stream.match(';', 0) == true)
            {
                stream.next();
                tok.addchar(';');
                tok.code.sp = TkSpEnum::CBSemiColon;
            }
            else
                tok.code.sp = TkSpEnum::CloseBrace;
            return tok;
        }
        break;
            // 匹配 :
        case ':':
        {
            tok.code.sp = TkSpEnum::Colon;
            return tok;
        }
        break;
        // 匹配 ;
        case ';':
        {
            tok.code.sp = TkSpEnum::SemiColon;
            return tok;
        }
        break;
        // 匹配 ,
        case ',':
        {
            tok.code.sp = TkSpEnum::Comma;
            return tok;
        }
        break;
        default:
            throw ErrorWhat::fmt("%u:%u: 未匹配词法规则的字符：%s\n",
                                 tok.pos.line, tok.pos.pos, tok.txt.c_str());
            break;
        }
        return tok;
    }

    Token Lexer::GetSinglineComment(Token &tok)
    {
        tok.kind = TkKind::SingleComments;
        Char ch = stream.next();
        while (true)
        {
            if (ch.isNull())
                break;
            else if (ch.isChar('\n'))
            {
                pos.line++;
                break;
            }
            tok.addchar(ch.val);
            ch = stream.next();
        }
        return tok;
    }

    Token Lexer::GetMultilineComment(Token &tok)
    {
        tok.kind = TkKind::MultipleComments;
        Char ch = stream.next();
        while (true)
        {
            if (ch.isNull())
                throw ErrorWhat::fmt("%u:%u: 文件意外结束！缺少符号 ‘*/’\n",
                                     tok.pos.line, tok.pos.pos);
            else if (ch.isChar('\n'))
            {
                pos.line++;
                break;
            }
            tok.addchar(ch.val);
            // 结束
            if (ch.isChar('*') == true && stream.match('/', 0) == true)
            {
                ch = stream.next();
                tok.addchar(ch.val);
                break;
            }
            ch = stream.next();
        }
        return tok;
    }

}