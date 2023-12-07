+++
title = '扩展巴科斯范式：EBNF'
weight = 2
+++


## 扩展巴科斯范式：EBNF

**扩展巴科斯-瑙尔范式(EBNF, Extended Backus–Naur Form)** 是表达作为描述计算机编程语言形式语言(是用精确的数学或机器可处理的公式定义的语言) 的正规方式的上下文无关文法 的元语法(metalanguage)符号表示法。

它是 **巴科斯范式(BNF)** 元语法符号表示法的一种扩展。

简单的理解就是用来描述 **语言词法** 和 **语法规则** 的语言。

### EBNF 基本形式

LEFT=RIGHT 意思为LEFT可由RIGHT推导而来，LEFT为非终结符，RIGHT可以为非终结符也可以为终结符； 非终结符 简单的理解就是可以继续推导的符号 **终结符** 不可被推导的符号。

### EBNF 符号

|   符号   |	含义   |	     示例    |
|---------|---------|------------------------|
|    =    |   定义  | CharA="a" ; 代表CharA由字母a推导而来 |
|    ,    |  连接符	 |  a,b,c 代表abc是挨着的 | 
|   ;     | 结束符   | CharA="a"; 代表 CharA这条语句定义结束   | 
|   \|    | 或者   | digit = "0" \| "1" \| "2" \| "3" \| "4" \| "5" \| "6" \| "7" \| "8" \| "9";   | 
|   [...] | 可选，出现0次或1次  |   number = ["-" \| "+"],digit  可匹配 1 -1 +1 ...|   
|   {...} |   重复，出现>=0次   |   number = ["-" \| "+"],digit,{digit}  可匹配 1 -1 +1 11  ...|   
|   (...) |   分组  |   number = （"-" \| "+"）,digit  符号必须添加，可匹配 -1 +1 ...|   
|   "..."或者'...' |  终结符,单引号主要是一些特殊情况，比如双引号   |  "a"或者'a' 由单或双引号引起来的部分是终结符，就是代表字母a，不可继续推导|  
|  (* ... *) |  注释    |  (*我是注释*) 注释不参与定义|  
|  ?...?  |  表示其中的内容具有特殊含义，对该含义的定义不在 EBNF 标准之内，有使用者来决定   |  space = ? US-ASCII character 32 ?;|  
|   -     |  排除(将右边的内容从左边进行排除)   |  string= allVistableChar - '"' 表示在allVistableChar里排除"字符|  

### EBNF 示例

以下提供一些示例以直观的理解EBNF。
```ebnf
digit excluding zero = "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;
digit                = "0" | digit excluding zero ;
natural number = digit excluding zero, { digit } ;
integer = "0" | [ "-" ], natural number ;
```

* digit excluding zero 可以是 1到9任意一个字符，digit则扩展为0到9任意一个字符。
* natural number可以是1、2、…、10、…、12345、…，因为{}代表重复任意次，包括0次。
* integer则可以是0或者可能带个负号的自然数。

这是用EBNF描述的EBNF自身语法：
```ebnf
Production     = NonTerminal "=" Expression ".".
Expression     = Term {"|" Term}.
Term           = Factor {Factor}.
Factor         = NonTerminal
                 | Terminal
                 | "(" Expression ")"
                 | "[" Expression "]"
                 | "{" Expression "}".
Terminal       = Identifier | “"“ <any char> “"“.
NonTerminal    = Identifier.
```

## 增强巴科斯范式：ABNF

RFC2234 定义了扩展的巴科斯范式(ABNF)。近年来在Internet的定义中 ABNF 被广泛使用。ABNF 做了更多的改进。扩充巴科斯-瑙尔范式(ABNF)基于了巴科斯-瑙尔范式(BNF)，但由它自己的语法和推导规则构成。这种元语言的发起原则是描述作为通信协议(双向规范)的语言的形式系统。它建档于 RFC 4234 中通常充当 IETF 通信协议的定义语言。

### ABNF 规则

一个ABNF规范是一些推导规则的集合，书写为：规则 = 定义;注释CR LF
其中：
* “规则”是不区分大小写的非最终符号
* “定义”由定义该规则的一系列符号组成
* “注释”用于记录
* “CR LF”（回车、换行）用来结束

规则名字是不区分大小写的:<rulename>,<Rulename>,<RULENAME>和<rUlENamE>都提及同一个规则。

规则名字由一个字母以及后续的多个字母、数字和连字符（减号）组成。

用尖括号（“<”，“>”）包围规则名并不是必需的（如同它们在BNF里那样），但是它们可以用来在描述中界定规则名，以方便识别出规则名。

ABNF 使用标准 ASCII 编码。

