#pragma once
#include "plugin.hpp"
#include "SkinChangedListener.hpp"

struct StalysModule: Module {
	std::vector<SkinChangedListener*> skinChangedListeners;
	std::string theme;
	
	json_t* dataToJson() override;
	void dataFromJson(json_t* root) override;

	void addSkinChangedListener(SkinChangedListener* listener);
	void setSkin(const std::string skin);

	virtual json_t* toJson(json_t* root) { return root; }
};

