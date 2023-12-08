#include <iostream>

#include "utils/print.hpp"

using namespace std;

int main(int argc, char **argv)
{
    for (int i = 0; i < 100; ++i)
        air::Error("error test:%d\n", i * 100);
    printf("end of test!\n");
    return 0;
}
