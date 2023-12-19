#include "project.hpp"
#include "airc/lexer/Lexer.hpp"
#include "utils/errorWhat.hpp"
#include "utils/print.hpp"
namespace air
{
    inline void parseBuild(air::Lexer &lexer, Project &proj)
    {
        Token tok = lexer.getNext();
        if (false == tok.isSeparator(TkSpEnum::Colon))
            throw ErrorWhat::fmt("缺少符号‘：’！\n%s\n", tok.toString());
        tok = lexer.getNext();
        if (false == tok.isString())
            throw ErrorWhat::fmt("缺少构建目录！\n%s\n", tok.toString());
        proj.buildDir = tok.txt;
        CheckPath(proj.buildDir);
    }
    inline void parseBits(air::Lexer &lexer, Project &proj)
    {
        Token tok = lexer.getNext();
        if (false == tok.isSeparator(TkSpEnum::Colon))
            throw ErrorWhat::fmt("缺少符号‘：’！\n%s\n", tok.toString());
        tok = lexer.getNext();
        if (false == tok.isString())
            throw ErrorWhat::fmt("缺少地址空间名称！\n%s\n", tok.toString());
        proj.projBits = tok.txt;
        if (proj.projBits == "x64")
            proj.addrbits = 64;
        else if (proj.projBits == "x32")
            proj.addrbits = 32;
        else
            throw ErrorWhat::fmt("未知地址空间名称！\n%s\n", tok.toString());
    }
    inline void parseLibrary(air::Lexer &lexer, Project &proj)
    {
        Token tok = lexer.getNext();
        if (false == tok.isSeparator(TkSpEnum::Colon))
            throw ErrorWhat::fmt("缺少符号‘：’！\n%s\n", tok.toString());
        tok = lexer.getNext();
        if (false == tok.isSeparator(TkSpEnum::OpenBracket))
            throw ErrorWhat::fmt("缺少符号‘[’！\n%s\n", tok.toString());
        while (true)
        {
            tok = lexer.getNext();
            if (true == tok.isSeparator(TkSpEnum::CloseBracket))
                break;
            if (false == tok.isString())
                throw ErrorWhat::fmt("缺少库文件目录路径字符串！\n%s\n", tok.toString());
            auto res = proj.dirsmap.insert({tok.txt, {}});
            if (res.second == false)
                Waring("路径重复：%s\n", res.first->first.c_str());
            else
                res.first->second.path = &res.first->first;
        }
    }
    inline void parseFile(air::Lexer &lexer, Project &proj)
    {
        Token tok = lexer.getNext();
        if (false == tok.isSeparator(TkSpEnum::Colon))
            throw ErrorWhat::fmt("缺少符号‘：’！\n%s\n", tok.toString());
        tok = lexer.getNext();
        if (false == tok.isSeparator(TkSpEnum::OpenBracket))
            throw ErrorWhat::fmt("缺少符号‘[’！\n%s\n", tok.toString());
        while (true)
        {
            tok = lexer.getNext();
            if (true == tok.isSeparator(TkSpEnum::CloseBracket))
                break;
            if (false == tok.isString())
                throw ErrorWhat::fmt("缺少编译文件路径字符串！\n%s\n", tok.toString());
            auto res = proj.filemap.insert({tok.txt, {}});
            if (res.second == false)
                Waring("路径重复：%s\n", res.first->first.c_str());
            else
                res.first->second.path = &res.first->first;
        }
    }

    inline void parseProject(air::Lexer &lexer, Project &proj)
    {
        Token tok = lexer.getNext();
        if (false == tok.isSeparator(TkSpEnum::Colon))
            throw ErrorWhat::fmt("缺少符号‘：’！\n%s\n", tok.toString());
        tok = lexer.getNext();
        if (false == tok.isString())
            throw ErrorWhat::fmt("缺少项目名称！\n%s\n", tok.toString());
        proj.projName = tok.txt;
        tok = lexer.getNext();
        if (false == tok.isSeparator(TkSpEnum::OpenBrace))
            throw ErrorWhat::fmt("缺少符号‘{’！\n%s\n", tok.toString());
        while (true)
        {
            tok = lexer.getNext();
            if (true == tok.isSeparator(TkSpEnum::CloseBrace))
                break;
            if (tok.isIdentity() == false)
                throw ErrorWhat::fmt("未知语法词元：%s！\n%s\n", tok.getTxt(), tok.toString());
            if (tok.txt == "build")
            {
                parseBuild(lexer, proj);
                continue;
            }
            if (tok.txt == "bits")
            {
                parseBits(lexer, proj);
                continue;
            }
            if (tok.txt == "library")
            {
                parseLibrary(lexer, proj);
                continue;
            }
            if (tok.txt == "file")
            {
                parseFile(lexer, proj);
                continue;
            }
        }
    }

