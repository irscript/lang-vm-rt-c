#ifndef __CHARSTREAM__H__
#define __CHARSTREAM__H__

#include <string>
#include <cassert>
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
};

// 字符串流接口
struct ICharStream
{
    ICharStream() : index(0) {}
    virtual ~ICharStream() {}
    // 获取字符串中的一段
    virtual std::string getSbu(uint32_t start, uint32_t end) = 0;

    // 获取下一字符
    virtual Char next() = 0;
    // 退回字符
    virtual void back(Char ch) = 0;

protected:
    uint32_t index; // 位置索引
};

// 字符串流
struct CharStreamImp : public ICharStream
{
    CharStreamImp() : ICharStream() {}

    // 设置字符串数据
    inline void setData(const std::string &str)
    {
        data = str;
        index = 0;
    }
    inline std::string &getData() { return data; }
    // 获取字符串中的一段
    virtual std::string getSbu(uint32_t start, uint32_t end) override
    {
        assert(start < end);
        return data.substr(start, end - start);
    }

    // 获取下一字符
    virtual Char next() override
    {
    }
    // 退回字符
    virtual void back(Char ch) override
    {
        index = ch.pos;
        assert(index < data.size());
    }

private:
    std::string data; // 字符串数据
};

// 文件字符流
struct FileStreamImp : public ICharStream
{
    FileStreamImp() : ICharStream() {}

    // 获取字符串中的一段
    virtual std::string getSbu(uint32_t start, uint32_t end) override
    {
        assert(start < end);
        return {};
    }

    // 获取下一字符
    virtual Char next() override
    {
        return {};
    }
    // 退回字符
    virtual void back(Char ch) override
    {
    }

private:
};

#endif //!__CHARSTREAM__H__