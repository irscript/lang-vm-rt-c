#include "Parser.hpp"
#include "utils/errorWhat.hpp"
namespace air
{
    // 解析基础表达式
    AstExpRef Parser::getBaseExp()
    {
        auto tok=lexer.getNext();
        
    }
    // 解析函数调用
    AstExpRef Parser::getFuncExp()
    {
    }
    // 解析一元表达式
    AstExpRef Parser::getUnaExp()
    {
    }
    // 解析二元表达式
    AstExpRef Parser::getBinExp()
    {
    }
    // 解析三元表达式
    AstExpRef Parser::getTerExp()
    {
    }
}