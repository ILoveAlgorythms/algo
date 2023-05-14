#include <iostream>
#include <string>
void lowercase(std::string& str) {
    const int len = str.length();
    for (int i = 0; i < len; ++i) {
        __asm__ (
            "movl $0x20, %%edx\n"     // загружаем значение со смещением для строки в регистр edx
            "cmpb $0x41, %1\n"        // сравниваем текущий символ с 'A'
            "jb 1f\n"                 // если меньше 'A', переходим к следующей итерации
            "cmpb $0x5a, %1\n"        // сравниваем текущий символ с 'Z'
            "ja 1f\n"                 // если больше 'Z', переходим к следующей итерации
            "addb %%dl, %1\n"         // вычисляем код символа в нижнем регистре
            "1:\n"
            : "+r" (i)                // вводим i из C++ в качестве операнда для asm
            , "+r" (str[i])          // вводим i-ый символ строки из C++ в качестве операнда для asm
            :
            : "%edx"                  // edx изменяется в asm, поэтому должен быть перечислен в качестве разрушаемого регистра
        );
    }
}

int main() {
    std::string str;
    std::cin >> str;
    lowercase(str);
    std::cout << str << "\n"; // выведет "hello, world!"
    return 0;
}
