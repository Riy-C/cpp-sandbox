#pragma once
#include <string>

enum class LoreCategory {
	Place,
	Character,
	Weapon, 
	Event,
	Beastiary
};

struct LoreEntry {
	std::string id;
	std::string title;
	LoreCategory category;
	std::string content;
	std::string subcategory;
};

//conversion functions
inline std::string loreCategoryToString(LoreCategory cat) {
	switch (cat) {
		case LoreCategory::Place: return "Place";
		case LoreCategory::Character: return "Character";
		case LoreCategory::Weapon: return "Weapon";
		case LoreCategory::Event: return "Event";
		case LoreCategory::Beastiary: return "Beastiary";
		default: return "Unknown";

	}
}

inline LoreCategory stringToLoreCategory(const std::string& str) {
	if (str == "Place") return LoreCategory::Place;
	if (str == "Character") return LoreCategory::Character;
	if (str == "Weapon") return LoreCategory::Weapon;
	if (str == "Event") return LoreCategory::Event;
	if (str == "Beastiary") return LoreCategory::Beastiary;
	return LoreCategory::Place; //default
}