#include <random>
#include <iostream>


	std::random_device dev;
	
	int main() {
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist10(1, 10);
		std::cout << dist10(rng) << std::endl;
	}
