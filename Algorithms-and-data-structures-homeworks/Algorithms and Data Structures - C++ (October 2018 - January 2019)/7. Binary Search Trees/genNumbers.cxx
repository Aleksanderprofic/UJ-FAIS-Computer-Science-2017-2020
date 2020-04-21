#include <iostream>
#include <string>
#include <random>

constexpr auto maximal = 100;

auto main(int argc, const char *argv[]) -> int {

	if(argc != 2) {
		std::cerr << "Missing ouput size\n";
		return 1;
	}

	auto number	 = std::stoi(argv[1]);								// Output size

	if(number <= 0) {
		std::cerr << "Incorrect ouput size\n";
		return 1;
	}

	std::random_device rd;  										// "True" random number as seed
	std::default_random_engine generator{rd()};
	std::uniform_int_distribution<> ranVal{0, maximal};
	std::uniform_real_distribution<> ranType{};

	std::cout << number << std::endl;
	for (auto i = 0; i < number; ++i)
	{
		std::cout << ranVal(generator) << std::endl;	// 20% chance for push_front()
     }
	return 0;
}