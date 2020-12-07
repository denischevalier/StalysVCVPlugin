#pragma once

// clip creates musical cliping on an input (range -1;1).
// The higher the ratio, the higher the distortion.
float clip(const float x, const float ratio);

// clipSignal creates musical cliping on a VCV signal (range -10;10).
float clipSignal(const float signal, const float ratio = 0.14925373313f); // ratio = 10/67

// exponent transforms a linear -1.f to 1.f value (typically the value of a pot) to an exponential curve one.
// The higher the ratio, the stepper the curve.
float exponent(const float x, const float ratio=0.39f);

// expSignal transforms a VCV signal (range -10;10) to an exponential curve.
float expSignal(const float signal, const float ratio=0.39f);

struct knob : rack::app::SvgKnob {
	knob() {
		minAngle = -0.83 * M_PI;
		maxAngle = 0.83 * M_PI;
		shadow->opacity = 0;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/knob.svg")));
	}
};

struct snapKnob : knob {
	snapKnob() {
		snap = true;
	}
};

struct port : rack::app::SvgPort {
	port() {
		shadow->opacity = 0;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/port.svg")));
	}
};
