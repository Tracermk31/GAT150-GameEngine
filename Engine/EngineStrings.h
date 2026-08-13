#pragma once

#include <iostream>

namespace ChiefEngine {
	inline std::string ToLower(const std::string& stringToLower) {
		std::string lowerString = stringToLower;

		for (auto& character : lowerString) {
			character = std::tolower(character);
		}
		return lowerString;
	}

	inline std::string ToUpper(const std::string& stringToUpper) {
		std::string upperString = stringToUpper;

		for (auto& character : upperString) {
			character = std::toupper(character);
		}
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