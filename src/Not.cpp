#include "Common.hpp"


struct Not : StalysModule {
  enum ParamIds { NUM_PARAMS };
  enum InputIds {
    IN1_INPUT,
    IN2_INPUT,
    IN3_INPUT,
    IN4_INPUT,
    IN5_INPUT,
    IN6_INPUT,
    IN7_INPUT,
    IN8_INPUT,
    NUM_INPUTS
  };
  enum OutputIds {
    OUT1_OUTPUT,
    OUT2_OUTPUT,
    OUT3_OUTPUT,
    OUT4_OUTPUT,
    OUT5_OUTPUT,
    OUT6_OUTPUT,
    OUT7_OUTPUT,
    OUT8_OUTPUT,
    NUM_OUTPUTS
  };
  enum LightIds { NUM_LIGHTS };

  Not() { config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS); }

  void process(const ProcessArgs &args) override {
    outputs[OUT1_OUTPUT].setVoltage(
      inputs[IN1_INPUT].getNormalVoltage(0.f) > 1.f ? 0.f : 10.f);
    outputs[OUT2_OUTPUT].setVoltage(
      inputs[IN2_INPUT].getNormalVoltage(0.f) > 1.f ? 0.f : 10.f);
    outputs[OUT3_OUTPUT].setVoltage(
      inputs[IN3_INPUT].getNormalVoltage(0.f) > 1.f ? 0.f : 10.f);
    outputs[OUT4_OUTPUT].setVoltage(
      inputs[IN4_INPUT].getNormalVoltage(0.f) > 1.f ? 0.f : 10.f);
    outputs[OUT5_OUTPUT].setVoltage(
      inputs[IN5_INPUT].getNormalVoltage(0.f) > 1.f ? 0.f : 10.f);
    outputs[OUT6_OUTPUT].setVoltage(
      inputs[IN6_INPUT].getNormalVoltage(0.f) > 1.f ? 0.f : 10.f);
    outputs[OUT7_OUTPUT].setVoltage(
      inputs[IN7_INPUT].getNormalVoltage(0.f) > 1.f ? 0.f : 10.f);
    outputs[OUT8_OUTPUT].setVoltage(
      inputs[IN8_INPUT].getNormalVoltage(0.f) > 1.f ? 0.f : 10.f);
  }
};


struct NotWidget : StalysModuleWidget {
  static constexpr int hp = 6;

  NotWidget(Not *module) {
    setModule(module);
    box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);
    setPanel(box.size, "Not");

    addInput(createInputCentered<port>(mm2px(Vec(7.62, 10.16)), module,
                                       Not::IN1_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 25.4)), module,
                                       Not::IN2_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 40.64)), module,
                                       Not::IN3_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 55.88)), module,
                                       Not::IN4_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 71.12)), module,
                                       Not::IN5_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 86.36)), module,
                                       Not::IN6_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 101.6)), module,
                                       Not::IN7_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 116.84)), module,
                                       Not::IN8_INPUT));

    addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 10.16)), module,
                                         Not::OUT1_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 25.4)), module,
                                         Not::OUT2_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 40.64)), module,
                                         Not::OUT3_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 55.88)), module,
                                         Not::OUT4_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 71.12)), module,
                                         Not::OUT5_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 86.36)), module,
                                         Not::OUT6_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 101.6)), module,
                                         Not::OUT7_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 116.84)), module,
                                         Not::OUT8_OUTPUT));
  }
};


Model *modelNot = createModel<Not, NotWidget>("Not");
