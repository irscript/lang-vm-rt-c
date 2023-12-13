#ifndef __CHARSTREAM__H__
#define __CHARSTREAM__H__

#include <cassert>
#include <cstdint>
#include <string>

#include <cstdio>

#include "utils/fileHelper.hpp"
namespace air
{
    // 字符封装
    struct Char
    {
        uint32_t pos; // 在字符流的位置
        uint32_t val; // 字符值

        inline Char(uint32_t pos, uint32_t ch)
            : pos(pos), val(ch) {}

        inline bool isalpha() const { return ::isalpha(val); } // 字母？
        inline bool isdigit() const { return ::isdigit(val); } // 数字
        inline bool isalnum() const { return ::isalnum(val); } // 数字和字母？

        inline bool isalpha_() const { return val == '_' || ::isalpha(val); } // 字母、下划线_？
        inline bool isalnum_() const { return val == '_' || ::isalnum(val); } // 字母、下划线_、数字？

        // 空白字符？
        inline bool isWhiteSpace() const
        {
            switch (val)
            {
            case ' ':
            case '\t':
            case '\v':
            case '\r':
            case '\n':
                return true;
            }
            return false;
        }

        // 空字符？
        inline bool isNull() const { return val == '\0'; }
        // 16进制字符
        inline bool isHex() const
        {
            if ('a' <= val && val <= 'f')
                return true;
            if ('A' <= val && val <= 'F')
                return true;
            return isdigit();
        }
        // 8进制字符
        inline bool isOct() const
        {
            return '0' <= val && val <= '7';
        }
        // 2进制字符
        inline bool isBin() const { return '0' == val || '1' == val; }

        // 字符判断
        inline bool isChar(uint32_t ch) const { return val == ch; }
        // 转义字符
        uint32_t escape() const
        {
            switch (val)
            {
            case '\\':
                return '\\';
            case '"':
                return '"';
            case '0':
                return '\0';
            case 'a':
                return '\a';
            case 'b':
                return '\b';
            case 'f':
                return '\f';
            case 'n':
                return '\n';
            case 'r':
                return '\r';
            case 't':
                return '\t';
            case 'v':
                return '\v';
            }
            return -1;
        }
    };

    // 字符串流
    struct CharStream
    {
        CharStream() {}

        // 打开文件
        bool open(const std::string &path)
        {
            index = 0;
            return ReadFile(path, data);
        }

        // 设置字符串数据
        inline void setData(const std::string &str)
        {
            data = str;
            index = 0;
        }
        inline std::string &getData() { return data; }
        // 获取字符串中的一段
        std::string getSbu(uint32_t start, uint32_t end)
        {
            assert(start < end);
            return data.substr(start, end - start);
        }

        uint32_t getpos() const { return index; }

        // 获取下一字符
        Char next()
        {
            if (index < data.size())
            {
                uint32_t pos = index;
                uint32_t ch = (uint8_t)data[pos];
                ++index;
                return Char(pos, ch);
            }
            return Char(data.size(), 0);
        }
        // 退回字符
        void back(Char ch)
        {
            index = ch.pos;
            assert(index <= data.size());
        }
        // 匹配一个字符
        bool match(char ch, int off)
        {
            if (index + off > data.size())
                return false;
            return data[index + off] == ch;
        }

    private:
        std::string data; // 字符串数据
        uint32_t index;   // 位置索引
    };
}
#endif //!__CHARSTREAM__H__