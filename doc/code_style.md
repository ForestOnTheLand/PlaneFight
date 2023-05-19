# 代码格式说明

希望可以遵守以下规则(排名区分先后): 

- 左大括号不换行. 
- 避免命名空间冲突, 严禁使用`using namespace std`, 用`std::xxx`代替. 
- 类的编写分文件, 声明在`.cpp`中, 实现在`.h`中.
    - 如果想定义一个变量, 使其能够在全局范围使用: 
        ```cpp
        // A.h
        #pragma once
        extern int a; // Declare
        extern const int b;
        extern const char* const str;
        ```
        ```cpp
        // A.cpp
        #include "A.h"
        int a = 1; // Initialize
        constexpr int b = 2;
        constexpr const char* str = "0";
    - 如果想定义静态成员变量: 
        ```cpp
        // A.h
        #pragma once
        class A {
            static int val; // Declare inside the class
        };
        ```
        ```cpp
        // A.cpp
        #include "A.h"
        int A::val = 1; // Must initialize outside the class!!!
- 如果是一个文件内的局部(**只在**该文件生效)的变量, 可以声明为`static`. 编译期常量推荐用`constexpr`替代`const`. 如: 
    ```cpp
    // A.cpp
    static constexpr const char* path = "...";
    static constexpr int number = 1;
    ```
    注意原来的`const char* const`相当于`constexpr const char*`.
- `new`出来的尽量`delete`. 不建议使用智能指针(智能指针和普通指针混用容易有`bug`)