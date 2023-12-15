#ifndef __ASTNODESTM_INC__
#define __ASTNODESTM_INC__

#include "astINode.hpp"
#include "utils/pch.hpp"
namespace air
{
    struct IAstStm : public IAstNode
    {
    };
    struct StmBlock; // 块语句

    struct StmIf;    // if 语句
    struct StmElsif; // elsif 语句
    struct StmElse;  // else 语句

    struct StmSwitch;  // switch 语句
    struct StmCase;    // case 语句
    struct StmDefault; // default 语句

    struct StmFor;     // 语句
    struct StmDoWhile; // 语句
    struct StmWhile;   // 语句

    struct StmTry;     // 语句
    struct StmCatch;   // 语句
    struct StmFinally; // 语句
    struct StmThrow;   // 语句

    struct StmLable;    // 语句
    struct StmGoto;     // 语句
    struct StmBreak;    // 语句
    struct StmContinue; // 语句
    struct StmReturn;   // 语句

    struct StmVar; // 语句
    struct StmExp; // 语句
}
#endif // __ASTNODESTM_INC__