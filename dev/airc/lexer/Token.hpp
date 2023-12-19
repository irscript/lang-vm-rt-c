#ifndef __TOKEN__H__
#define __TOKEN__H__

#include "TkEnum.hpp"
#include "utils/pch.hpp"

#include "airc/base/mapTable.hpp"
namespace air
{
    struct TokPos
    {
        uint32_t pos;  // 起始位置
        uint32_t line; // 行号

        TokPos(uint32_t pos = 0, uint32_t line = 0)
            : pos(pos), line(line) {}

        std::string toString() const
        {
            std::stringstream ss;

            ss << line;
            ss << ":";
            ss << pos;

            return ss.str();
        }
    };

    struct Token
    {
        std::string txt; // 词元对应的文本
        TokPos pos;      // 词元的起始位置
        TkKind kind;     // 词元的类别
        union
        {
            TkAnnotate ann;
            TkKeyWord key;
            TkSpEnum sp;
            TkOpEnum op;
        } code; // 词元编码
        union
        {
            uint32_t i32;
            uint64_t i64;
            float f32;
            double f64;
        } val; // 词元常量值
        // std::string str; // 词元对应的字符串常量

        Token(TkKind kind = TkKind::Unknown) : kind(kind)
        {
            code.key = (TkKeyWord::Unknown);
            val.i64 = (0);
        }

        inline auto getTxt() const { return txt.c_str(); }

        std::string toString() const
        {
            std::stringstream ss;

            ss << txt;
            ss << ":";
            ss << pos.line;
            ss << ":";
            ss << pos.pos;
            return ss.str();
        }

        inline void addchar(uint32_t ch)
        {
            txt.push_back(ch);
        }

        // 检查普通关键字
        inline bool checkKeyword()
        {
            auto reskey = MapTable::findKeyword(txt);
            if (TkKeyWord::Unknown != reskey)
            {
                kind = TkKind::KeyWord;
                code.key = reskey;
                return true;
            }
            kind = TkKind::Identifier;
            return false;
        }
        // 检查注解关键字
        inline bool checkAnnword()
        {
            auto resann = MapTable::findAnnword(txt);
            if (TkAnnotate::Unknown != resann)
            {
                kind = TkKind::Annotate;
                code.ann = resann;
                return true;
            }
            return false;
        }
        // 是否标识符
        inline bool isIdentity() const
        {
            return TkKind::Identifier == kind;
        }
        // 是否普通关键字 key
        inline bool isKeyword(TkKeyWord key) const
        {
            return TkKind::KeyWord == kind && key == code.key;
        }
        // 是否标注关键字 ann
        inline bool isAnnotate(TkAnnotate ann) const
        {
            return TkKind::Annotate == kind && ann == code.ann;
        }
        // 是否操作符 op
        inline bool isOperator(TkOpEnum op) const
        {
            return TkKind::Operator == kind && op == code.op;
        }
        // 是否分隔符 sp
        inline bool isSeparator(TkSpEnum sp) const
        {
            return TkKind::Separator == kind && sp == code.sp;
        }

        // 是否字符串
        inline bool isString() const
        {
            return TkKind::StringLiteral == kind || TkKind::StringLiteral2 == kind;
        }
    };
}
#endif //!__TOKEN__H__