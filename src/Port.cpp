#include "Port.hpp"

void port::skinChanged(const std::string& skin) {
	std::string _skin = skin;
	if (_skin == "" || _skin == "default") {
		_skin = DEFAULT_SKIN;
	}

	std::string svg = "res/"+_skin+"/port.svg";

	setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, svg)));

	fb->dirty = true;
}
