var relearn_search_index = [
  {
    "content": "巴科斯范式：BNF 巴科斯范式 以美国人巴科斯(Backus)和丹麦人诺尔(Naur)的名字命名的一种形式化的语法表示方法，用来描述语法的一种形式体系，是一种典型的元语言。又称巴科斯-诺尔形式(Backus-Naur form)。它不仅能严格地表示语法规则，而且所描述的语法是与上下文无关的。\n它具有语法简单，表示明确，便于语法分析和编译的特点。\nBNF表示语法规则的方式为：\n非终结符用尖括号括起。 每条规则的左部是一个非终结符，右部是由非终结符和终结符组成的一个符号串，中间一般以“::=”分开。 具有相同左部的规则可以共用一个左部，各右部之间以直竖“|”隔开。 BNF 详细规则 在双引号中的字(“word”)代表着这些字符本身。而double_quote用来代表双引号。 在双引号外的字（有可能有下划线）代表着语法部分。 尖括号( \u003c \u003e )内包含的为必选项。 方括号( [ ] )内包含的为可选项。 大括号( { } )内包含的为可重复0至无数次的项。 竖线( | )表示在其左右两边任选一项，相当于\"OR\"的意思。 ::= 是“被定义为”的意思。 C 语言的 BNF 定义 %token int_const char_const float_const id string enumeration_const %% translation_unit\t: external_decl | translation_unit external_decl ; external_decl\t: function_definition | decl ; function_definition\t: decl_specs declarator decl_list compound_stat |\tdeclarator decl_list compound_stat | decl_specs declarator\tcompound_stat |\tdeclarator compound_stat ; decl\t: decl_specs init_declarator_list ';' | decl_specs\t';' ; decl_list\t: decl | decl_list decl ; decl_specs\t: storage_class_spec decl_specs | storage_class_spec | type_spec decl_specs | type_spec | type_qualifier decl_specs | type_qualifier ; storage_class_spec\t: 'auto' | 'register' | 'static' | 'extern' | 'typedef' ; type_spec\t: 'void' | 'char' | 'short' | 'int' | 'long' | 'float' | 'double' | 'signed' | 'unsigned' | struct_or_union_spec | enum_spec | typedef_name ; type_qualifier\t: 'const' | 'volatile' ; struct_or_union_spec\t: struct_or_union id '{' struct_decl_list '}' | struct_or_union\t'{' struct_decl_list '}' | struct_or_union id ; struct_or_union\t: 'struct' | 'union' ; struct_decl_list\t: struct_decl | struct_decl_list struct_decl ; init_declarator_list\t: init_declarator | init_declarator_list ',' init_declarator ; init_declarator\t: declarator | declarator '=' initializer ; struct_decl\t: spec_qualifier_list struct_declarator_list ';' ; spec_qualifier_list\t: type_spec spec_qualifier_list | type_spec | type_qualifier spec_qualifier_list | type_qualifier ; struct_declarator_list\t: struct_declarator | struct_declarator_list ',' struct_declarator ; struct_declarator\t: declarator | declarator ':' const_exp |\t':' const_exp ; enum_spec\t: 'enum' id '{' enumerator_list '}' | 'enum'\t'{' enumerator_list '}' | 'enum' id ; enumerator_list\t: enumerator | enumerator_list ',' enumerator ; enumerator\t: id | id '=' const_exp ; declarator\t: pointer direct_declarator |\tdirect_declarator ; direct_declarator\t: id | '(' declarator ')' | direct_declarator '[' const_exp ']' | direct_declarator '['\t']' | direct_declarator '(' param_type_list ')' | direct_declarator '(' id_list ')' | direct_declarator '('\t')' ; pointer\t: '*' type_qualifier_list | '*' | '*' type_qualifier_list pointer | '*'\tpointer ; type_qualifier_list\t: type_qualifier | type_qualifier_list type_qualifier ; param_type_list\t: param_list | param_list ',' '...' ; param_list\t: param_decl | param_list ',' param_decl ; param_decl\t: decl_specs declarator | decl_specs abstract_declarator | decl_specs ; id_list\t: id | id_list ',' id ; initializer\t: assignment_exp | '{' initializer_list '}' | '{' initializer_list ',' '}' ; initializer_list\t: initializer | initializer_list ',' initializer ; type_name\t: spec_qualifier_list abstract_declarator | spec_qualifier_list ; abstract_declarator\t: pointer | pointer direct_abstract_declarator |\tdirect_abstract_declarator ; direct_abstract_declarator: '(' abstract_declarator ')' | direct_abstract_declarator '[' const_exp ']' |\t'[' const_exp ']' | direct_abstract_declarator '['\t']' |\t'['\t']' | direct_abstract_declarator '(' param_type_list ')' |\t'(' param_type_list ')' | direct_abstract_declarator '('\t')' |\t'('\t')' ; typedef_name\t: id ; stat\t: labeled_stat | exp_stat | compound_stat | selection_stat | iteration_stat | jump_stat ; labeled_stat\t: id ':' stat | 'case' const_exp ':' stat | 'default' ':' stat ; exp_stat\t: exp ';' |\t';' ; compound_stat\t: '{' decl_list stat_list '}' | '{'\tstat_list '}' | '{' decl_list\t'}' | '{'\t'}' ; stat_list\t: stat | stat_list stat ; selection_stat\t: 'if' '(' exp ')' stat | 'if' '(' exp ')' stat 'else' stat | 'switch' '(' exp ')' stat ; iteration_stat\t: 'while' '(' exp ')' stat | 'do' stat 'while' '(' exp ')' ';' | 'for' '(' exp ';' exp ';' exp ')' stat | 'for' '(' exp ';' exp ';'\t')' stat | 'for' '(' exp ';'\t';' exp ')' stat | 'for' '(' exp ';'\t';'\t')' stat | 'for' '('\t';' exp ';' exp ')' stat | 'for' '('\t';' exp ';'\t')' stat | 'for' '('\t';'\t';' exp ')' stat | 'for' '('\t';'\t';'\t')' stat ; jump_stat\t: 'goto' id ';' | 'continue' ';' | 'break' ';' | 'return' exp ';' | 'return'\t';' ; exp\t: assignment_exp | exp ',' assignment_exp ; assignment_exp\t: conditional_exp | unary_exp assignment_operator assignment_exp ; assignment_operator\t: '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '\u003c\u003c=' | '\u003e\u003e=' | '\u0026=' | '^=' | '|=' ; conditional_exp\t: logical_or_exp | logical_or_exp '?' exp ':' conditional_exp ; const_exp\t: conditional_exp ; logical_or_exp\t: logical_and_exp | logical_or_exp '||' logical_and_exp ; logical_and_exp\t: inclusive_or_exp | logical_and_exp '\u0026\u0026' inclusive_or_exp ; inclusive_or_exp\t: exclusive_or_exp | inclusive_or_exp '|' exclusive_or_exp ; exclusive_or_exp\t: and_exp | exclusive_or_exp '^' and_exp ; and_exp\t: equality_exp | and_exp '\u0026' equality_exp ; equality_exp\t: relational_exp | equality_exp '==' relational_exp | equality_exp '!=' relational_exp ; relational_exp\t: shift_expression | relational_exp '\u003c' shift_expression | relational_exp '\u003e' shift_expression | relational_exp '\u003c=' shift_expression | relational_exp '\u003e=' shift_expression ; shift_expression\t: additive_exp | shift_expression '\u003c\u003c' additive_exp | shift_expression '\u003e\u003e' additive_exp ; additive_exp\t: mult_exp | additive_exp '+' mult_exp | additive_exp '-' mult_exp ; mult_exp\t: cast_exp | mult_exp '*' cast_exp | mult_exp '/' cast_exp | mult_exp '%' cast_exp ; cast_exp\t: unary_exp | '(' type_name ')' cast_exp ; unary_exp\t: postfix_exp | '++' unary_exp | '--' unary_exp | unary_operator cast_exp | 'sizeof' unary_exp | 'sizeof' '(' type_name ')' ; unary_operator\t: '\u0026' | '*' | '+' | '-' | '~' | '!' ; postfix_exp\t: primary_exp | postfix_exp '[' exp ']' | postfix_exp '(' argument_exp_list ')' | postfix_exp '('\t')' | postfix_exp '.' id | postfix_exp '-\u003e' id | postfix_exp '++' | postfix_exp '--' ; primary_exp\t: id | const | string | '(' exp ')' ; argument_exp_list\t: assignment_exp | argument_exp_list ',' assignment_exp ; const\t: int_const | char_const | float_const | enumeration_const ;",
    "description": "",
    "tags": null,
    "title": "巴科斯范式：BNF",
    "uri": "/1_lang/1_meta/1_bnf/index.html"
  },
  {
    "content": "目录 语言描述语法 巴科斯范式：BNF 扩展巴科斯范式：EBNF 增强巴科斯范式：ABNF airlang 语法 标识符 ",
    "description": "",
    "tags": null,
    "title": "编程语言",
    "uri": "/1_lang/index.html"
  },
  {
    "content": "标识符 组成：由 任意个 字母、数字、下划线_ 组成。 规则：必须以字母 或 下划线开头。 提示 和C语言的标识符规则一致\n关键字 void bool int8 int16 int32 int64 uint8 uint16 uint32 uint64 uint sint uintptr flt32 flt64 char cstring string if elsif else switch case default for do while break continue goto return struct enum class interface entrust destructor constructor const static final public private protected注解符 组成：由 @ 符号开始，后接 任意个 字母、数字、_ 组成。 用途：用于标注一些信息 注解字 符号 含义 @file @func @line @override ",
    "description": "",
    "tags": null,
    "title": "标识符",
    "uri": "/1_lang/2_langdef/1_bnf/index.html"
  },
  {
    "content": "引言 词法分析，也称为扫描或词法分析器，是编译过程中的第一步。它负责将源代码（即程序员编写的程序）分解成一系列有意义的符号，这些符号被称为标记（tokens），可以叫做词元。 每个标记代表源代码中的一部分，如关键字、标识符、常量、运算符和分隔符。 在词法分析过程中，输入的源代码被逐字符地读取，并根据预定的规则（通常称为词法规则或正则表达式）进行匹配。当找到一个匹配时，就生成一个相应的标记，并将其发送到下一个编译阶段（通常是语法分析）。这个过程会一直持续到整个源代码文件都被处理完为止。\n词法分析的主要目的是识别出源代码中的词汇结构，为后续的编译步骤提供基础。通过这种方式，编译器可以理解程序的基本元素，从而能够正确地解析和执行代码。\n目录 字符抽象 字符流抽象 词法分析器 案列测试 ",
    "description": "",
    "tags": null,
    "title": "词法分析",
    "uri": "/2_compiler/1_lexer/index.html"
  },
  {
    "content": "目录 巴科斯范式：BNF 扩展巴科斯范式：EBNF 增强巴科斯范式：ABNF ",
    "description": "",
    "tags": null,
    "title": "语言描述语法",
    "uri": "/1_lang/1_meta/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "字符抽象",
    "uri": "/2_compiler/1_lexer/1_char/index.html"
  },
  {
    "content": "词法定义 词法规则\n在引号中的字( ‘word’ )代表着这些字符本身。 尖括号( \u003c \u003e )内包含的为必选项。 方括号( [ ] )内包含的为可选项。 大括号( { } )内包含的为可重复0至无数次的项，后接 ‘*’，表示至少一次。 竖线( | )表示在其左右两边任选一项，相当于\"OR\"的意思。 = 是“被定义为”的意思。 digit = [0-9] ;数字字符 alpha = [a-z,A-Z] ;字母字符 alpha_ = [a-z,A-Z,_] ;含下划线'_'的字母字符 sign = [+,-] ;正负符号 intnum = [$sign] {$digit} ;整数字符串 fltnum = $intnum '.' {digit} ['E'|'e'] [$intnum] ;实数字符串 number = {digit}*语法定义 \u003cdigit\u003e = (0-9) ;数字字符",
    "description": "",
    "tags": null,
    "title": "airlang 语法",
    "uri": "/1_lang/2_langdef/index.html"
  },
  {
    "content": "目录 词法分析 引言 编译原理是将文本字符流，通过一系列的分析、转换，最后生成确定的指令文件的数据分析转换技术。 编译器是利用编译原理，将一种程序（源程序）翻译成另一种程序（目标程序）的计算机程序。业界也将编译器分为三个部分：前端、中端、后端。\n编译器所做的工作流程如下图所示。\n",
    "description": "",
    "tags": null,
    "title": "编译器",
    "uri": "/2_compiler/index.html"
  },
  {
    "content": "扩展巴科斯范式：EBNF 扩展巴科斯-瑙尔范式(EBNF, Extended Backus–Naur Form) 是表达作为描述计算机编程语言形式语言(是用精确的数学或机器可处理的公式定义的语言) 的正规方式的上下文无关文法 的元语法(metalanguage)符号表示法。\n它是 巴科斯范式(BNF) 元语法符号表示法的一种扩展。\n简单的理解就是用来描述 语言词法 和 语法规则 的语言。\nEBNF 基本形式 LEFT=RIGHT 意思为LEFT可由RIGHT推导而来，LEFT为非终结符，RIGHT可以为非终结符也可以为终结符； 非终结符 简单的理解就是可以继续推导的符号 终结符 不可被推导的符号。\nEBNF 符号 符号 含义 示例 = 定义 CharA=“a” ; 代表CharA由字母a推导而来 , 连接符 a,b,c 代表abc是挨着的 ; 结束符 CharA=“a”; 代表 CharA这条语句定义结束 | 或者 digit = “0” | “1” | “2” | “3” | “4” | “5” | “6” | “7” | “8” | “9”; […] 可选，出现0次或1次 number = [\"-\" | “+”],digit 可匹配 1 -1 +1 … {…} 重复，出现\u003e=0次 number = [\"-\" | “+”],digit,{digit} 可匹配 1 -1 +1 11 … (…) 分组 number = （\"-\" | “+\"）,digit 符号必须添加，可匹配 -1 +1 … “…“或者’…' 终结符,单引号主要是一些特殊情况，比如双引号 “a\"或者’a’ 由单或双引号引起来的部分是终结符，就是代表字母a，不可继续推导 (* … *) 注释 (我是注释) 注释不参与定义 ?…? 表示其中的内容具有特殊含义，对该含义的定义不在 EBNF 标准之内，有使用者来决定 space = ? US-ASCII character 32 ?; - 排除(将右边的内容从左边进行排除) string= allVistableChar - ‘”’ 表示在allVistableChar里排除\"字符 EBNF 示例 以下提供一些示例以直观的理解EBNF。\ndigit excluding zero = \"1\" | \"2\" | \"3\" | \"4\" | \"5\" | \"6\" | \"7\" | \"8\" | \"9\" ; digit = \"0\" | digit excluding zero ; natural number = digit excluding zero, { digit } ; integer = \"0\" | [ \"-\" ], natural number ; digit excluding zero 可以是 1到9任意一个字符，digit则扩展为0到9任意一个字符。 natural number可以是1、2、…、10、…、12345、…，因为{}代表重复任意次，包括0次。 integer则可以是0或者可能带个负号的自然数。 这是用EBNF描述的EBNF自身语法：\nProduction = NonTerminal \"=\" Expression \".\". Expression = Term {\"|\" Term}. Term = Factor {Factor}. Factor = NonTerminal | Terminal | \"(\" Expression \")\" | \"[\" Expression \"]\" | \"{\" Expression \"}\". Terminal = Identifier | “\"“ \u003cany char\u003e “\"“. NonTerminal = Identifier.增强巴科斯范式：ABNF RFC2234 定义了扩展的巴科斯范式(ABNF)。近年来在Internet的定义中 ABNF 被广泛使用。ABNF 做了更多的改进。扩充巴科斯-瑙尔范式(ABNF)基于了巴科斯-瑙尔范式(BNF)，但由它自己的语法和推导规则构成。这种元语言的发起原则是描述作为通信协议(双向规范)的语言的形式系统。它建档于 RFC 4234 中通常充当 IETF 通信协议的定义语言。\nABNF 规则 一个ABNF规范是一些推导规则的集合，书写为：规则 = 定义;注释CR LF 其中：\n“规则”是不区分大小写的非最终符号 “定义”由定义该规则的一系列符号组成 “注释”用于记录 “CR LF”（回车、换行）用来结束 规则名字是不区分大小写的:,,和都提及同一个规则。\n规则名字由一个字母以及后续的多个字母、数字和连字符（减号）组成。\n用尖括号（“\u003c”，“\u003e”）包围规则名并不是必需的（如同它们在BNF里那样），但是它们可以用来在描述中界定规则名，以方便识别出规则名。\nABNF 使用标准 ASCII 编码。\n终结符由一个或多个数值字符指定。数值字符可以指定为跟随着基数(b = 二进制, d = 十进制, x = 十六进制)的一个百分号“%”，随后是这个数值，或数值的串联(用“.” 来指示)。例如回车可以指定为十进制的 %d13 或十六进制的 %x0D。回车换行可以指定为 %d13.10。\n文字正文通过使用包围在引号(\")中字符串来指定。这些字符串是大小写不敏感的，使用的字符集是 US-ASCII。所以字符串“abc”将匹配“abc”, “Abc”, “aBc”, “abC”, “ABc”, “AbC”, “aBC” 和 “ABC”。对于大小写敏感匹配，必须定义明确的字符: 要匹配 “aBc” 定义将是 %d97 %d66 %d99。\nABNF 操作符 空白被用来分隔定义的各个元素: 要使空格被识别为分割符则必须明确的包含它。\n串联 规则1 规则2 规则可以通过列出一序列的规则名字来定义。\n例如要匹配字符串“aba”可以使用下列规则:\nfu = %x61; a bar = %x62; b mumble = fu bar fu 选择 规则1 / 规则2 规则可以通过用反斜杠(“/”)分隔的多选一规则来定义。\n例如要接受规则 \u003cfu\u003e 或规则 \u003cbar\u003e 可构造如下规则：\nfu = %x61; a bar = %x62; b fubar = fu / bar 递增选择 规则1 =/ 规则2 可以通过使用在规则名字和定义之间的“=/”来向一个规则增加补充选择。\n例如规则：\nruleset = alt1 / alt2 / alt3 / alt4 / alt5 等价于\nruleset = alt1 / alt2 ruleset =/ alt3 ruleset =/ alt4 / alt5 值范围 %c##-## 数值范围可以通过使用连字符(“-”)来指定。\n例如规则：\nOCTAL = \"0\" / \"1\" / \"2\" / \"3\" / \"4\" / \"5\" / \"6\" / \"7\" 等价于\nOCTAL = %x30-37 序列分组 (规则1 规则2) 元素可以放置在圆括号中来组合定义中的规则。\n要匹配“elem fubar snafu”或“elem tarfu snafu”可以构造下列规则：\ngroup = elem (fubar / tarfu) snafu 要匹配“elem fubar”或“tarfu snafu”可以构造下列规则：\ngroup = elem fubar / tarfu snafu group = (elem fubar) / (tarfu snafu) 可变重复 n*n规则 要指示一个元素的重复可以使用形式 \u003ca\u003e * \u003cb\u003e 元素。 可选的 \u003ca\u003e 给出要包括的元素的最小数目，缺省为 0。 可选的 \u003cb\u003e 给出要包括的元素的最大数目，缺省为无穷。 对零或多个元素使用 *元素，对一或多个元素使用 1*元素，对二或三个元素使用 2*3元素。 特定重复　n规则\n要指示明确数目的元素可使用形式 \u003ca\u003e 元素，它等价于 \u003ca\u003e*\u003ca\u003e元素。 使用 2DIGIT 得到两个数字，使用 3DIGIT 得到三个数字。(DIGIT 在下面的核心规则中定义)。 可选序列 [规则] 要指示可选元素下列构造是等价的：\n[fubar snafu] *1(fubar snafu) 0*1(fubar snafu) 注释 ; 注释 分号(“;”)开始一个注释并持续到此行的结束。\n操作符优先级 上述操作符有从最紧绑定(binding)到最松绑定的给定优先级:\n字符串，名字形成(formation) 注释 值范围 重复 分组，可选 串联 选择 与串联一起使用选择操作符可以造成混淆，建议使用分组来做明确串联分组。\n核心规则 核心规则定义于 ABNF 标准中。\n规则 形式定义 意义 ALPHA %x41-5A / %x61-7A 大写和小写 ASCII 字母 (A-Z a-z) DIGIT %x30-39 数字 (0-9) HEXDIG DIGIT / “A” / “B” / “C” / “D” / “E” / “F” 十六进制数字 (0-9 A-F a-f) DQUOTE %x22 双引号 SP %x20 空格 HTAB %x09 水平tab WSP SP / HTAB 空格和水平tab LWSP *(WSP / CRLF WSP) 线性空白(晚于换行) VCHAR %x21-7E 可见(打印)字符 CHAR %x01-7F 任何 7-位 US-ASCII 字符，不包括 NUL OCTET %x00-FF\t8 位数据 CTL %x00-1F / %x7F 控制字符 CR %x0D 回车 LF %x0A 换行 CRLF CR LF 互联网标准换行 BIT “0” / “1” ",
    "description": "",
    "tags": null,
    "title": "扩展巴科斯范式：EBNF",
    "uri": "/1_lang/1_meta/2_ebnf/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "字符流抽象",
    "uri": "/2_compiler/1_lexer/2_stream/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "词法分析器",
    "uri": "/2_compiler/1_lexer/3_lexer/index.html"
  },
  {
    "content": "目录 引言 ",
    "description": "",
    "tags": null,
    "title": "反汇编器",
    "uri": "/3_disassembler/index.html"
  },
  {
    "content": "增强巴科斯范式：ABNF RFC2234 定义了扩展的巴科斯范式(ABNF)。近年来在Internet的定义中 ABNF 被广泛使用。ABNF 做了更多的改进。扩充巴科斯-瑙尔范式(ABNF)基于了巴科斯-瑙尔范式(BNF)，但由它自己的语法和推导规则构成。这种元语言的发起原则是描述作为通信协议(双向规范)的语言的形式系统。它建档于 RFC 4234 中通常充当 IETF 通信协议的定义语言。\nABNF 规则 一个ABNF规范是一些推导规则的集合，书写为：规则 = 定义;注释CR LF 其中：\n“规则”是不区分大小写的非最终符号 “定义”由定义该规则的一系列符号组成 “注释”用于记录 “CR LF”（回车、换行）用来结束 规则名字是不区分大小写的:,,和都提及同一个规则。\n规则名字由一个字母以及后续的多个字母、数字和连字符（减号）组成。\n用尖括号（“\u003c”，“\u003e”）包围规则名并不是必需的（如同它们在BNF里那样），但是它们可以用来在描述中界定规则名，以方便识别出规则名。\nABNF 使用标准 ASCII 编码。\n终结符由一个或多个数值字符指定。数值字符可以指定为跟随着基数(b = 二进制, d = 十进制, x = 十六进制)的一个百分号“%”，随后是这个数值，或数值的串联(用“.” 来指示)。例如回车可以指定为十进制的 %d13 或十六进制的 %x0D。回车换行可以指定为 %d13.10。\n文字正文通过使用包围在引号(\")中字符串来指定。这些字符串是大小写不敏感的，使用的字符集是 US-ASCII。所以字符串“abc”将匹配“abc”, “Abc”, “aBc”, “abC”, “ABc”, “AbC”, “aBC” 和 “ABC”。对于大小写敏感匹配，必须定义明确的字符: 要匹配 “aBc” 定义将是 %d97 %d66 %d99。\nABNF 操作符 空白被用来分隔定义的各个元素: 要使空格被识别为分割符则必须明确的包含它。\n串联 规则1 规则2 规则可以通过列出一序列的规则名字来定义。\n例如要匹配字符串“aba”可以使用下列规则:\nfu = %x61; a bar = %x62; b mumble = fu bar fu 选择 规则1 / 规则2 规则可以通过用反斜杠(“/”)分隔的多选一规则来定义。\n例如要接受规则 \u003cfu\u003e 或规则 \u003cbar\u003e 可构造如下规则：\nfu = %x61; a bar = %x62; b fubar = fu / bar 递增选择 规则1 =/ 规则2 可以通过使用在规则名字和定义之间的“=/”来向一个规则增加补充选择。\n例如规则：\nruleset = alt1 / alt2 / alt3 / alt4 / alt5 等价于\nruleset = alt1 / alt2 ruleset =/ alt3 ruleset =/ alt4 / alt5 值范围 %c##-## 数值范围可以通过使用连字符(“-”)来指定。\n例如规则：\nOCTAL = \"0\" / \"1\" / \"2\" / \"3\" / \"4\" / \"5\" / \"6\" / \"7\" 等价于\nOCTAL = %x30-37 序列分组 (规则1 规则2) 元素可以放置在圆括号中来组合定义中的规则。\n要匹配“elem fubar snafu”或“elem tarfu snafu”可以构造下列规则：\ngroup = elem (fubar / tarfu) snafu 要匹配“elem fubar”或“tarfu snafu”可以构造下列规则：\ngroup = elem fubar / tarfu snafu group = (elem fubar) / (tarfu snafu) 可变重复 n*n规则 要指示一个元素的重复可以使用形式 \u003ca\u003e * \u003cb\u003e 元素。 可选的 \u003ca\u003e 给出要包括的元素的最小数目，缺省为 0。 可选的 \u003cb\u003e 给出要包括的元素的最大数目，缺省为无穷。 对零或多个元素使用 *元素，对一或多个元素使用 1*元素，对二或三个元素使用 2*3元素。 特定重复　n规则\n要指示明确数目的元素可使用形式 \u003ca\u003e 元素，它等价于 \u003ca\u003e*\u003ca\u003e元素。 使用 2DIGIT 得到两个数字，使用 3DIGIT 得到三个数字。(DIGIT 在下面的核心规则中定义)。 可选序列 [规则] 要指示可选元素下列构造是等价的：\n[fubar snafu] *1(fubar snafu) 0*1(fubar snafu) 注释 ; 注释 分号(“;”)开始一个注释并持续到此行的结束。\n操作符优先级 上述操作符有从最紧绑定(binding)到最松绑定的给定优先级:\n字符串，名字形成(formation) 注释 值范围 重复 分组，可选 串联 选择 与串联一起使用选择操作符可以造成混淆，建议使用分组来做明确串联分组。\n核心规则 核心规则定义于 ABNF 标准中。\n规则 形式定义 意义 ALPHA %x41-5A / %x61-7A 大写和小写 ASCII 字母 (A-Z a-z) DIGIT %x30-39 数字 (0-9) HEXDIG DIGIT / “A” / “B” / “C” / “D” / “E” / “F” 十六进制数字 (0-9 A-F a-f) DQUOTE %x22 双引号 SP %x20 空格 HTAB %x09 水平tab WSP SP / HTAB 空格和水平tab LWSP *(WSP / CRLF WSP) 线性空白(晚于换行) VCHAR %x21-7E 可见(打印)字符 CHAR %x01-7F 任何 7-位 US-ASCII 字符，不包括 NUL OCTET %x00-FF\t8 位数据 CTL %x00-1F / %x7F 控制字符 CR %x0D 回车 LF %x0A 换行 CRLF CR LF 互联网标准换行 BIT “0” / “1” ",
    "description": "",
    "tags": null,
    "title": "增强巴科斯范式：ABNF",
    "uri": "/1_lang/1_meta/3_abnf/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "案列测试",
    "uri": "/2_compiler/1_lexer/4_test/index.html"
  },
  {
    "content": "待续 ",
    "description": "",
    "tags": null,
    "title": "字节码文件",
    "uri": "/4_bytecode/index.html"
  },
  {
    "content": "待续 ",
    "description": "",
    "tags": null,
    "title": "虚拟机",
    "uri": "/5_vmrt/index.html"
  },
  {
    "content": "目录汇总 编程语言 语言描述语法 巴科斯范式：BNF 扩展巴科斯范式：EBNF 增强巴科斯范式：ABNF airlang 语法 标识符 编译器 词法分析 字符抽象 字符流抽象 词法分析器 案列测试 反汇编器 字节码文件 虚拟机 ",
    "description": "",
    "tags": null,
    "title": "airlang",
    "uri": "/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "类别",
    "uri": "/categories/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "标签",
    "uri": "/tags/index.html"
  }
]
