// cppsandbox.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include is similar to C-sharp's using directive. the difference is that #include literally copies the contents of the specified file into the current file at compile time, instead of just making the types and namespaces available.
//this is useful because it allows you to use code from other files or libraries without having to manually copy and paste the code into your file.
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Weapon.h"
#include "json.hpp"

using json_serializer = nlohmann::json;

//weapon class enum to string conversion
std::string weaponClassToString(WeaponClass wc) {
	switch (wc) {
		case WeaponClass::Physical: return "Physical";
		case WeaponClass::Neo: return "Neo";
		case WeaponClass::Occult: return "Occult";
		case WeaponClass::Spiritbound: return "Spiritbound";
		default: return "???";
	}
}

//weapon class string to enum conversion
WeaponClass stringToWeaponClass(const std::string& str) {
	if (str == "Physical") return WeaponClass::Physical;
	if (str == "Neo") return WeaponClass::Neo;
	if (str == "Occult") return WeaponClass::Occult;
	if (str == "Spiritbound") return WeaponClass::Spiritbound;
	return WeaponClass::Physical; //default
}

//rarity enum to string conversion
std::string rarityToString(Rarity r) {
	switch (r) {
		case Rarity::Junk: return "Junk";
		case Rarity::Common: return "Common";
		case Rarity::Uncommon: return "Uncommon";
		case Rarity::Rare: return "Rare";
		case Rarity::Signature: return "Signature";
		case Rarity::Forbidden: return "Forbidden";
		default: return "???";
	}
}

//rarity string to enum conversion
Rarity stringToRarity(const std::string& str) {
	if (str == "Junk") return Rarity::Junk;
	if (str == "Common") return Rarity::Common;
	if (str == "Uncommon") return Rarity::Uncommon;
	if (str == "Rare") return Rarity::Rare;
	if (str == "Signature") return Rarity::Signature;
	if (str == "Forbidden") return Rarity::Forbidden;
	return Rarity::Common; // Default
}

void saveWeapons(const std::vector<Weapon>& weapons, const std::string& filename) {
	json_serializer weaponsJson = json_serializer::array();

	for (const auto& weapon : weapons) {
		json_serializer weaponObj;
		weaponObj["name"] = weapon.name;
		weaponObj["size"] = weapon.size;
		weaponObj["class"] = weaponClassToString(weapon.weaponClass);
		weaponObj["shape"] = weapon.Shape;
		weaponObj["rarity"] = rarityToString(weapon.rarity);
		weaponObj["dmg"] = weapon.dmg;
		weaponObj["ndmg"] = weapon.ndmg;
		weaponObj["odmg"] = weapon.odmg;
		weaponObj["price"] = weapon.price;
		weaponObj["description"] = weapon.description;

		weaponsJson.push_back(weaponObj);
	}

	std::ofstream outFile(filename);
	if (outFile.is_open()) {
		outFile << weaponsJson.dump(4); // Pretty print with 4 spaces indentation
		outFile.close();
		std::cout << "Weapons saved to " << filename << std::endl;
	}
	else {
		std::cerr << "Error: Could not save weapons!\n " << filename << std::endl;
	}
}

//loads weapons from a json file
std::vector<Weapon> loadWeapons(const std::string& filename) {
	std::vector<Weapon> weapons;

	//error validation for no files
	std::ifstream inFile(filename);
	if (!inFile.is_open()) {
		std::cout << "No existing weapons found. Starting fresh.\n";
		return weapons;
	}

	json_serializer weaponsJson;
	inFile >> weaponsJson;
	inFile.close();

	//organize json data into weapon structs
	for (const auto& weaponObj : weaponsJson) {
		Weapon weapon;
		weapon.name = weaponObj["name"];
		weapon.size = weaponObj["size"];
		weapon.weaponClass = stringToWeaponClass(weaponObj["class"]);
		weapon.Shape = weaponObj["shape"];
		weapon.rarity = stringToRarity(weaponObj["rarity"]);
		weapon.dmg = weaponObj["dmg"];
		weapon.ndmg = weaponObj["ndmg"];
		weapon.odmg = weaponObj["odmg"];
		weapon.price = weaponObj["price"];
		weapon.description = weaponObj["description"];

		weapons.push_back(weapon);
	}

	std::cout << "Loaded " << weapons.size() << " weapons from " << filename << "\n";
	return weapons;
}

