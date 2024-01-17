+++
title = '标识符'
weight = 1
autonumbering = true
+++

## 标识符

* 组成：由 任意个 字母、数字、下划线_ 组成。
* 规则：必须以字母 或 下划线开头。

{{% notice style="tip" %}}

和C语言的标识符规则一致

{{% /notice %}}

## 关键字

```D
void bool 

int8 int16 int32 int64
uint8 uint16 uint32 uint64
uint sint uintptr

flt32 flt64

char 
cstring string

if elsif else
switch case default
for do while
break continue goto return

struct enum class interface entrust
destructor constructor

const static final
public private protected

```


## 注解符
* 组成：由 @ 符号开始，后接 任意个 字母、数字、_ 组成。
* 用途：用于标注一些信息

## 注解字

|   符号  |  		含义		|
|---------|--------------------|
| @file   | 	|
| @func	  | 	|
| @line	  | 	|
| @override	  | 	|

