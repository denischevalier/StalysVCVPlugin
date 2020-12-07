#pragma once
#include "plugin.hpp"
#include "SkinChangedListener.hpp"

struct knob : SvgKnob, SkinChangedListener {
	knob() {
		minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		shadow->opacity = 0;
		std::string def = "bee";
		skinChanged(def);
	}

	void skinChanged(std::string& skin) override;
};
