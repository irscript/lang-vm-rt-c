#ifndef __TOKEN__H__
#define __TOKEN__H__

#include "TkEnum.hpp"
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <string>
namespace air
{
    struct TokPos
    {
        uint32_t pos;
        uint32_t line;

        TokPos(uint32_t pos = 0, uint32_t line = 0)
            : pos(pos), line(line) {}

        std::string toString() const
        {
            std::stringstream ss;

            ss << " [ line: ";
            ss << line;
            ss << " ,pos ";
            ss << pos;
            ss << " ]";
            return ss.str();
        }
    };

    struct Token
    {
        std::string txt;
        TokPos pos;
        TkKeyWord kind;
        union
        {
            TkAnnotate ann;
            TkKeyWord key;
            TkSpEnum sp;
            TkOpEnum op;
        } code;
        union
        {
            uint32_t i32;
            uint64_t i64;
            float f32;
            double f64;
        } val;
    };
}
#endif //!__TOKEN__H__