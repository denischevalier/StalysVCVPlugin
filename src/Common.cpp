#include "Common.hpp"

float clipSignal(const float signal, const float ratio) { // ratio = 10/67
	return clip(signal/10.f, ratio)*10.f;
}

float clip(const float x, const float ratio) {
	const float clamped = rack::math::clamp(x, -1.2f, 1.2f);
	return clamped - clamped*clamped*clamped * ratio;
}

float expSignal(const float signal, const float ratio) {
	return exponent(signal/10.f, ratio)*10.f;
}

float exponent(const float x, const float ratio) {
	const float clamped = rack::math::clamp(x, -1.17f, 1.17f);
	return clamped*clamped*clamped * ratio;
}

