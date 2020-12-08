#pragma once
#include "Knob.hpp"

struct snapKnob: smallKnob {
	snapKnob() {
		snap = true;
	}
};
