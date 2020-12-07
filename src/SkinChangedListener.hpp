#pragma once
#include "plugin.hpp"

struct SkinChangedListener {
	virtual void skinChanged(std::string& skin) = 0;
};
