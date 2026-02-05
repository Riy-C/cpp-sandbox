#include <SDL3/SDL.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

// Include your existing headers
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Weapon.h"
#include "LoreEntry.h"
#include "json.hpp"

using json_serializer = nlohmann::json;

#pragma region helper functions

std::string weaponClassToString(WeaponClass wc) {

	switch (wc) {
	case WeaponClass::Physical: return "Physical";
	case WeaponClass::Neo: return "Neo";
	case WeaponClass::Occult: return "Occult";
	case WeaponClass::Spiritbound: return "Spiritbound";
	default: return "???";
	}
}

WeaponClass StringToWeaponClass(const std::string& str) {

	if (str == "Physical") return WeaponClass::Physical;
	if (str == "Neo") return WeaponClass::Neo;
	if (str == "Occult") return WeaponClass::Occult;
	if (str == "Spiritbound") return WeaponClass::Spiritbound;
	return WeaponClass::Physical; //default
}

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
		outFile << weaponsJson.dump(4);
		outFile.close();
		std::cout << "Weapons saved to " << filename << std::endl;
	}
	else {
		std::cerr << "Error: Could not save weapons.";
	}
}

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = nullptr;

	window = SDL_CreateWindow("Bruh", 800, 800, SDL_WINDOW_RESIZABLE);

	if (window == nullptr)
	{
		printf("Window is null: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
	if (renderer == nullptr)
	{
		printf("Renderer is null: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	bool running = true;

	while (running)
	{
		// NOTE: For even better CPU efficiency, could use SDL_WaitEventTimeout(&event, 16)
		// instead of SDL_PollEvent to sleep when idle (event-driven rendering)
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL3_ProcessEvent(&event);
			if (event.type == SDL_EVENT_QUIT)
			{
				running = false;
			}

			if (event.type == SDL_EVENT_WINDOW_RESIZED)
			{
			}
		}

		// Start the ImGui frame
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		// stuff goes here
		ImGui::Text("Hello, world!");

		// Rendering
		ImGui::Render();
		SDL_SetRenderDrawColor(renderer, 23, 23, 26, 255);  // Match WindowBg color (0.09 * 255  23)
		SDL_RenderClear(renderer);
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
		SDL_RenderPresent(renderer);
	}

	// Cleanup
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}