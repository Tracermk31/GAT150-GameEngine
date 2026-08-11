#pragma once

#include <string>
#include <iostream>

namespace ChiefEngine {
	inline std::string ToLower(const std::string& stringToLower) {
		std::string lowerString;

		for (auto& character : lowerString) {
			character = std::tolower(character);
		}
		std::cout << lowerString << std::endl;
		return lowerString;
	}

	inline std::string ToUpper(const std::string& stringToUpper) {
		std::string upperString;

		for (auto& character : upperString) {
			character = std::toupper(character);
		}
		std::cout << upperString << std::endl;
		return upperString;
	}

	inline bool EqualsIgnoreCase(const std::string& thisString, const std::string& otherString) {
		if (thisString.size() != otherString.size()) { 
			return false; 
		} else {
			return (ToLower(thisString) == ToLower(otherString));
		}
	}
}