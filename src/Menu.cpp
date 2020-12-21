#include "Menu.hpp"

void OptionsMenuItem::addItem(const OptionMenuItem &item) {
  menuItems.push_back(item);
}

void OptionsMenuItem::addSpacer() {
  menuItems.push_back(SpacerOptionMenuItem());
}

Menu *OptionsMenuItem::createChildMenu() {
  Menu *menu = new Menu;
  for (const OptionMenuItem &item : menuItems) {
    if (item.text == "<spacer>") {
      menu->addChild(new MenuLabel());
    } else {
      menu->addChild(new OptionMenuItem(item));
    }
  }
  return menu;
}

void OptionsMenuItem::addToMenu(OptionsMenuItem *item, Menu *menu) {
  menu->addChild(item);
}
