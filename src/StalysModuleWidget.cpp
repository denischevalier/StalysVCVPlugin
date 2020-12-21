#include "StalysModuleWidget.hpp"
#include "Menu.hpp"
#include "Skin.hpp"
#include <functional>

StalysModuleWidget::StalysModuleWidget() {
  Skins::skins().registerDefaultSkinChangeListener(this);
}

StalysModuleWidget::~StalysModuleWidget() {
  Skins::skins().deregisterDefaultSkinChangeListener(this);
}

void StalysModuleWidget::addParam(ParamWidget *param) {
  ModuleWidget::addParam(param);
  if (module) {
    auto l = dynamic_cast<SkinChangedListener *>(param);
    if (l) {
      auto m = dynamic_cast<StalysModule *>(module);
      assert(m);
      m->addSkinChangedListener(l);
    }
  }
}

void StalysModuleWidget::addInput(PortWidget *input) {
  ModuleWidget::addInput(input);
  if (module) {
    auto l = dynamic_cast<SkinChangedListener *>(input);
    if (l) {
      auto m = dynamic_cast<StalysModule *>(module);
      assert(m);
      m->addSkinChangedListener(l);
    }
  }
}

void StalysModuleWidget::addOutput(PortWidget *output) {
  ModuleWidget::addOutput(output);
  if (module) {
    auto l = dynamic_cast<SkinChangedListener *>(output);
    if (l) {
      auto m = dynamic_cast<StalysModule *>(module);
      assert(m);
      m->addSkinChangedListener(l);
    }
  }
}

void StalysModuleWidget::skinChanged(const std::string &skin) { updatePanel(); }

void StalysModuleWidget::updatePanel() {
  if (modulePanel) {
    removeChild(modulePanel);
    delete modulePanel;
    modulePanel = NULL;
  }

  std::string skin = Skins::skins().defaultSkin();

  if (module) {
    auto m = dynamic_cast<StalysModule *>(module);
    assert(m);
    skin = m->theme;
    if (skin == "" || skin == "default") {
      skin = Skins::skins().defaultSkin();
    }
  }

  std::string svg = "res/" + skin + "/" + slug + ".svg";

  modulePanel = new rack::SvgPanel();
  modulePanel->box.size = size;

  addChildBottom(modulePanel);
  modulePanel->setBackground(
      APP->window->loadSvg(asset::plugin(pluginInstance, svg)));
}

void StalysModuleWidget::setPanel(Vec panelSize, std::string moduleSlug) {
  size = panelSize;
  slug = moduleSlug;
  if (module) {
    auto m = dynamic_cast<StalysModule *>(module);
    assert(m);
    m->addSkinChangedListener(this);
  }
  updatePanel();
}

void StalysModuleWidget::appendContextMenu(Menu *menu) {
  auto m = dynamic_cast<StalysModule *>(module);
  assert(m);
  Skins *skins = &Skins::skins();

  if (skins->available().size() > 0) {
    menu->addChild(new MenuLabel());
    OptionsMenuItem *s = new OptionsMenuItem("Panel");

    s->addItem(OptionMenuItem(
        "Default", [m]() { return m->theme == "default"; },
        [m]() { m->setSkin("default"); }));
    for (auto skin : skins->available()) {
      std::string key = skin.key;
      s->addItem(OptionMenuItem(
          skin.display.c_str(), [m, key]() { return m->theme == key; },
          [m, key]() { m->setSkin(key); }));
    }

    s->addSpacer();
    for (auto skin : skins->available()) {
      std::string key = skin.key;
      s->addItem(
          OptionMenuItem((std::string("Default to ") + skin.display).c_str(),
                         [key, skins]() { return skins->defaultSkin() == key; },
                         [key, skins]() { skins->setDefaultSkin(key); }));
    }

    OptionsMenuItem::addToMenu(s, menu);
  }

  contextMenu(menu);
}

void StalysModuleWidget::defaultSkinChanged(const std::string &skin) {
  if (module) {
    auto m = dynamic_cast<StalysModule *>(module);
    assert(m);
    if (m->theme == "default") {
      m->setSkin("default");
    }
  } else {
    updatePanel();
  }
}
