#ifndef __PRINT_INC__
#define __PRINT_INC__
#include "pch.hpp"
namespace air
{
    // 控制台打印
    struct Printer
    {
        // 打印颜色
        enum
        {
            Black,       // 黑色
            Blue,        // 蓝色
            Green,       // 绿色
            Wathet,      // 浅蓝色
            Red,         // 红色
            Purple,      // 紫色
            Yellow,      // 黄色
            White,       // 白色
            Grey,        // 灰色
            LightBlue,   // 淡蓝色
            LightGreen,  // 淡绿色
            Aqua,        // 淡浅绿色
            LightRed,    // 淡红色
            Lavender,    // 淡紫色
            FaintYellow, // 淡黄色
            BrightWhite, // 亮白色
        };
        static inline void lock()
        {
            while (flag.test_and_set())
                ;
        }
        static inline void unlock() { flag.clear(); }

        static void print(uint32_t clr, const char *fmt, ...);

    private:
        static std::atomic_flag flag; // 多线程共享锁
    };
    template <typename... Arg>
    inline void Print(const char *fmt, Arg... arg)
    {
        Printer::lock();
        Printer::print(Printer::BrightWhite, fmt, arg...);
        Printer::unlock();
    }
    template <typename... Arg>
    inline void Error(const char *fmt, Arg... arg)
    {
        Printer::lock();
        Printer::print(Printer::LightRed, fmt, arg...);
        Printer::unlock();
    }
    template <typename... Arg>
    inline void Waring(const char *fmt, Arg... arg)
    {
        Printer::lock();
        Printer::print(Printer::FaintYellow, fmt, arg...);
        Printer::unlock();
    }
    template <typename... Arg>
    inline void Info(const char *fmt, Arg... arg)
    {
        Printer::lock();
        Printer::print(Printer::LightGreen, fmt, arg...);
        Printer::unlock();
    }
    template <typename... Arg>
    inline void Notify(const char *fmt, Arg... arg)
    {
        Printer::lock();
        Printer::print(Printer::Green, fmt, arg...);
        Printer::unlock();
    }
}
#endif // __PRINT_INC__