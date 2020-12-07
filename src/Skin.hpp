#pragma once
#include "Common.hpp"

struct Skin {
	std::string key;
	std::string display;

	Skin(const char* key, const char* display) :  key(key), display(display) {}
};

class Skins {
	private:
		std::vector<Skin> availableSkins;
		std::string def;
		bool loaded = false;
		std::mutex lock;

	public:
		Skins() {}
		Skins(const Skins&) = delete;
		void operator=(const Skins&) = delete;

		static const Skins& skins();
		inline const std::vector<Skin>& available() const { return availableSkins; }
		inline const std::string& defaultKey() const { return def; }
		bool validKey(const std::string& key) const;
	private:
		void loadSkins();
};
