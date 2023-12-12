+++
title = '字符抽象'
weight = 1
autonumbering = true
+++

字符抽象是编译器在处理源代码时的一种重要机制。在编程中，我们使用的字符实际上可以被看作是特定的整数值（通常是ASCII值或者Unicode值）。编译器在读取源代码时，会将这些字符转换成对应的整数值，并进行相应的操作。

例如，在C语言中，我们可以使用字符字面量来表示单个字符，如'a'或'5'。编译器会将这些字符字面量解析为它们对应的整数值，并在需要的时候将其转换回字符形式。

此外，编译器还会对字符串进行特殊的处理。在C语言中，字符串实际上是字符数组，每个元素都包含了字符的整数值。当编译器遇到一个字符串字面量，如"Hello, world!"，它会创建一个包含所有字符的数组，并在末尾添加一个空字符（其整数值通常为0），以表示字符串的结束。

总的来说，字符抽象使得编译器能够有效地处理文本数据，并且不需要程序员关注底层的细节。通过这种方式，程序员可以更加专注于编写逻辑清晰、易于维护的代码。

## 好处

在词法分析中，对字符抽象的好处主要体现在以下几个方面：
<ol>
    <li> <b>简化处理逻辑</b>：通过将输入的字符序列转换为一个更高级别的表示（如单词或符号），编译器可以忽略掉字符编码的细节，简化处理过程。例如，无论源代码使用的是ASCII还是Unicode编码，编译器都可以将其统一视为一个整数值流。</li>
    <li> <b>提高识别效率</b>：通过对字符进行分类和归类，可以更快地识别出有意义的单词和符号。比如，在识别关键字时，只需要检查某个字符串是否与预定义的关键字列表匹配即可，而不需要关心每个字符的具体值。</li>
    <li> <b>便于错误检测</b>：词法分析阶段通常会首先执行错误检测，如检查拼写错误、未闭合的括号等。使用字符抽象可以帮助编译器更容易地定位这些问题，并提供有用的错误信息。</li>
    <li> <b>减少后续阶段的工作量</b>：对字符进行抽象后生成的词法单元是语法分析阶段的主要输入。如果在词法分析阶段就能够正确地区分不同类型的词素（如标识符、数字、运算符等），那么语法分析阶段就可以直接使用这些词素，而不需要重新处理原始的字符数据。</li>
    <li> <b>支持跨平台编译</b>：对于不同的操作系统和硬件平台，可能使用的字符编码不同。通过在词法分析阶段进行字符抽象，编译器可以在一定程度上独立于具体的字符编码，从而提高代码的可移植性。</li>
</ol>
通过字符抽象，词法分析器能够以一种更加高效且平台无关的方式处理源代码，使得整个编译过程更加可靠和健壮。

## 实现

```c++
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
```

