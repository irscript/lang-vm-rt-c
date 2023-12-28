#ifndef __PROJECT_INC__
#define __PROJECT_INC__

#include "fileUnit.hpp"
#include "strPool.hpp"
#include "symTable.hpp"
#include "utils/pch.hpp"
namespace air
{
    // 项目描述
    /*
     * project "项目名称"
     * {
     *   build："构建目录"
     *   arch: "编译架构" "x64"  //"x32"
     *   library：// 库目录
     *   [
     *      "库文件目录"
     *      "库文件目录2"
     *   ]
     *   file: // 编译文件
     *   [
     *      "编译文件名称"
     *      "编译文件名称2"
     *   ]
     * }
     */

    // 项目单元
    struct Project
    {
        // 项目搜索目录
        struct Directory
        {
            Directory() : path(nullptr) {}
            const std::string *path; // 目录路径
        };

        // 项目文件
        struct File
        {
            File() {}

            FileUnit unit;            // 文件单元
            std::set<StringRef> deps; // 依赖文件
        };
        std::map<std::string, Directory> dirsmap; // 搜索的目录
        std::map<std::string, File> filemap;      // 编译的文件

        std::string buildDir; // 构建目录
        std::string projPath; // 项目目录
        std::string projName; // 项目名称
        std::string projBits; // 项目架构
        uint32_t addrbits;    // 目标地址大小

        StringPool strings;  // 字符串池
        SymbolTable symbols; // 全局符号表

        // 读取项目文件
        void load(const std::string &path);
        // 开始编译项目
        void compiling();
        void compiling(const std::string &file, File &funit); // 编译文件
        void compilingDeps(const std::string &file);          // 编译依赖文件
        // 获取文件唯一路径
        std::string getFilePath(const std::string &path);

        // 添加基本类型符号
        void initSymbol();

        // 分配编号
        uint32_t getVarSerial() { return varSerial++; }
        uint32_t getFuncSerial() { return funcSerial++; }
        uint32_t getTypeSerial() { return typeSerial++; }

    private:
        uint32_t funcSerial; // 函数编号
        uint32_t typeSerial; // 类型编号
        uint32_t varSerial;  // 变量编号
    };

    // 项目集中心
    struct ProjectCenter
    {
        std::map<std::string, Project> projs; // 项目集：名称->项目
    };
}

#endif // __PROJECT_INC__