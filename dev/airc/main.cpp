#include <iostream>

#include "base/mapTable.hpp"
#include "base/project.hpp"
#include "utils/errorWhat.hpp"
#include "utils/print.hpp"

using namespace std;

int main(int argc, char **argv)
{
    system("chcp 65001");
    system("cls");

    air::MapTable::init();

    std::string file = "E:\\airlang\\Dev\\dev\\airlang\\airlang.airproj";
    air::Project proj;
    try
    {
        // 解析项目文件
        proj.load(file);
        // 开始编译项目
        proj.compiling();
    }
    catch (air::ErrorWhat what)
    {
        air::Error("%s\n", what.what.c_str());
    }

    return 0;
}
