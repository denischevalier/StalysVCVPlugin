#pragma once
#include "plugin.hpp"

struct SkinChangedListener {
	virtual void skinChanged(const std::string& skin) = 0;
};
