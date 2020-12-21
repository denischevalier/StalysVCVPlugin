#include "Common.hpp"


struct Blank : StalysModule {
  enum ParamIds { NUM_PARAMS };
  enum InputIds { NUM_INPUTS };
  enum OutputIds { NUM_OUTPUTS };
  enum LightIds { NUM_LIGHTS };

  Blank() { config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS); }

  void process(const ProcessArgs &args) override {}
};


struct BlankWidget : StalysModuleWidget {
  static constexpr int hp = 24;

  BlankWidget(Blank *module) {
    setModule(module);
    box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);
    setPanel(box.size, "Blank");
  }
};


Model *modelBlank = createModel<Blank, BlankWidget>("Blank");
