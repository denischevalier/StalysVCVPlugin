#pragma once
#include "Skin.hpp"
#include "plugin.hpp"
#include "SkinChangedListener.hpp"
#include "StalysModule.hpp"

struct StalysModuleWidget : ModuleWidget, SkinChangedListener, DefaultSkinChangeListener {
  std::string slug;
  rack::SvgPanel *modulePanel = NULL;
  Vec size;

  StalysModuleWidget();
  virtual ~StalysModuleWidget();

  void appendContextMenu(Menu *menu) override;
  void addParam(ParamWidget* param);
  void addInput(PortWidget* input);
  void addOutput(PortWidget* output);

  virtual void contextMenu(Menu *menu) {}

  void skinChanged(const std::string& skin) override;
  void defaultSkinChanged(const std::string& skin) override;
  void setPanel(Vec size, std::string slug);
  void updatePanel();
};
