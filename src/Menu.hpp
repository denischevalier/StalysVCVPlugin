#pragma once
#include <functional>
#include "plugin.hpp"

struct OptionMenuItem : MenuItem {
	std::function<bool()> checker;
	std::function<void()> setter;

	OptionMenuItem(const char* label, std::function<bool()> check, std::function<void()> set)
	: checker(check)
	, setter(set)
	{
		this->text = label;
	}

	void onAction(const event::Action& e) override {
		setter();
	}

	void step() override {
		MenuItem::step();
		rightText = checker() ? "✔" : "";
	}
};

struct SpacerOptionMenuItem : OptionMenuItem {
	SpacerOptionMenuItem()
	: OptionMenuItem("<spacer>", []() { return false; }, []() {})
	{}
};

struct BoolOptionMenuItem : OptionMenuItem {
	BoolOptionMenuItem(const char* label, std::function<bool*()> get)
	: OptionMenuItem(label, [=]() { return *(get()); }, [=]() { bool* b = get(); *b = !*b; })
	{}
};

struct OptionsMenuItem : MenuItem {
	std::vector<OptionMenuItem> menuItems;

	OptionsMenuItem(const char* label) {
		this->text = label;
		this->rightText = "▸";
	}

	void addItem(const OptionMenuItem& item);
	void addSpacer();
	Menu* createChildMenu() override;
	static void addToMenu(OptionsMenuItem* item, Menu* menu);
};