终结符由一个或多个数值字符指定。数值字符可以指定为跟随着基数(b = 二进制, d = 十进制, x = 十六进制)的一个百分号“%”，随后是这个数值，或数值的串联(用“.” 来指示)。例如回车可以指定为十进制的 %d13 或十六进制的 %x0D。回车换行可以指定为 %d13.10。

文字正文通过使用包围在引号(")中字符串来指定。这些字符串是大小写不敏感的，使用的字符集是 US-ASCII。所以字符串“abc”将匹配“abc”, “Abc”, “aBc”, “abC”, “ABc”, “AbC”, “aBC” 和 “ABC”。对于大小写敏感匹配，必须定义明确的字符: 要匹配 “aBc” 定义将是 %d97 %d66 %d99。

### ABNF 操作符

空白被用来分隔定义的各个元素: 要使空格被识别为分割符则必须明确的包含它。

#### 串联

    规则1 规则2   

规则可以通过列出一序列的规则名字来定义。

例如要匹配字符串“aba”可以使用下列规则:

    fu = %x61; a
    bar = %x62; b
    mumble = fu bar fu

#### 选择

    规则1 / 规则2   

规则可以通过用反斜杠(“/”)分隔的多选一规则来定义。

例如要接受规则 \<fu> 或规则 \<bar> 可构造如下规则：

    fu = %x61; a
    bar = %x62; b
    fubar = fu / bar 

#### 递增选择

    规则1 =/ 规则2   

可以通过使用在规则名字和定义之间的“=/”来向一个规则增加补充选择。

例如规则：
    
    ruleset = alt1 / alt2 / alt3 / alt4 / alt5

等价于

    ruleset = alt1 / alt2
    ruleset =/ alt3
    ruleset =/ alt4 / alt5

#### 值范围

    %c##-##     

数值范围可以通过使用连字符(“-”)来指定。

例如规则：

    OCTAL = "0" / "1" / "2" / "3" / "4" / "5" / "6" / "7"

等价于

    OCTAL = %x30-37

#### 序列分组

    (规则1 规则2)  

元素可以放置在圆括号中来组合定义中的规则。

要匹配“elem fubar snafu”或“elem tarfu snafu”可以构造下列规则：

    group = elem (fubar / tarfu) snafu

要匹配“elem fubar”或“tarfu snafu”可以构造下列规则：

    group = elem fubar / tarfu snafu
    group = (elem fubar) / (tarfu snafu)

#### 可变重复

    n*n规则   

    要指示一个元素的重复可以使用形式 <a> * <b> 元素。
    可选的 <a> 给出要包括的元素的最小数目，缺省为 0。
    可选的 <b> 给出要包括的元素的最大数目，缺省为无穷。
    对零或多个元素使用 *元素，对一或多个元素使用 1*元素，对二或三个元素使用 2*3元素。

#### 特定重复　　

n规则

    要指示明确数目的元素可使用形式 <a> 元素，它等价于 <a>*<a>元素。
    使用 2DIGIT 得到两个数字，使用 3DIGIT 得到三个数字。(DIGIT 在下面的核心规则中定义)。

#### 可选序列

    [规则]  

要指示可选元素下列构造是等价的：

    [fubar snafu]
    *1(fubar snafu)
    0*1(fubar snafu)

#### 注释

    ; 注释      

分号(“;”)开始一个注释并持续到此行的结束。

### 操作符优先级

上述操作符有从最紧绑定(binding)到最松绑定的给定优先级:

* 字符串，名字形成(formation)
* 注释
* 值范围
* 重复
* 分组，可选
* 串联
* 选择

与串联一起使用选择操作符可以造成混淆，建议使用分组来做明确串联分组。

### 核心规则

核心规则定义于 ABNF 标准中。

|规则|	形式定义|	意义|
|---|---|---|
|ALPHA|	%x41-5A / %x61-7A	|大写和小写 ASCII 字母 (A-Z a-z)|
|DIGIT|	%x30-39|	数字 (0-9)|
|HEXDIG|	DIGIT / "A" / "B" / "C" / "D" / "E" / "F"|	十六进制数字 (0-9 A-F a-f)|
|DQUOTE|	%x22	|双引号|
|SP|	%x20|	空格|
|HTAB|	%x09	|水平tab|
|WSP|	SP / HTAB|	空格和水平tab|
|LWSP|	*(WSP / CRLF WSP)|	线性空白(晚于换行)|
|VCHAR|	%x21-7E	|可见(打印)字符|
|CHAR|	%x01-7F	|任何 7-位 US-ASCII 字符，不包括 NUL|
|OCTET|	%x00-FF	8 |位数据|
|CTL|	%x00-1F / %x7F|	控制字符|
|CR|	%x0D|	回车|
|LF|	%x0A|	换行|
|CRLF|	CR LF|	互联网标准换行|
|BIT|	"0" / "1"|	 |