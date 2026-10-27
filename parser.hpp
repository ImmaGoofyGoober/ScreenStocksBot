#ifndef SCREENSTOCKSBOT_PARSER_HPP
#define SCREENSTOCKSBOT_PARSER_HPP

#include <string>
#include <optional>

#include "strategies.hpp"


class Parser {
private:
	std::optional<Strategy> strategy_;
	std::string username_{};
	std::string marketDataPath_{};

public:
	void Initialize();
	void Start();

};
#endif