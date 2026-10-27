#include <fstream>
#include <print>
#include <string>

#include "json.hpp"
#include "strategies.hpp"


using json = nlohmann::json;

void Strategy::ExecuteMarketCommand(const std::string& stockID, const std::string& commandName) {
	const std::string commandPath{ commandsPath + "\\" + stockID + "\\" + commandName + ".json" };
	std::ifstream commandFileInput(commandPath);

	json command;
	commandFileInput >> command;
	commandFileInput.close();

	command["execute"] = true;

	std::ofstream commandFileOutput(commandPath);
	commandFileOutput << command.dump(4);
}

// Strategy

void Strategy::ExecuteLong(const double& price) {
	if (inShort_ == true) {
		return;
	}

	if (!inLong_ && price <= longOpenPrice) {
		ExecuteMarketCommand(stockID, "buymax");
		std::print("\033[32mLong Open Attempt:\033[0m {} \n\n", price);
		inLong_ = true;
	}
	else if (inLong_ && price >= longClosePrice){
		ExecuteMarketCommand(stockID, "closemax");
		std::print("\033[33mLong Close Attempt:\033[0m {} \n\n", price);
		inLong_ = false;
	}
};

void Strategy::ExecuteShort(const double& price) {
	if (inLong_ == true) {
		return;
	}

	if (!inShort_ && price >= shortOpenPrice) {
		ExecuteMarketCommand(stockID, "shortmax");
		std::print("\033[31mShort Open Attempt:\033[0m {} \n\n", price);
		inShort_ = true;
	}
	else if (inShort_ && price <= shortClosePrice) {
		ExecuteMarketCommand(stockID, "closemax");
		std::print("\033[33mShort Close Attempt:\033[0m {} \n\n", price);
		inShort_ = false;
	}
};
