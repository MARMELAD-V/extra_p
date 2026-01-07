#include "pipeline.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

void run_test(const std::string& test_name, bool result) {
    std::cout << (result ? "[PASS]" : "[FAIL]") << " " << test_name << std::endl;
    if (!result) {
        std::cerr << "Test failed: " << test_name << std::endl;
    }
}

//Basic pipeline with integer operations
void test_basic_integer_pipeline() {
    int value = 5;
    auto pipeline = value | [](int x){return x * 2;} 
                     | [](int x){return x + 10;};
    int result = pipeline();
    run_test("Basic integer pipeline", result == 20);
}

//String size pipeline
void test_string_size_pipeline() {
    std::string str = "Hello World!";
    auto pipeline = str | size 
                    | [](auto x){return x * 2;};
    auto result = pipeline();
    run_test("String size pipeline", result == 24); // 12 * 2 = 24
}

//Multiple chained operations
void test_multiple_operations() {
    double num = 3.5;
    auto pipeline = num | [](double x){return x * 2.0;}
                  | [](double x){return x + 1.0;}
                  | [](double x){return x / 2.0;};
    double result = pipeline();
    run_test("Multiple operations", std::abs(result - 4.0) < 0.001);
}

//Void-returning function (should execute immediately)
void test_void_function() {
    std::string str = "test";
    bool executed = false;
    auto pipeline = str | size
                    | [](auto x){return x * 2;}
                    | [&executed](auto x){executed = true; std::cout << x;};
    run_test("Void function execution", executed);
}

//Pipeline copy and move
void test_pipeline_copy_move() {
    int value = 10;
    auto pipeline1 = value | [](int x){return x * 2;};
    auto pipeline2 = pipeline1; //Copy
    auto pipeline3 = std::move(pipeline1); //Move
    
    int result2 = pipeline2();
    int result3 = pipeline3();
    
    run_test("Pipeline copy", result2 == 20);
    run_test("Pipeline move", result3 == 20);
}

//Pipeline assignment
void test_pipeline_assignment() {
    int value1 = 5;
    int value2 = 10;
    auto pipeline1 = value1 | [](int x){return x * 2;};
    auto pipeline2 = value2 | [](int x){return x * 3;};
    
    pipeline2 = pipeline1; // Copy assignment
    int result = pipeline2();
    
    run_test("Pipeline assignment", result == 10);
}

//Vector operations
void test_vector_pipeline() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto pipeline = vec | size
                    | [](auto x){return x * 2;};
    auto result = pipeline();
    run_test("Vector size pipeline", result == 10); // 5 * 2 = 10
}

//Complex calculation pipeline
void test_complex_calculation() {
    int start = 2;
    auto pipeline = start 
                  | [](int x){return x * x;}      // 4
                  | [](int x){return x + 5;}      // 9
                  | [](int x){return x * 3;}      // 27
                  | [](int x){return x - 7;};     // 20
    int result = pipeline();
    run_test("Complex calculation", result == 20);
}

//String transformation pipeline
void test_string_transformation() {
    std::string text = "hello";
    auto pipeline = text | size
                    | [](auto x){return x * x;}  // 5 * 5 = 25
                    | [](auto x){return x + 10;}; // 35
    auto result = pipeline();
    run_test("String transformation", result == 35);
}

//Eager evaluation (temporary pipeline)
void test_eager_evaluation() {
    int value = 7;
    int captured = 0;
    value | [](int x){return x * 2;}
          | [&captured](int x){captured = x; return x;};
    run_test("Eager evaluation", captured == 14);
}

//Pipeline with get() method
void test_pipeline_get() {
    int value = 15;
    auto pipeline = value | [](int x){return x + 5;};
    int intermediate = pipeline.get();
    int final = pipeline();
    
    run_test("Pipeline get() method", intermediate == 20 && final == 20);
}

// Multiple void functions
void test_multiple_void_functions() {
    int value = 3;
    int count = 0;
    auto pipeline = value 
                  | [](int x){return x * 2;}
                  | [&count](int x){count++; std::cout << "Step 1: " << x << std::endl;}
                  | [&count](int x){count++; std::cout << "Step 2: " << x << std::endl;};
    run_test("Multiple void functions", count == 2);
}

int main() {
    std::cout << "Running Pipeline Tests\n";
    
    test_basic_integer_pipeline();
    test_string_size_pipeline();
    test_multiple_operations();
    test_void_function();
    test_pipeline_copy_move();
    test_pipeline_assignment();
    test_vector_pipeline();
    test_complex_calculation();
    test_string_transformation();
    test_eager_evaluation();
    test_pipeline_get();
    test_multiple_void_functions();
    
    std::cout << "\nTests Complet";
    return 0;
}
