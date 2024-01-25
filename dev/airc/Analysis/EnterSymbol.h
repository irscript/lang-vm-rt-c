#ifndef __ENTERSYMBOL_INC__
#define __ENTERSYMBOL_INC__

#include "airc/base/astNode.hpp"
#include "airc/base/fileUnit.hpp"
#include "airc/base/project.hpp"
#include "airc/lexer/Lexer.hpp"
#include "utils/pch.hpp"
namespace air
{
    // 类型符号生成
    struct EnterSymbol : public IAstVisitor{

        EnterSymbol(Project &project):project(project){}
        virtual std::any start(struct FileUnit&unit)override;
        private:
        Project &project;
        FileUnit* unit;
    };
}
#endif // __ENTERSYMBOL_INC__