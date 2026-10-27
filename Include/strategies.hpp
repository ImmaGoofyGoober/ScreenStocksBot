#ifndef SCREENSTOCKSBOT_STRATEGIES_HPP
#define SCREENSTOCKSBOT_STRATEGIES_HPP

#include <string>

class Strategy {
private:
	bool inLong_{};
	bool inShort_{};
	std::string username_{};

	const std::string commandsPath{ R"(C:\Users\)" + username_ + R"(\AppData\LocalLow\Conradical Games\Screen Stocks\mods\commands)" };
	void ExecuteMarketCommand(const std::string& stockID, const std::string& commandName);
public:
	Strategy(std::string username, std::string sID, double lOP, double lCP, double sOP, double sCP)
		: username_(username),
		stockID(sID),
		longOpenPrice(lOP),
		longClosePrice(lCP),
		shortOpenPrice(sOP),
		shortClosePrice(sCP)
	{

	}

	std::string stockID{};
	double longOpenPrice{}; 
	double longClosePrice{};
	double shortOpenPrice{};
	double shortClosePrice{};

	void ExecuteLong(const double& price);
	void ExecuteShort(const double& price);
};

#endif