简介
===

不使用递归或者编译原理，纯粹的字符串分析，实现的一个表达式计算器

现已支持:

+  表达式计算，比如 (3+8)*6/5 之类
+  函数，比如 add(3,4)-5+max(3,4)+8/3-max(max(5,7),8)+8/3-max(4,5,6)
+  某个具体功能，比如rgb转hex： rgb_hex(210,34,678)

使用帮助
===

+  在程序中输入:h获取帮助
+  不检查表达式，不检查函数参数，表达式错误将使结果难以预料，比如除以0什么的。
+  不保证无bug
+  使用c中的double类型计算，不适用于高精度场合
+  会忽略所有的空白符，2 34 5 - 7和2345-7是等价的
+  操作符仅支持 + - \* / ，其他都使用函数来实现
+  负数必须加括号，-8+3或者5+8--4是错误的
+  使用“:st on”和“:st off”来设置是否显示计算的每一步

代码结构
===
+  main.c 提取子表达式并计算
+  my_fun.c 自定义函数
+  my_str.c 封装一些字符串操作
+  other_fun.c 以冒号开头的其他功能


Brief introduction
===

Do not use recursion or compiler principle, pure string analysis, the realization of an expression calculator

now supported:

+ expression, such as (3+8) *6/5, and so on.

+ function, such as add (3,4) -5+max (3,4) +8/3-max (max (5,7), 8) +8/3-max (4,5,6)

+ a specific function, such as RGB rgb_hex hex: (210,34,78)

Use help
===

+ input :h to get help
+ do not check + expression, do not check the function parameters, the expression error will cause results such as what the 0 There's no telling, divided by.

+ Input in the program: help

+ no guarantee without bug

+ Using double in C type, not suitable for high precision

+ All the gaps are ignored, and the 7 - 2345 and 2345-7 are equivalent

+ Only support the + operator + - /, other use function to achieve

+ negative numbers have to be added, -8+3 or 5+8--4 is wrong.

+ use the "on ST" and "off ST" to print the calculation of each step

Code structure
===

+ main.c extraction sub expressions and calculations

+ my_fun.c custom functions

+ my_str.c some string operation

+ other_fun.c to other functions at the beginning of the colon  
