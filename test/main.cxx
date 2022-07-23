#include <iostream>
#include <uint128_t.hpp>
#include <uint256_t.hpp>

int main() {
    uint128_t num1{1245889674452};
    uint256_t num2{245896475563247};

    std::cout << "---------------------------\xa\xa";
    std::cout << "value -> " << num1 << '\xa';
    std::cout << "sizee -> " << sizeof(num1) << '\xa';
    std::cout << "sizee -> " << sizeof(uint128_t) << '\xa';
    std::cout << "\xa---------------------------\xa";
    std::cout << "---------------------------\xa\xa";
    std::cout << "value -> " << num2 << '\xa';
    std::cout << "sizee -> " << sizeof(num2) << '\xa';
    std::cout << "sizee -> " << sizeof(uint256_t) << '\xa';
    std::cout << "\xa---------------------------\xa";
}