#ifndef __TKENUM__H__
#define __TKENUM__H__
#include <cstdint>

// 词元类别
enum class TkKind : uint16_t
{
    Unknown,          // 未知
    SingleComments,   // 单行注释
    MultipleComments, // 多行注释
    Annotate,         // 注解
    KeyWord,          // 关键字
    Identifier,       // 标志符
    StringLiteral,    // 字符串常量
    CharLiteral,      // 字符常量
    IntegerLiteral,   // 整形字符串常量
    FloatLiteral,     // 浮点字符串常量
    Separator,        // 分隔符
    Operator,         // 操作符
    EOS,              // 字符流结束
};
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
    Colon,        // : 冒号
    SemiColon,    // ; 分号
    Comma,        // , 逗号
    Ellipsis,     // ... 省略号
};

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
    ShrR, // (>>  循环右移

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

    Shl,  // <<=   复合左移
    ShrL, // >>=   复合逻辑右移
    ShrA, // ->>=  复合算术右移
    ShlR, // <<)=  复合循环左移
    ShrR, // (>>=  复合循环右移

    EQ, // == 等于
    NE, // != 不等于
    GT, // >  小于
    GE, // >= 小于等于
    LT, // <  大于
    LE, // <= 大于等于
};

// 关键字枚举
enum class TkKeyWord : uint16_t
{
    Unknown, // 未知

    Package,
    Requires,
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
    Uintptr, // 地址

    Flt32, // 32位浮点
    Flt64, // 64位浮点

    String,  // 字符串
    CString, // 常量字符串
    Char,    // utf8字符

    Any,

    //  基本值
    Nullptr, // 空地址
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
    Readonly,  // 只读的
    Inline,    // 内联的
    Override,  // 重写的
    Virtual,   // 虚函数

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

    New,    // 分配一个对象
    Sizeof, // 获取类型大小
    IsA,    // 判断是否是该类型的实例
    Cast,   // 类型转换

    // 异常
    Try,
    Catch,
    Finally,
    Throw,

    // 同步异步
    Async,        // 异步调用函数
    Await,        // 等待异步唤醒
    Synchronized, // 同步代码块
    Volatile,
};

// 注解关键字
enum class TkAnnotate : uint16_t
{
    Unknown, // 未知

    File, // @File
    Func, // @func
    Line, // @line

    Override, //@override
    Operator, //@operator

};
#endif //!__TKENUM__H__