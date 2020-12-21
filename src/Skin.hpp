#pragma once
#include "plugin.hpp"
#include <unordered_set>
#include <mutex>

struct DefaultSkinChangeListener {
	virtual void defaultSkinChanged(const std::string& skin) = 0;
};

struct Skin {
	std::string key;
	std::string display;

	Skin(const char* key, const char* display) :  key(key), display(display) {}
};

class Skins {
	private:
		typedef std::unordered_set<DefaultSkinChangeListener*> default_skin_listeners_set;
		std::vector<Skin> availableSkins;
		bool loaded = false;
		std::mutex lock;
		std::string defaultKey;
		default_skin_listeners_set defaultSkinListeners;
		std::mutex defaultSkinListenersLock;

	public:
		Skins() {}
		Skins(const Skins&) = delete;
		void operator=(const Skins&) = delete;

		static Skins& skins();
		inline const std::vector<Skin>& available() const { return availableSkins; }
		inline const std::string defaultSkin() const { return defaultKey; }
		bool validKey(const std::string& key) const;

		void setDefaultSkin(std::string skinKey);
		void registerDefaultSkinChangeListener(DefaultSkinChangeListener* listener);
		void deregisterDefaultSkinChangeListener(DefaultSkinChangeListener* listener);

	private:
		void loadSkins();
};