void addWeapon(std::vector<Weapon>& weapons) {
	Weapon newWeapon;

	std::cout << "=== ADD NEW WEAPON ==\n";

	std::cin.ignore(); //clear input buffer

	std::cout << "Name: ";
	std::getline(std::cin, newWeapon.name);

	std::cout << "Size: ";
	std::getline(std::cin, newWeapon.size);

	//Weapon Class selection
	std::cout << "\nWeapon Class:\n";
	std::cout << "[1] Physical\n";
	std::cout << "[2] Neo\n";
	std::cout << "[3] Occult\n";
	std::cout << "[4] Spiritbound\n";
	std::cout << "Choice: ";

	int classChoice = 0;
	std::cin >> classChoice;
	switch (classChoice) {
	case 1: newWeapon.weaponClass = WeaponClass::Physical; break;
	case 2: newWeapon.weaponClass = WeaponClass::Neo; break;
	case 3: newWeapon.weaponClass = WeaponClass::Occult; break;
	case 4: newWeapon.weaponClass = WeaponClass::Spiritbound; break;
	default: newWeapon.weaponClass = WeaponClass::Physical;
	}

	std::cin.ignore(); //clear input buffer
	std::cout << "Shape: ";
	std::getline(std::cin, newWeapon.Shape);

	//Rarity selection
	std::cout << "\nRarity:\n";
	std::cout << "[1] Junk\n";
	std::cout << "[2] Common\n";
	std::cout << "[3] Uncommon\n";
	std::cout << "[4] Rare\n";
	std::cout << "[5] Signature\n";
	std::cout << "[6] Forbidden\n";
	std::cout << "Choice: ";

	int rarityChoice = 0;
	std::cin >> rarityChoice;
	switch (rarityChoice) {
	case 1: newWeapon.rarity = Rarity::Junk; break;
	case 2: newWeapon.rarity = Rarity::Common; break;
	case 3: newWeapon.rarity = Rarity::Uncommon; break;
	case 4: newWeapon.rarity = Rarity::Rare; break;
	case 5: newWeapon.rarity = Rarity::Signature; break;
	case 6: newWeapon.rarity = Rarity::Forbidden; break;
	default: newWeapon.rarity = Rarity::Common;
	}

	std::cout << "Physical Damage: ";
	std::cin >> newWeapon.dmg;

	std::cout << "Neo Damage: ";
	std::cin >> newWeapon.ndmg;

	std::cout << "Occult Damage: ";
	std::cin >> newWeapon.odmg;

	std::cout << "Price: ";
	std::cin >> newWeapon.price;

	std::cin.ignore(); //clear input buffer
	std::cout << "Description: ";
	std::getline(std::cin, newWeapon.description);

	weapons.push_back(newWeapon);
	std::cout << "Weapon added successfully!\n";
}

// Displays all weapons saved in the inventory
void displayAllWeapons(const std::vector<Weapon>& weapons) {
	if (weapons.empty()) {
		std::cout << "No weapons in inventory.\n";
		return;
	}

	std::cout << "=== WEAPON INVENTORY ===\n";
	for (size_t i = 0; i < weapons.size(); i++) {
		const auto& weapon = weapons[i];
		std::cout << "\n[" << (i + 1) << "] " << weapon.name << "\n";
		std::cout << "   Size: " << weapon.size << "\n";
		std::cout << "   Class: " << weaponClassToString(weapon.weaponClass) << "\n";
		std::cout << "   Shape: " << weapon.Shape << "\n";
		std::cout << "   Rarity: " << rarityToString(weapon.rarity) << "\n";
		std::cout << "   Damage: " << weapon.dmg << "\n";
		std::cout << "   Neo Damage: " << weapon.ndmg << "\n";
		std::cout << "   Occult Damage: " << weapon.odmg << "\n";
		std::cout << "   Price: $" << weapon.price << "\n";
		std::cout << "   Description: " << weapon.description << "\n";
	}
}

//search for weapon by name
void searchWeapon(const std::vector<Weapon>& weapons) {
	if (weapons.empty()) {
		std::cout << "No weapons in inventory to search.\n";
		return;
	}

	std::cin.ignore(); //clear input buffer
	std::cout << "\nEnter weapon name to search: ";
	std::string searchTerm;
	std::getline(std::cin, searchTerm);

	bool found = false;
	for (const auto& weapon : weapons) {
		if (weapon.name.find(searchTerm) != std::string::npos) {
			std::cout << "\n" << weapon.name << "\n";
			std::cout << "Size:" << weapon.size << "\n";
			std::cout << "Class:" << weaponClassToString(weapon.weaponClass) << "\n";
			std::cout << "Shape: " << weapon.Shape << "\n";
			std::cout << "Rarity: " << rarityToString(weapon.rarity) << "\n";
			std::cout << "Damage: " << weapon.dmg << "\n";
			std::cout << "Neo Damage: " << weapon.ndmg << "\n";
			std::cout << "Occult Damage: " << weapon.odmg << "\n";
			std::cout << "Price: $" << weapon.price << "\n";
			std::cout << "Description: " << weapon.description << "\n";
			found = true;
		}
	}

	if (!found) {
		std::cout << "\nNo weapons found matching \"" << searchTerm << "'\n";
	}
}

//menu switch
void displayMenu() {
	std::cout << "--== Weapon Manager ==--\n";
	std::cout << "[1] View Weapons\n";
	std::cout << "[2] Add Weapon\n";
	std::cout << "[3] Search for Weapon\n";
	std::cout << "[4] Save and Quit\n";
	std::cout << "Choice: ";
}

int main()
{
    std::cout << "Weapon Inventory System\n";
    std::cout << "=======================\n";

	std::vector<Weapon> weapons = loadWeapons("weapons.json");

	bool running = true;
	while (running) {
		displayMenu();

		int choice;
		std::cin >> choice;

		switch (choice) {
			case 1:
				displayAllWeapons(weapons);
				break;
			case 2:
				addWeapon(weapons);
				break;
			case 3:
				searchWeapon(weapons);
				break;
			case 4:
				saveWeapons(weapons, "weapons.json");
				std::cout << "\nWeapons saved. Exiting Weapons Manager.\n";
				running = false;
				break;
			default:
				std::cout << "Invalid choice. Please try again.\n";
				break;
		}
	}
	return 0;
}

