+++
title = '词元(Token)定义'
weight = 4
autonumbering = true
+++

## 词元类别
```c++
// 词元类别
enum class TkKind : uint16_t
{
    Unknown,          // 未知
    SingleComments,   // 单行注释
    MultipleComments, // 多行注释
    Annotate,         // 注解
    KeyWord,          // 关键字
    Identifier,       // 标志符
    StringLiteral,    // 存在转义的字符串常量
    StringLiteral2,   // 不转义的字符串常量
    CharLiteral,      // 字符常量
    SIntLiteral,      // 有符号整形字符串常量
    UIntLiteral,      // 无符号整形字符串常量
    Flt32Literal,     // 浮点字符串常量
    Flt64Literal,     // 浮点字符串常量
    Separator,        // 分隔符
    Operator,         // 操作符
    EOS,              // 字符流结束
};
```
## 分隔符
```c++
// 分隔符
enum class TkSpEnum : uint16_t
{
    Unknown,      // 未知
    OpenBracket,  // [ 左方括号
    CloseBracket, // ] 右方括号
    OpenParen,    // ( 左括号
    CloseParen,   // ) 右括号
    OpenBrace,    // { 左花括号
    CloseBrace,   // } 右花括号
    CBSemiColon,  // }; 右花括号和分号
    Colon,        // : 冒号
    SemiColon,    // ; 分号
    Comma,        // , 逗号
    Ellipsis,     // ... 省略号
};
```
## 操作符
```c++
// 操作符
enum class TkOpEnum : uint16_t
{
    Unknown, // 未知

    Dot, //. 成员访问符

    Plus2,  // ++  自增
    Minus2, // --  自减

    Plus,     // + 加法
    Minus,    // - 减法
    Multiply, // * 乘法
    Divide,   // / 除法
    Modulus,  // % 求余

    BitAnd, // & 位与
    BitOr,  // | 位或
    BitNot, // ~ 位非
    BitXOr, // ^ 位异或

    Shl,  // <<   左移
    ShrL, // >>   逻辑右移
    ShrA, // ->>  算术右移
    ShlR, // <<)  循环左移
    ShrR, // >>(  循环右移

    LogicalNot, // !  逻辑非
    LogicalAnd, // && 逻辑与
    LogicalOr,  // || 逻辑或

    Assign, // =   赋值

    PlusAssign,     // += 复合加法
    MinusAssign,    // -= 复合减法
    MultiplyAssign, // *= 复合乘法
    DivideAssign,   // /= 复合除法
    ModulusAssign,  // %= 复合求余

    BitAndAssign, // &= 复合位与
    BitOrAssign,  // |= 复合位或
    BitNotAssign, // ~= 复合位非
    BitXOrAssign, // ^= 复合位异或

    ShlAssign,  // <<=   复合左移
    ShrLAssign, // >>=   复合逻辑右移
    ShrAAssign, // ->>=  复合算术右移
    ShlRAssign, // <<)=  复合循环左移
    ShrRAssign, // (>>=  复合循环右移

    EQ, // == 等于
    NE, // != 不等于
    GT, // >  小于
    GE, // >= 小于等于
    LT, // <  大于
    LE, // <= 大于等于
};

```
## 关键字
```c++
enum class TkKeyWord : uint16_t
{
    Unknown, // 未知

    Package,
    Require,
    Using,

    // 基本类型
    Void,
    Bool,

    Int8,
    Int16,
    Int32,
    Int64,

    UInt8,
    UInt16,
    UInt32,
    UInt64,

    SInt,    // 根据目标架构，可变有符号
    UInt,    // 根据目标架构，可变无符号
    Pointer, // 地址

    Flt32, // 32位浮点
    Flt64, // 64位浮点

    String,  // 字符串
    CString, // 常量字符串
    Char,    // utf8字符

    Any,

    //  基本值
    Null, // 空地址
    False,
    True,

    In, // 范围内: x in [1,6)

    // 基本跳转
    Break,
    Continue,
    Goto,
    Return,

    // 循环
    Do,
    While,
    For,
    Foreach,
    // 条件
    If,
    Elsif,
    Else,
    Switch,
    Case,
    Default,

    // 修饰
    Private,   // 私有的
    Protected, // 受保护的
    Public,    // 公开的
    Static,    // 静态的
    Const,     // 常量（不可修改）的
    Final,     // 只读的

    // 扩展类型
    Enum,
    Union,
    Struct,
    Class,
    Interface,
    Entrust,

    This,   // 实例成员访问指针
    Super,  // 父类成员访问指针
    Friend, // 友元声明

    New,        // 分配一个对象
    Sizeof,     // 获取类型大小
    Typeof,     // 判断实例是否是该类型
    Instanceof, // 判断是否是该类型的实例
    Cast,       // 类型转换

    // 异常
    Try,
    Catch,
    Finally,
    Throw,

    // 同步异步
    Await,   // 等待异步唤醒
    Synched, // 同步代码块
};

```
## 注解关键字
```c++
enum class TkAnnotate : uint16_t
{
    Unknown, // 未知

    File, // @file
    Func, // @func
    Line, // @line

    Buildin,  // @buildin 内建函数
    Async,    // @async 异步调用函数
    Volatile, // @volatile 易变的变量

    Inline,   // @inline
    Virtual,  // @virtual
    Override, // @override
    Operator, // @operator

};
```

## 词元定义
```c++
struct TokPos
{
    uint32_t pos;  // 起始位置
    uint32_t line; // 行号

    TokPos(uint32_t pos = 0, uint32_t line = 0)
        : pos(pos), line(line) {}

    std::string toString() const
    {
        std::stringstream ss;

        ss << "[ line: ";
        ss << line;
        ss << " ,pos ";
        ss << pos;
        ss << " ]";
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

    void addchar(uint32_t ch)
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
};

```