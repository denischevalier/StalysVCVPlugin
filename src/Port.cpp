#include "Port.hpp"
#include "Skin.hpp"

void port::skinChanged(std::string& skin) {
	if (skin == "" || skin == "default") {
		const Skins& skins = Skins::skins();
		skin = skins.defaultKey();
	}

	std::string svg = "res/"+skin+"/port.svg";

	setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, svg)));

	fb->dirty = true;
}
