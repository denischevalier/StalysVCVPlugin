#pragma once
#include "plugin.hpp"
#include "SkinChangedListener.hpp"

struct port : rack::app::SvgPort, SkinChangedListener {
	port() {
		shadow->opacity = 0;
		std::string def = "bee";
		skinChanged(def);
	}

	void skinChanged(std::string& skin) override;
};
