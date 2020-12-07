#pragma once
#include "plugin.hpp"
#include "Knob.hpp"

struct snapKnob: knob {
	snapKnob() {
		snap = true;
	}
};
