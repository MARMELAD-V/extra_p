#include "pipeline.h"
#include <iostream>
#include <string>

int main() {
    // Первый пример: 
    std::string str = "Hello World!";
    auto pipeline = str | size 
                    | [](auto x){return x * 2;} 
                    | [](auto x){std::cout << x; return x;};
    std::cout << "Pipeline created\n";
    pipeline(); // Should output: 24
    std::cout << std::endl;

    // Второй пример: пайплайн работает без использования переменной
    std::string str2 = "Hello World!";
    str2 | size 
         | [](auto x){return x * 2;} 
         | [](auto x){std::cout << x << std::endl; return x;}; //24
    std::cout << std::endl;

    // Третий пример:
    int value = 5;
    auto result = value | [](int x){return x * 2;} 
                     | [](int x){return x + 10;};
    std::cout << "Result: " << result() << std::endl; //20
    std::cout << std::endl;

    //Четвертый пример: 
    std::string text = "test";
    auto textPipeline = text | size
                            | [](auto x){return x * 3;}
                            | [](auto x){return x + 5;};
    std::cout << "Text length * 3 + 5 = " << textPipeline() << std::endl; //17
    std::cout << std::endl;

    //Пятый пример
    std::cout << "Example 5: Multiple operations\n";
    double num = 3.5;
    auto calc = num | [](double x){return x * 2.0;}
                  | [](double x){return x + 1.0;}
                  | [](double x){return x / 2.0;};
    std::cout << "Result: " << calc() << std::endl; //4.0
    std::cout << std::endl;

    return 0;
}
