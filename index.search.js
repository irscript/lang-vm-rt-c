var relearn_search_index = [
  {
    "content": "巴科斯范式：BNF 巴科斯范式 以美国人巴科斯(Backus)和丹麦人诺尔(Naur)的名字命名的一种形式化的语法表示方法，用来描述语法的一种形式体系，是一种典型的元语言。又称巴科斯-诺尔形式(Backus-Naur form)。它不仅能严格地表示语法规则，而且所描述的语法是与上下文无关的。\n它具有语法简单，表示明确，便于语法分析和编译的特点。\nBNF表示语法规则的方式为：\n非终结符用尖括号括起。 每条规则的左部是一个非终结符，右部是由非终结符和终结符组成的一个符号串，中间一般以“::=”分开。 具有相同左部的规则可以共用一个左部，各右部之间以直竖“|”隔开。 BNF 详细规则 在双引号中的字(“word”)代表着这些字符本身。而double_quote用来代表双引号。 在双引号外的字（有可能有下划线）代表着语法部分。 尖括号( \u003c \u003e )内包含的为必选项。 方括号( [ ] )内包含的为可选项。 大括号( { } )内包含的为可重复0至无数次的项。 竖线( | )表示在其左右两边任选一项，相当于\"OR\"的意思。 ::= 是“被定义为”的意思。 C 语言的 BNF 定义 1%token int_const char_const float_const id string enumeration_const 2%% 3 4translation_unit\t: external_decl 5\t| translation_unit external_decl 6\t; 7external_decl\t: function_definition 8\t| decl 9\t; 10function_definition\t: decl_specs declarator decl_list compound_stat 11\t|\tdeclarator decl_list compound_stat 12\t| decl_specs declarator\tcompound_stat 13\t|\tdeclarator compound_stat 14\t; 15decl\t: decl_specs init_declarator_list ';' 16\t| decl_specs\t';' 17\t; 18decl_list\t: decl 19\t| decl_list decl 20\t; 21decl_specs\t: storage_class_spec decl_specs 22\t| storage_class_spec 23\t| type_spec decl_specs 24\t| type_spec 25\t| type_qualifier decl_specs 26\t| type_qualifier 27\t; 28storage_class_spec\t: 'auto' | 'register' | 'static' | 'extern' | 'typedef' 29\t; 30type_spec\t: 'void' | 'char' | 'short' | 'int' | 'long' | 'float' 31\t| 'double' | 'signed' | 'unsigned' 32\t| struct_or_union_spec 33\t| enum_spec 34\t| typedef_name 35\t; 36type_qualifier\t: 'const' | 'volatile' 37\t; 38struct_or_union_spec\t: struct_or_union id '{' struct_decl_list '}' 39\t| struct_or_union\t'{' struct_decl_list '}' 40\t| struct_or_union id 41\t; 42struct_or_union\t: 'struct' | 'union' 43\t; 44struct_decl_list\t: struct_decl 45\t| struct_decl_list struct_decl 46\t; 47init_declarator_list\t: init_declarator 48\t| init_declarator_list ',' init_declarator 49\t; 50init_declarator\t: declarator 51\t| declarator '=' initializer 52\t; 53struct_decl\t: spec_qualifier_list struct_declarator_list ';' 54\t; 55spec_qualifier_list\t: type_spec spec_qualifier_list 56\t| type_spec 57\t| type_qualifier spec_qualifier_list 58\t| type_qualifier 59\t; 60struct_declarator_list\t: struct_declarator 61\t| struct_declarator_list ',' struct_declarator 62\t; 63struct_declarator\t: declarator 64\t| declarator ':' const_exp 65\t|\t':' const_exp 66\t; 67enum_spec\t: 'enum' id '{' enumerator_list '}' 68\t| 'enum'\t'{' enumerator_list '}' 69\t| 'enum' id 70\t; 71enumerator_list\t: enumerator 72\t| enumerator_list ',' enumerator 73\t; 74enumerator\t: id 75\t| id '=' const_exp 76\t; 77declarator\t: pointer direct_declarator 78\t|\tdirect_declarator 79\t; 80direct_declarator\t: id 81\t| '(' declarator ')' 82\t| direct_declarator '[' const_exp ']' 83\t| direct_declarator '['\t']' 84\t| direct_declarator '(' param_type_list ')' 85\t| direct_declarator '(' id_list ')' 86\t| direct_declarator '('\t')' 87\t; 88pointer\t: '*' type_qualifier_list 89\t| '*' 90\t| '*' type_qualifier_list pointer 91\t| '*'\tpointer 92\t; 93type_qualifier_list\t: type_qualifier 94\t| type_qualifier_list type_qualifier 95\t; 96param_type_list\t: param_list 97\t| param_list ',' '...' 98\t; 99param_list\t: param_decl 100\t| param_list ',' param_decl 101\t; 102param_decl\t: decl_specs declarator 103\t| decl_specs abstract_declarator 104\t| decl_specs 105\t; 106id_list\t: id 107\t| id_list ',' id 108\t; 109initializer\t: assignment_exp 110\t| '{' initializer_list '}' 111\t| '{' initializer_list ',' '}' 112\t; 113initializer_list\t: initializer 114\t| initializer_list ',' initializer 115\t; 116type_name\t: spec_qualifier_list abstract_declarator 117\t| spec_qualifier_list 118\t; 119abstract_declarator\t: pointer 120\t| pointer direct_abstract_declarator 121\t|\tdirect_abstract_declarator 122\t; 123direct_abstract_declarator: '(' abstract_declarator ')' 124\t| direct_abstract_declarator '[' const_exp ']' 125\t|\t'[' const_exp ']' 126\t| direct_abstract_declarator '['\t']' 127\t|\t'['\t']' 128\t| direct_abstract_declarator '(' param_type_list ')' 129\t|\t'(' param_type_list ')' 130\t| direct_abstract_declarator '('\t')' 131\t|\t'('\t')' 132\t; 133typedef_name\t: id 134\t; 135stat\t: labeled_stat 136\t| exp_stat 137\t| compound_stat 138\t| selection_stat 139\t| iteration_stat 140\t| jump_stat 141\t; 142labeled_stat\t: id ':' stat 143\t| 'case' const_exp ':' stat 144\t| 'default' ':' stat 145\t; 146exp_stat\t: exp ';' 147\t|\t';' 148\t; 149compound_stat\t: '{' decl_list stat_list '}' 150\t| '{'\tstat_list '}' 151\t| '{' decl_list\t'}' 152\t| '{'\t'}' 153\t; 154stat_list\t: stat 155\t| stat_list stat 156\t; 157selection_stat\t: 'if' '(' exp ')' stat 158\t| 'if' '(' exp ')' stat 'else' stat 159\t| 'switch' '(' exp ')' stat 160\t; 161iteration_stat\t: 'while' '(' exp ')' stat 162\t| 'do' stat 'while' '(' exp ')' ';' 163\t| 'for' '(' exp ';' exp ';' exp ')' stat 164\t| 'for' '(' exp ';' exp ';'\t')' stat 165\t| 'for' '(' exp ';'\t';' exp ')' stat 166\t| 'for' '(' exp ';'\t';'\t')' stat 167\t| 'for' '('\t';' exp ';' exp ')' stat 168\t| 'for' '('\t';' exp ';'\t')' stat 169\t| 'for' '('\t';'\t';' exp ')' stat 170\t| 'for' '('\t';'\t';'\t')' stat 171\t; 172jump_stat\t: 'goto' id ';' 173\t| 'continue' ';' 174\t| 'break' ';' 175\t| 'return' exp ';' 176\t| 'return'\t';' 177\t; 178exp\t: assignment_exp 179\t| exp ',' assignment_exp 180\t; 181assignment_exp\t: conditional_exp 182\t| unary_exp assignment_operator assignment_exp 183\t; 184assignment_operator\t: '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '\u003c\u003c=' 185\t| '\u003e\u003e=' | '\u0026=' | '^=' | '|=' 186\t; 187conditional_exp\t: logical_or_exp 188\t| logical_or_exp '?' exp ':' conditional_exp 189\t; 190const_exp\t: conditional_exp 191\t; 192logical_or_exp\t: logical_and_exp 193\t| logical_or_exp '||' logical_and_exp 194\t; 195logical_and_exp\t: inclusive_or_exp 196\t| logical_and_exp '\u0026\u0026' inclusive_or_exp 197\t; 198inclusive_or_exp\t: exclusive_or_exp 199\t| inclusive_or_exp '|' exclusive_or_exp 200\t; 201exclusive_or_exp\t: and_exp 202\t| exclusive_or_exp '^' and_exp 203\t; 204and_exp\t: equality_exp 205\t| and_exp '\u0026' equality_exp 206\t; 207equality_exp\t: relational_exp 208\t| equality_exp '==' relational_exp 209\t| equality_exp '!=' relational_exp 210\t; 211relational_exp\t: shift_expression 212\t| relational_exp '\u003c' shift_expression 213\t| relational_exp '\u003e' shift_expression 214\t| relational_exp '\u003c=' shift_expression 215\t| relational_exp '\u003e=' shift_expression 216\t; 217shift_expression\t: additive_exp 218\t| shift_expression '\u003c\u003c' additive_exp 219\t| shift_expression '\u003e\u003e' additive_exp 220\t; 221additive_exp\t: mult_exp 222\t| additive_exp '+' mult_exp 223\t| additive_exp '-' mult_exp 224\t; 225mult_exp\t: cast_exp 226\t| mult_exp '*' cast_exp 227\t| mult_exp '/' cast_exp 228\t| mult_exp '%' cast_exp 229\t; 230cast_exp\t: unary_exp 231\t| '(' type_name ')' cast_exp 232\t; 233unary_exp\t: postfix_exp 234\t| '++' unary_exp 235\t| '--' unary_exp 236\t| unary_operator cast_exp 237\t| 'sizeof' unary_exp 238\t| 'sizeof' '(' type_name ')' 239\t; 240unary_operator\t: '\u0026' | '*' | '+' | '-' | '~' | '!' 241\t; 242postfix_exp\t: primary_exp 243\t| postfix_exp '[' exp ']' 244\t| postfix_exp '(' argument_exp_list ')' 245\t| postfix_exp '('\t')' 246\t| postfix_exp '.' id 247\t| postfix_exp '-\u003e' id 248\t| postfix_exp '++' 249\t| postfix_exp '--' 250\t; 251primary_exp\t: id 252\t| const 253\t| string 254\t| '(' exp ')' 255\t; 256argument_exp_list\t: assignment_exp 257\t| argument_exp_list ',' assignment_exp 258\t; 259const\t: int_const 260\t| char_const 261\t| float_const 262\t| enumeration_const 263\t;",
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
    "content": "标识符 组成：由 任意个 字母、数字、下划线_ 组成。 规则：必须以字母 或 下划线开头。 提示 和C语言的标识符规则一致\n关键字 1void bool 2 3int8 int16 int32 int64 4uint8 uint16 uint32 uint64 5uint sint uintptr 6 7flt32 flt64 8 9char 10cstring string 11 12if elsif else 13switch case default 14for do while 15break continue goto return 16 17struct enum class interface entrust 18destructor constructor 19 20const static final 21public private protected注解符 组成：由 @ 符号开始，后接 任意个 字母、数字、_ 组成。 用途：用于标注一些信息 注解字 符号 含义 @file @func @line @override ",
    "description": "",
    "tags": null,
    "title": "标识符",
    "uri": "/1_lang/2_langdef/1_keyword/index.html"
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
    "content": "字符抽象是编译器在处理源代码时的一种重要机制。在编程中，我们使用的字符实际上可以被看作是特定的整数值（通常是ASCII值或者Unicode值）。编译器在读取源代码时，会将这些字符转换成对应的整数值，并进行相应的操作。\n例如，在C语言中，我们可以使用字符字面量来表示单个字符，如’a’或'5’。编译器会将这些字符字面量解析为它们对应的整数值，并在需要的时候将其转换回字符形式。\n此外，编译器还会对字符串进行特殊的处理。在C语言中，字符串实际上是字符数组，每个元素都包含了字符的整数值。当编译器遇到一个字符串字面量，如\"Hello, world!\"，它会创建一个包含所有字符的数组，并在末尾添加一个空字符（其整数值通常为0），以表示字符串的结束。\n总的来说，字符抽象使得编译器能够有效地处理文本数据，并且不需要程序员关注底层的细节。通过这种方式，程序员可以更加专注于编写逻辑清晰、易于维护的代码。\n好处 在词法分析中，对字符抽象的好处主要体现在以下几个方面：\n简化处理逻辑：通过将输入的字符序列转换为一个更高级别的表示（如单词或符号），编译器可以忽略掉字符编码的细节，简化处理过程。例如，无论源代码使用的是ASCII还是Unicode编码，编译器都可以将其统一视为一个整数值流。 提高识别效率：通过对字符进行分类和归类，可以更快地识别出有意义的单词和符号。比如，在识别关键字时，只需要检查某个字符串是否与预定义的关键字列表匹配即可，而不需要关心每个字符的具体值。 便于错误检测：词法分析阶段通常会首先执行错误检测，如检查拼写错误、未闭合的括号等。使用字符抽象可以帮助编译器更容易地定位这些问题，并提供有用的错误信息。 减少后续阶段的工作量：对字符进行抽象后生成的词法单元是语法分析阶段的主要输入。如果在词法分析阶段就能够正确地区分不同类型的词素（如标识符、数字、运算符等），那么语法分析阶段就可以直接使用这些词素，而不需要重新处理原始的字符数据。 支持跨平台编译：对于不同的操作系统和硬件平台，可能使用的字符编码不同。通过在词法分析阶段进行字符抽象，编译器可以在一定程度上独立于具体的字符编码，从而提高代码的可移植性。 通过字符抽象，词法分析器能够以一种更加高效且平台无关的方式处理源代码，使得整个编译过程更加可靠和健壮。 实现 1// 字符封装 2struct Char 3{ 4 uint32_t pos; // 在字符流的位置 5 uint32_t val; // 字符值 6 7 inline Char(uint32_t pos, uint32_t ch) 8 : pos(pos), val(ch) {} 9 10 inline bool isalpha() const { return ::isalpha(val); } // 字母？ 11 inline bool isdigit() const { return ::isdigit(val); } // 数字 12 inline bool isalnum() const { return ::isalnum(val); } // 数字和字母？ 13 14 inline bool isalpha_() const { return val == '_' || ::isalpha(val); } // 字母、下划线_？ 15 inline bool isalnum_() const { return val == '_' || ::isalnum(val); } // 字母、下划线_、数字？ 16 17 // 空白字符？ 18 inline bool isWhiteSpace() const 19 { 20 switch (val) 21 { 22 case ' ': 23 case '\\t': 24 case '\\v': 25 case '\\r': 26 case '\\n': 27 return true; 28 } 29 return false; 30 } 31 32 // 空字符？ 33 inline bool isNull() const { return val == '\\0'; } 34 // 16进制字符 35 inline bool isHex() const 36 { 37 if ('a' \u003c= val \u0026\u0026 val \u003c= 'f') 38 return true; 39 if ('A' \u003c= val \u0026\u0026 val \u003c= 'F') 40 return true; 41 return isdigit(); 42 } 43 // 8进制字符 44 inline bool isOct() const 45 { 46 return '0' \u003c= val \u0026\u0026 val \u003c= '7'; 47 } 48 // 2进制字符 49 inline bool isBin() const { return '0' == val || '1' == val; } 50 51 // 字符判断 52 inline bool isChar(uint32_t ch) const { return val == ch; } 53};",
    "description": "",
    "tags": null,
    "title": "字符抽象",
    "uri": "/2_compiler/1_lexer/1_char/index.html"
  },
  {
    "content": "词法定义 词法规则\n在引号中的字( ‘word’ )代表着这些字符本身。 尖括号( \u003c \u003e )内包含的为必选项。 方括号( [ ] )内包含的为可选项。 大括号( { } )内包含的为可重复0至无数次的项，后接 ‘*’，表示至少一次。 竖线( | )表示在其左右两边任选一项，相当于\"OR\"的意思。 = 是“被定义为”的意思。 1 digit = [0-9] ;数字字符 2 alpha = [a-z,A-Z] ;字母字符 3 alpha_ = [a-z,A-Z,_] ;含下划线'_'的字母字符 4 5 sign = [+,-] ;正负符号 6 7 intnum = [$sign] {$digit} ;整数字符串 8 fltnum = $intnum '.' {digit} ['E'|'e'] [$intnum] ;实数字符串 9 10 number = {digit}*语法定义 1 \u003cdigit\u003e = (0-9) ;数字字符",
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
    "content": "扩展巴科斯范式：EBNF 扩展巴科斯-瑙尔范式(EBNF, Extended Backus–Naur Form) 是表达作为描述计算机编程语言形式语言(是用精确的数学或机器可处理的公式定义的语言) 的正规方式的上下文无关文法 的元语法(metalanguage)符号表示法。\n它是 巴科斯范式(BNF) 元语法符号表示法的一种扩展。\n简单的理解就是用来描述 语言词法 和 语法规则 的语言。\nEBNF 基本形式 LEFT=RIGHT 意思为LEFT可由RIGHT推导而来，LEFT为非终结符，RIGHT可以为非终结符也可以为终结符； 非终结符 简单的理解就是可以继续推导的符号 终结符 不可被推导的符号。\nEBNF 符号 符号 含义 示例 = 定义 CharA=“a” ; 代表CharA由字母a推导而来 , 连接符 a,b,c 代表abc是挨着的 ; 结束符 CharA=“a”; 代表 CharA这条语句定义结束 | 或者 digit = “0” | “1” | “2” | “3” | “4” | “5” | “6” | “7” | “8” | “9”; […] 可选，出现0次或1次 number = [\"-\" | “+”],digit 可匹配 1 -1 +1 … {…} 重复，出现\u003e=0次 number = [\"-\" | “+”],digit,{digit} 可匹配 1 -1 +1 11 … (…) 分组 number = （\"-\" | “+\"）,digit 符号必须添加，可匹配 -1 +1 … “…“或者’…' 终结符,单引号主要是一些特殊情况，比如双引号 “a\"或者’a’ 由单或双引号引起来的部分是终结符，就是代表字母a，不可继续推导 (* … *) 注释 (我是注释) 注释不参与定义 ?…? 表示其中的内容具有特殊含义，对该含义的定义不在 EBNF 标准之内，有使用者来决定 space = ? US-ASCII character 32 ?; - 排除(将右边的内容从左边进行排除) string= allVistableChar - ‘”’ 表示在allVistableChar里排除\"字符 EBNF 示例 以下提供一些示例以直观的理解EBNF。\n1digit excluding zero = \"1\" | \"2\" | \"3\" | \"4\" | \"5\" | \"6\" | \"7\" | \"8\" | \"9\" ; 2digit = \"0\" | digit excluding zero ; 3natural number = digit excluding zero, { digit } ; 4integer = \"0\" | [ \"-\" ], natural number ; digit excluding zero 可以是 1到9任意一个字符，digit则扩展为0到9任意一个字符。 natural number可以是1、2、…、10、…、12345、…，因为{}代表重复任意次，包括0次。 integer则可以是0或者可能带个负号的自然数。 这是用EBNF描述的EBNF自身语法：\n1Production = NonTerminal \"=\" Expression \".\". 2Expression = Term {\"|\" Term}. 3Term = Factor {Factor}. 4Factor = NonTerminal 5 | Terminal 6 | \"(\" Expression \")\" 7 | \"[\" Expression \"]\" 8 | \"{\" Expression \"}\". 9Terminal = Identifier | “\"“ \u003cany char\u003e “\"“. 10NonTerminal = Identifier.增强巴科斯范式：ABNF RFC2234 定义了扩展的巴科斯范式(ABNF)。近年来在Internet的定义中 ABNF 被广泛使用。ABNF 做了更多的改进。扩充巴科斯-瑙尔范式(ABNF)基于了巴科斯-瑙尔范式(BNF)，但由它自己的语法和推导规则构成。这种元语言的发起原则是描述作为通信协议(双向规范)的语言的形式系统。它建档于 RFC 4234 中通常充当 IETF 通信协议的定义语言。\nABNF 规则 一个ABNF规范是一些推导规则的集合，书写为：规则 = 定义;注释CR LF 其中：\n“规则”是不区分大小写的非最终符号 “定义”由定义该规则的一系列符号组成 “注释”用于记录 “CR LF”（回车、换行）用来结束 规则名字是不区分大小写的:,,和都提及同一个规则。\n规则名字由一个字母以及后续的多个字母、数字和连字符（减号）组成。\n用尖括号（“\u003c”，“\u003e”）包围规则名并不是必需的（如同它们在BNF里那样），但是它们可以用来在描述中界定规则名，以方便识别出规则名。\nABNF 使用标准 ASCII 编码。\n终结符由一个或多个数值字符指定。数值字符可以指定为跟随着基数(b = 二进制, d = 十进制, x = 十六进制)的一个百分号“%”，随后是这个数值，或数值的串联(用“.” 来指示)。例如回车可以指定为十进制的 %d13 或十六进制的 %x0D。回车换行可以指定为 %d13.10。\n文字正文通过使用包围在引号(\")中字符串来指定。这些字符串是大小写不敏感的，使用的字符集是 US-ASCII。所以字符串“abc”将匹配“abc”, “Abc”, “aBc”, “abC”, “ABc”, “AbC”, “aBC” 和 “ABC”。对于大小写敏感匹配，必须定义明确的字符: 要匹配 “aBc” 定义将是 %d97 %d66 %d99。\nABNF 操作符 空白被用来分隔定义的各个元素: 要使空格被识别为分割符则必须明确的包含它。\n串联 规则1 规则2 规则可以通过列出一序列的规则名字来定义。\n例如要匹配字符串“aba”可以使用下列规则:\nfu = %x61; a bar = %x62; b mumble = fu bar fu 选择 规则1 / 规则2 规则可以通过用反斜杠(“/”)分隔的多选一规则来定义。\n例如要接受规则 \u003cfu\u003e 或规则 \u003cbar\u003e 可构造如下规则：\nfu = %x61; a bar = %x62; b fubar = fu / bar 递增选择 规则1 =/ 规则2 可以通过使用在规则名字和定义之间的“=/”来向一个规则增加补充选择。\n例如规则：\nruleset = alt1 / alt2 / alt3 / alt4 / alt5 等价于\nruleset = alt1 / alt2 ruleset =/ alt3 ruleset =/ alt4 / alt5 值范围 %c##-## 数值范围可以通过使用连字符(“-”)来指定。\n例如规则：\nOCTAL = \"0\" / \"1\" / \"2\" / \"3\" / \"4\" / \"5\" / \"6\" / \"7\" 等价于\nOCTAL = %x30-37 序列分组 (规则1 规则2) 元素可以放置在圆括号中来组合定义中的规则。\n要匹配“elem fubar snafu”或“elem tarfu snafu”可以构造下列规则：\ngroup = elem (fubar / tarfu) snafu 要匹配“elem fubar”或“tarfu snafu”可以构造下列规则：\ngroup = elem fubar / tarfu snafu group = (elem fubar) / (tarfu snafu) 可变重复 n*n规则 要指示一个元素的重复可以使用形式 \u003ca\u003e * \u003cb\u003e 元素。 可选的 \u003ca\u003e 给出要包括的元素的最小数目，缺省为 0。 可选的 \u003cb\u003e 给出要包括的元素的最大数目，缺省为无穷。 对零或多个元素使用 *元素，对一或多个元素使用 1*元素，对二或三个元素使用 2*3元素。 特定重复　n规则\n要指示明确数目的元素可使用形式 \u003ca\u003e 元素，它等价于 \u003ca\u003e*\u003ca\u003e元素。 使用 2DIGIT 得到两个数字，使用 3DIGIT 得到三个数字。(DIGIT 在下面的核心规则中定义)。 可选序列 [规则] 要指示可选元素下列构造是等价的：\n[fubar snafu] *1(fubar snafu) 0*1(fubar snafu) 注释 ; 注释 分号(“;”)开始一个注释并持续到此行的结束。\n操作符优先级 上述操作符有从最紧绑定(binding)到最松绑定的给定优先级:\n字符串，名字形成(formation) 注释 值范围 重复 分组，可选 串联 选择 与串联一起使用选择操作符可以造成混淆，建议使用分组来做明确串联分组。\n核心规则 核心规则定义于 ABNF 标准中。\n规则 形式定义 意义 ALPHA %x41-5A / %x61-7A 大写和小写 ASCII 字母 (A-Z a-z) DIGIT %x30-39 数字 (0-9) HEXDIG DIGIT / “A” / “B” / “C” / “D” / “E” / “F” 十六进制数字 (0-9 A-F a-f) DQUOTE %x22 双引号 SP %x20 空格 HTAB %x09 水平tab WSP SP / HTAB 空格和水平tab LWSP *(WSP / CRLF WSP) 线性空白(晚于换行) VCHAR %x21-7E 可见(打印)字符 CHAR %x01-7F 任何 7-位 US-ASCII 字符，不包括 NUL OCTET %x00-FF\t8 位数据 CTL %x00-1F / %x7F 控制字符 CR %x0D 回车 LF %x0A 换行 CRLF CR LF 互联网标准换行 BIT “0” / “1” ",
    "description": "",
    "tags": null,
    "title": "扩展巴科斯范式：EBNF",
    "uri": "/1_lang/1_meta/2_ebnf/index.html"
  },
  {
    "content": "字符流抽象是指在编程和软件开发中，将底层的字节流或字符编码处理细节隐藏起来，提供一个更高级别的接口来操作文本数据。这样做的目的是简化程序设计，提高代码可读性，并使开发者可以专注于应用程序的逻辑和语义，而不是底层的实现细节。\n在编译器中，词法分析阶段通常会对输入的源代码进行字符流抽象。这一阶段会将原始的字符序列转换为一系列有意义的单元，如标识符、关键字、数字、运算符等，这些单元被称为词法单元（或称为标记、符号）。每个词法单元都有对应的类型和值，这使得后续的语法分析和语义分析阶段能够更容易地理解和处理源代码。\n此外，字符流抽象也经常出现在IO库的设计中，例如Java中的Reader和Writer类，或者C++中的iostream库。这些库提供了一个统一的方式来读取和写入字符流，无论底层的字符编码如何变化。使用这些库的开发者通常不需要关心字符编码的具体细节，从而可以更加高效地编写跨平台和兼容多种字符集的代码。\n总的来说，字符流抽象是一种强大的工具，它可以帮助程序员更好地处理文本数据，而无需深入了解底层的字符编码细节。\n好处 在词法分析中对字符流进行抽象有以下几个主要好处：\n提高处理效率：对输入的字符流进行抽象，可以有效地将连续的字符组合成有意义的单元（如标识符、关键字、数字和运算符）。这有助于减少语法分析阶段需要处理的元素数量，从而提高编译器的整体效率。 更少的错误：通过将字符流转换为更高级别的表示，编译器能够更容易地检测出潜在的错误。例如，一个未闭合的字符串常量或注释可能会导致后续的解析错误；通过在词法分析阶段识别这些错误，可以提前报告并提供更准确的错误信息。 通用性与可移植性：字符流抽象使得编译器可以不关心具体的字符编码细节，比如ASCII、ISO-8859-1或者Unicode等。这种特性使得编译器能够在多种平台上运行，而无需针对每个平台进行特定的修改。 简化程序结构：词法分析器的设计和实现通常会利用字符流抽象的概念，比如使用有限自动机（FA）或正则表达式来匹配模式。这种方法简化了代码，使其更具可读性和维护性。 隐藏复杂性：对于程序员而言，他们通常关注于源代码的逻辑和语义，而非底层的字符编码。通过对字符流的抽象，编译器可以让程序员以一种更高层次的语言来表达意图，而不是直接操作底层的字符数据。 总的来说，字符流抽象是编译器设计中的重要概念，它能帮助编译器更好地理解源代码，并有效地生成目标代码。 实现 1// 字符串流 2struct CharStream 3{ 4 CharStream() {} 5 6 // 打开文件 7 bool open(const std::string \u0026path) 8 { 9 return readFile(path, data); 10 } 11 12 // 设置字符串数据 13 inline void setData(const std::string \u0026str) 14 { 15 data = str; 16 index = 0; 17 } 18 inline std::string \u0026getData() { return data; } 19 // 获取字符串中的一段 20 std::string getSbu(uint32_t start, uint32_t end) 21 { 22 assert(start \u003c end); 23 return data.substr(start, end - start); 24 } 25 26 // 获取下一字符 27 Char next() 28 { 29 if (index \u003c data.size()) 30 { 31 uint32_t pos = index; 32 uint32_t ch = data[pos]; 33 ++index; 34 return Char(pos, ch); 35 } 36 return Char(data.size(), 0); 37 } 38 // 退回字符 39 void back(Char ch) 40 { 41 index = ch.pos; 42 assert(index \u003c data.size()); 43 } 44 // 匹配一个字符 45 bool match(char ch, int off) 46 { 47 if (index + off \u003e data.size()) 48 return false; 49 return data[index + off] == ch; 50 } 51 52private: 53 std::string data; // 字符串数据 54 uint32_t index; // 位置索引 55};",
    "description": "",
    "tags": null,
    "title": "字符流抽象",
    "uri": "/2_compiler/1_lexer/2_stream/index.html"
  },
  {
    "content": "词法分析器（也称为扫描器、分词器或词法分析程序）是编译器或解释器的一部分，负责将输入的源代码字符串分解成一系列有意义的最小单元，这些单元被称为标记（Token）。每个标记代表了语言的一个原子单元，如关键字、标识符、常量、运算符和标点符号等。\n在编译过程中，词法分析器通常是第一个执行的阶段。它从源代码的开头开始，按顺序读取字符，并根据语言的语法规则生成标记流。这些规则通常由正则表达式或者有限状态自动机来定义，它们描述了如何识别特定类型的标记。\n词法分析器的主要任务包括：\n分隔：从连续的字符流中分离出独立的标记。 标识化：确定每个标记的类型，并可能附带相关的属性值。 错误处理：检测并报告源代码中的错误，如非法字符、未闭合的字符串或注释等。 例如，在C++编程语言中，以下源代码片段：\n1int main() { 2 int x = 10; 3 return 0; 4}词法分析器会将其分解为一系列标记：\n标记 类型 值 int 关键字 main 标识符 ( 符号 ) 符号 { 符号 int 关键字 x 标识符 = 符号 10 整数常量 10 ; 符号 } 符号 return 关键字 0 整数常量 0 ; 符号 } 符号 通过这种分割，后续的语法分析器能够更轻松地理解源代码的结构，并进行更复杂的语义检查和代码生成。\n作用 词法分析器在编译过程中的主要作用如下：\n标记化输入源代码：词法分析器将连续的字符序列分解成离散的标记（Token），这些标记代表了语言的基本元素，如关键字、标识符、常量和运算符等。 提供语法分析所需的输入：词法分析的结果通常是语法分析阶段的主要输入。语法分析器使用这些标记来构建抽象语法树（Abstract Syntax Tree, AST），进而理解程序的结构和语义。 错误检测：词法分析器可以检测源代码中的常见错误，如未闭合的字符串或注释、非法字符以及一些简单的拼写错误等。早期发现并报告错误有助于提高开发效率和程序质量。 简化后续处理：通过将复杂的字符流转换为易于处理的标记流，词法分析器降低了后续编译阶段的复杂性。这使得编译器设计者能够专注于更高层次的语法和语义问题。 增强可读性和可维护性：通过隐藏底层的字符编码细节，词法分析器提高了编译器代码的可读性和可维护性。开发者可以更轻松地理解和修改词法分析器，而不必关心低级别的实现细节。 支持跨平台编译：由于字符流抽象，词法分析器可以在一定程度上独立于具体的字符编码。这种特性使得编译器能够在多种操作系统和硬件平台上运行，而无需针对每个平台进行特定的修改。 总的来说，词法分析器是编译过程中的一个重要组成部分，它负责将复杂的字符数据转换为更容易理解和处理的形式，以便后续阶段对源代码进行深入分析和处理。\n词元（Token）定义 关键字表 注解关键字表 解析标识符 解析注解关键字 解析数字常量 解析字符串常量 解析字符常量 解析操作符 解析分隔符 ",
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
