    
!!!!使用g++或clang++直接在终端下编译运行
！所有文件都是utf-8编码
    
./test/test2.ml:      ASCII text, with CRLF line terminators
./test/test3.ml:      ASCII text, with CRLF line terminators
./test/test.ml:       ASCII text, with CRLF line terminators
./README.txt:         UTF-8 Unicode text
./scan/keywords.inc:  ASCII text, with CRLF line terminators
./scan/operators.inc: ASCII text, with CRLF line terminators
./scan/scanner.cpp:   C source, UTF-8 Unicode text, with CRLF line terminators
./basescanner.cpp:    C source, UTF-8 Unicode text, with CRLF line terminators

--------------------------------------------------------------------
    对于basescanner.cpp

代码只有一些必需的库

编译后执行程序会提示输入文件名
(文件名字也可以直接作为命令行参数传递，实验的代码在test目录里面)
(一共只有三次输入文件名字的机会)

输出直接在控制台显示
(如果输入太多不便于观察，可以使用其他一些重定向的软件)

---------------------------------------------------------------------

    对于scanner.cpp(在scan目录里面)

希望识别尽可能更加详细

操作与对与编译basescanner.cpp得到的可执行文件一样