    void Project::load(const std::string &path)
    {
        std::filesystem::path fpath(path);
        projPath = fpath.root_path().string();

        CheckPath(projPath);

        Info("%s：解析项目文件...\n", path.c_str());
        air::CharStream stream;
        if (stream.open(path) == false)
            throw ErrorWhat::fmt("%s: 文件读取失败！\n", path.c_str());

        air::Lexer lexer(stream);
        Token tok = lexer.getNext();
        if (tok.isIdentity() == false || tok.txt != "project")
            throw ErrorWhat::fmt("未知语法词元：%s！\n%s\n", tok.getTxt(), tok.toString());
        // 解析项目
        parseProject(lexer, *this);

        Notify("解析项目文件完成！\n");
    }

    /*  编译流程
     *   语法分析所有文件
     *   语义分析所有文件
     *   中间代码生成
     *   优化器优化
     *   目标代码生成
     **/

    void Project::compiling()
    {
        // 检查生成目录
        {
            std::string path = buildDir + projBits;
            std::filesystem::path buildPath(path);
            auto build = std::filesystem::absolute(buildPath);
            // 创建目录
            std::filesystem::create_directories(build);
            Info("build-path:%s\n", build.string().c_str());
        }
        // 初始化基本类型符号
        initSymbol();
        // 单文件编译
    }
    std::string Project::getFilePath(const std::string &path)
    {
        std::set<std::string> fileset; // 文件路径集合
        std::string file;
        for (auto dir : dirsmap)
        {
            file = dir.first + path;
            // 文件存在
            if (std::filesystem::exists(file) == true)
                fileset.insert(file);
        }
        // 未找到文件路径
        if (fileset.empty() == true)
            throw ErrorWhat::fmt("%s:文件可能不存在 ！\n", path.c_str());
        // 文件路径冲突
        else if (fileset.size() != 1)
        {
            Printer::lock();
            Printer::print(Printer::Purple, "%s:存在以下路径：\n", path.c_str());
            for (auto item : fileset)
                Printer::print(Printer::Aqua, "\t%s\n", item.c_str());
            Printer::unlock();
            throw ErrorWhat::fmt("%s:文件路径冲突 ！\n", path.c_str());
        }
        return *fileset.begin();
    }

    void Project::initSymbol()
    {
        uint32_t plat = sizeof(uintptr_t) * 8;
        // 检查目标地址空间
        if (addrbits > plat || (addrbits != 32 && addrbits != 64))
            throw ErrorWhat::fmt("无效目标地址空间: x%d ！\n最大有效地址空间：x%d\n", addrbits, plat);

        // 开始插入基本类型
        {
            auto name = strings.refString("void");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, 0, 0, false)));
        }
        {
            auto name = strings.refString("bool");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, 1, 1, false)));
        }
        // 有符号整数
        {
            auto name = strings.refString("int8");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, 1, 1, true)));
        }
        {
            auto name = strings.refString("int16");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, 2, 2, true)));
        }
        {
            auto name = strings.refString("int32");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, 4, 4, true)));
        }
        {
            auto name = strings.refString("int64");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, 8, addrbits, true)));
        }
        // 无符号整数
        {
            auto name = strings.refString("uint8");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, 1, 1, false)));
        }
        {
            auto name = strings.refString("uint16");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, 2, 2, false)));
        }
        {
            auto name = strings.refString("uint32");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, 4, 4, false)));
        }
        {
            auto name = strings.refString("uint64");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, 8, addrbits, false)));
        }
        // 可变类型
        {
            auto name = strings.refString("sint");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, addrbits, addrbits, true)));
        }
        {
            auto name = strings.refString("uint");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, addrbits, addrbits, false)));
        }
        {
            auto name = strings.refString("uintptr");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, addrbits, addrbits, false)));
        }
        {
            auto name = strings.refString("any");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, addrbits, addrbits, false)));
        }
        // 浮点类型
        {
            auto name = strings.refString("flt32");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, 4, 4, true)));
        }
        {
            auto name = strings.refString("flt64");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, 8, addrbits, false)));
        }
        // 字符串类型
        {
            auto name = strings.refString("char");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, addrbits, addrbits, false)));
        }
        // 字符串类型
        {
            auto name = strings.refString("cstring");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, addrbits, addrbits, false)));
        }
        {
            auto name = strings.refString("string");
            symbols.insert(&name.get(), makeSymbol(new BuildinTypeSymbol(name, addrbits, addrbits, false)));
        }
    }
}