# Pipeline operator

Пайплайн абстракция. Использует оператор `|` для цепочки операций со значениями.
## Files
- `pipeline.h` — шаблон пайплайна.
- `main.cpp` — примеры использования.
- `tests.cpp` — тестирование.

```powershell
# Build and run demo
g++ -std=c++17 -Wall -Wextra main.cpp -o main.exe
.\main.exe

# Build and run tests
g++ -std=c++17 -Wall -Wextra tests.cpp -o tests.exe
.\tests.exe
```

## Example
```cpp
std::string str = "Hello World!";
auto pipeline = str | size
                | [](auto x){ return x * 2; }
                | [](auto x){ std::cout << x; return x; };
pipeline(); // 24
```

Можно создавать пайплайны напрямую, не храня их в памяти
```cpp
std::string str = "Hello World!";
str | size
    | [](auto x){ return x * 2; }
    | [](auto x){ std::cout << x; return x; }; // 24
```
