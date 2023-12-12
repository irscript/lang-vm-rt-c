#include <iostream>

#include "utils/print.hpp"
#include "lexer/CharStream.hpp"
#include "mapTable.hpp"
using namespace std;

int main(int argc, char **argv)
{
    air::MapTable::init();
    for (int i = 0; i < 100; ++i)
        air::Error("error test:%d\n", i * 100);
    printf("end of test!\n");
    return 0;
}
