#include <iostream>
#include <chrono>
#include <print>

#include "parser.hpp"


int main() {
	Parser parser{};
	parser.Initialize();

	int intervalInput{};
	std::print("Interval (ms): ");
	std::cin >> intervalInput;
	std::cout << "\n";
	std::cout << "-------------------------\n\n";

	const std::chrono::milliseconds interval(intervalInput);
	auto startTime = std::chrono::steady_clock::now();

	while (true) {
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

		if (elapsedTime >= interval) {
			parser.Start();

			startTime = currentTime;
		}
	}

	return 0;
}
