#include <iostream>
#include <fstream>
#include <string>
#include <print>

#include "json.hpp"
#include "parser.hpp"


using json = nlohmann::json;

void Parser::Initialize() {
	std::string stockID{};
	double longOpenPrice{};
	double longClosePrice{};
	double shortOpenPrice{};
	double shortClosePrice{};

	std::print("Username: ");
	std::cin >> username_;
	std::cout << "\n";

	std::print("Stock ID: ");
	std::cin >> stockID;
	std::cout << "\n";

	std::print("Long Open Price: $");
	std::cin >> longOpenPrice;
	std::cout << "\n";

	std::print("Long Close Price: $");
	std::cin >> longClosePrice;
	std::cout << "\n";

	std::print("Short Open Price: $");
	std::cin >> shortOpenPrice;
	std::cout << "\n";

	std::print("Short Close Price: $");
	std::cin >> shortClosePrice;
	std::cout << "\n";

	strategy_.emplace(username_, stockID, longOpenPrice, longClosePrice, shortOpenPrice, shortClosePrice);
	marketDataPath_ = R"(C:\Users\)" + username_ + R"(\AppData\LocalLow\Conradical Games\Screen Stocks\mods\export\market.json)";
}

void Parser::Start() {
	std::ifstream marketFile(marketDataPath_);

	if (marketFile.is_open()) {
		json marketData = json::parse(marketFile);

		if (marketData["marketReady"] != true) {
			return;
		}

		for (const auto& stock : marketData["stocks"]) {
			std::string stockID{ stock["stockId"] };

			if (stockID == strategy_->stockID) {
				strategy_->ExecuteLong(stock["price"]);
				strategy_->ExecuteShort(stock["price"]);

				marketFile.close();
			}
		}
	}
};