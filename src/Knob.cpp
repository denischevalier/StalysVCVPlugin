#include "Knob.hpp"
#include "Skin.hpp"

void knob::skinChanged(std::string& skin) {
	if (skin == "" || skin == "default") {
		const Skins& skins = Skins::skins();
		skin = skins.defaultKey();
	}

	std::string svg = "res/"+skin+"/knob.svg";

	setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, svg)));

	fb->dirty = true;
};
