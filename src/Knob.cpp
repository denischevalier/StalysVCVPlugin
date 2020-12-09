#include "Knob.hpp"
#include "Skin.hpp"

void smallKnob::skinChanged(const std::string& skin) {
	std::string _skin = skin;
	if (_skin == "" || _skin == "default") {
		_skin = Skins::skins().defaultSkin();
	}

	std::string svg = "res/"+_skin+"/knob.svg";

	setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, svg)));

	fb->dirty = true;
};
