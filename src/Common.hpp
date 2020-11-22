#pragma once

// clip creates musical cliping on an input.
// It comes from Befaco AxB+C VCV implementation (see README.md).
float clip(const float x);

// exponentialBipolar80Pade_5_4 transforms a linear -1.f to 1.f value (typically the value of a pot) to an exponential curve one.
// It comes from Befaco AxB+C VCV implementation (see README.md).
float exponentialBipolar80Pade_5_4(const float x);
