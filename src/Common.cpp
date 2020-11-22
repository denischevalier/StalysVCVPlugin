#include "plugin.hpp"
#include "Common.hpp"

float clip(const float x) {
	// We consider input is [-10.f;10.f] bounded. Reducing it to [-1.f;1.f]
	const float y = x / 10.f;
	// Pade approximant of x/(1 + x^12)^(1/12)
	const float limit = 1.16691853009184f;
	const float clamped = clamp(y, -limit, limit);

	return ((clamped + 1.45833f * std::pow(clamped, 13) + 0.559028f * std::pow(clamped, 25) + 0.0427035f * std::pow(clamped, 37))
		/ (1 + 1.54167f * std::pow(clamped, 12) + 0.642361f * std::pow(clamped, 24) + 0.0579909f * std::pow(clamped, 36))) * 10.f;
}

float exponentialBipolar80Pade_5_4(const float x) {
	return (0.109568f * x + 0.281588f * std::pow(x, 3) + 0.133841f * std::pow(x, 5))
		/ (1 - 0.630374f * std::pow(x, 2) + 0.166271f * std::pow(x, 4));
}
