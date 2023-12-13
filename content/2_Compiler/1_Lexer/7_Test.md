+++
title = '案列测试'
weight = 7
autonumbering = true
+++

此章节代码对应标记链接：https://github.com/irscript/lang-vm-rt-c/releases/tag/lexer_test

## 测试文本
```c++
//词法分析测试

/*普通关键字*/
package
require
using
void
bool
int8
int16
int32
int64
uint8
uint16
uint32
uint64
sint
uint
pointer
flt32
flt64
string
cstring
char
any
null
false
true
in
break
continue
goto
return
do
while
for
foreach
if
elsif
else
switch
case 
default
private
protected
public
static
const
final
enum
union
struct
entrust
class
interface
this
super
friend
new
sizeof
typeof
instanceof
cast
try
catch
finally
throw
await
synched

/*注解关键字*/
@file
@func
@line
@buildin
@async
@volatile
@inline
@virtual
@override
@operator

/*操作符*/
.
++
--
+
-
*
/
%
&
|
~
^
<<
>>
->>
<<)
>>(
!
&&
||
=
+=
-=
*=
/=
%=
&=
|=
~=
^=
<<=
>>=
->>=
<<)=
>>(=
==
!=
>
>=
<
<=
/*分隔符*/
[
]
(
)
{
}
};
;
,
...

//整数
0x455ff
0b10
07123
123456

//浮点
1.23f
1.2e-5
0.1e+5
1.e+5

//字符常量
'a'

//字符串常量
"这是一个字符串"
@"12346"
```

## 测试程序
```c++
#include <iostream>

#include "lexer/Lexer.hpp"
#include "mapTable.hpp"
#include "utils/errorWhat.hpp"
#include "utils/print.hpp"
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

```