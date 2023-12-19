#ifndef __PCH_INC__
#define __PCH_INC__

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#define Plat_Windows 1 // Windows平台
/*
#elif defined(__linux__)
#define Plat_Linux 1 // Linux平台
#elif defined(ANDROID) || defined(_ANDROID_)
#define Plat_Android 1 // Android平台

#elif defined(__APPLE__) || defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_MAC)
#define PLATFORM_IOS 1 // iOS、Mac平台
*/
#else
#error "未知平台!"
#endif

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <unistd.h>

#include <any>
#include <atomic>
#include <filesystem>
#include <fstream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>
// 平台相关
#ifdef Plat_Windows
#include <Windows.h>
#include <direct.h>
#endif

using flt32_t = float;
using flt64_t = double;



#endif // __PCH_INC__