#include "print.hpp"
#include "pch.hpp"
#include <stdio.h>
std::atomic_flag air::Printer::flag; // 多线程共享锁

#ifdef Plat_Windows
#include <windows.h>
namespace air
{
    void Printer::print(uint32_t clr, const char *fmt, ...)
    {
        HANDLE hCns = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hCns, clr);

        static char buffer[1024];

        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buffer, sizeof(buffer), fmt, ap);
        va_end(ap);
        fputs(buffer, stdout);
        // puts(buffer);

        SetConsoleTextAttribute(hCns, Printer::White);
    }
}
#endif