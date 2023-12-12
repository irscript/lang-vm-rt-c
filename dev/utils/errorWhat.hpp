#ifndef __ERRORWHAT_INC__
#define __ERRORWHAT_INC__
#include "pch.hpp"
namespace air
{
    struct ErrorWhat
    {
        ErrorWhat(const char *msg) { what = msg; }

        std::string what;

        template <typename... Arg>
        static ErrorWhat fmt(const char *fmt, Arg... arg)
        {
            ErrorWhat what("");
            std::string msg;
            msg.resize(1024);
            sprintf(msg.data(), fmt, arg...);
            what.what = msg;
            return what;
        }
    };
}

#endif // __ERRORWHAT_INC__