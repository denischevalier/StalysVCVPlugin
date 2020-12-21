#pragma once
#include "plugin.hpp"
#include "SkinChangedListener.hpp"

struct smallKnob : SvgKnob, SkinChangedListener {
  smallKnob() {
    minAngle = -0.83 * M_PI;
    maxAngle = 0.83 * M_PI;
    shadow->opacity = 0;
    skinChanged("");
  }

  void skinChanged(const std::string& skin) override;
};
