#include "Menu.hpp"

void OptionsMenuItem::addToMenu(OptionsMenuItem* item, Menu* menu) {
	menu->addChild(item);
}
