#include <uint128_t.hxx>
#include <uint256_t.hxx>
#include <iostream>


auto main() -> int
{
	const uint128_t num1(0xaaaaaaaaaaaaaaaaULL, 0xaaaaaaaaaaaaaaaaULL);
	
	std::cout << "---------------------------\xa\xa";
    std::cout << "value -> " << num1 << '\xa';
    std::cout << "sizee -> " << sizeof(num1) << '\xa';
    std::cout << "sizee -> " << sizeof(uint128_t) << '\xa';
    std::cout << "\xa---------------------------\xa";
    std::cout << "---------------------------\xa\xa";

	const uint256_t num2(
		0xf0f0f0f0f0f0f0f0ULL,
		0xf0f0f0f0f0f0f0f0ULL,
		0xf0f0f0f0f0f0f0f0ULL,
		0xf0f0f0f0f0f0f0f0ULL
	);
    
    std::cout << "value -> " << num2 << '\xa';
    std::cout << "sizee -> " << sizeof(num2) << '\xa';
    std::cout << "sizee -> " << sizeof(uint256_t) << '\xa';
    std::cout << "\xa---------------------------\xa";
		
}