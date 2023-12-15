#include <iostream>

#include "base/mapTable.hpp"
#include "lexer/Lexer.hpp"
#include "utils/errorWhat.hpp"
#include "utils/print.hpp"

#include "base/strPool.hpp"
#include "base/symTable.hpp"
using namespace std;

int main(int argc, char **argv)
{
    system("chcp 65001");
    system("cls");

    air::MapTable::init();
    air::CharStream stream;
    std::string file = "E:\\airlang\\Dev\\dev\\airlang\\lexer.test.air";
    if (stream.open(file) == false)
    {
        air::Error("%s: 读取文件失败！\n", file.c_str());
        return 0;
    }
    air::Lexer lexer(stream);
    try
    {
        while (true)
        {
            auto tok = lexer.getNext();
            if (tok.kind == air::TkKind::EOS)
                break;
            air::Print("%u:%u\t%u:%u\t %s\n",
                       tok.pos.line, tok.pos.pos,
                       (uint16_t)tok.kind, (uint16_t)tok.code.key,
                       tok.txt.c_str());
            if (tok.kind == air::TkKind::UIntLiteral)
                air::Print("\t%llu\n", tok.val.i64);
            else if (tok.kind == air::TkKind::SIntLiteral)
                air::Print("\t%lld\n", tok.val.i64);
            else if (tok.kind == air::TkKind::Flt32Literal)
                air::Print("\t%f\n", tok.val.f32);
            else if (tok.kind == air::TkKind::Flt64Literal)
                air::Print("\t%lf\n", tok.val.f64);
        }
    }
    catch (air::ErrorWhat what)
    {
        air::Error("错误：%s\n", what.what.c_str());
    }

    return 0;
}
