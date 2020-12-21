#include "Common.hpp"

struct Clip : StalysModule {
  enum ParamIds {
    RATIO_LEVEL1_PARAM,
    RATIO_LEVEL2_PARAM,
    RATIO_LEVEL3_PARAM,
    RATIO_LEVEL4_PARAM,
    RATIO_LEVEL5_PARAM,
    RATIO_LEVEL6_PARAM,
    RATIO_LEVEL7_PARAM,
    RATIO_LEVEL8_PARAM,
    NUM_PARAMS
  };
  enum InputIds {
    IN1_INPUT,
    RATIO1_INPUT,
    IN2_INPUT,
    RATIO2_INPUT,
    IN3_INPUT,
    RATIO3_INPUT,
    IN4_INPUT,
    RATIO4_INPUT,
    IN5_INPUT,
    RATIO5_INPUT,
    IN6_INPUT,
    RATIO6_INPUT,
    IN7_INPUT,
    RATIO7_INPUT,
    IN8_INPUT,
    RATIO8_INPUT,
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

  Clip() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
    configParam(RATIO_LEVEL1_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
    configParam(RATIO_LEVEL2_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
    configParam(RATIO_LEVEL3_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
    configParam(RATIO_LEVEL4_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
    configParam(RATIO_LEVEL5_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
    configParam(RATIO_LEVEL6_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
    configParam(RATIO_LEVEL7_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
    configParam(RATIO_LEVEL8_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
  }

  void process(const ProcessArgs &args) override {
    outputs[OUT1_OUTPUT].setVoltage(rack::math::clamp(
        clipSignal(inputs[IN1_INPUT].getVoltage(),
                   inputs[RATIO1_INPUT].isConnected()
                       ? (inputs[RATIO1_INPUT].getVoltage() / 10.f) *
                             params[RATIO_LEVEL1_PARAM].getValue()
                       : params[RATIO_LEVEL1_PARAM].getValue()),
        -10.f, 10.f));
    outputs[OUT2_OUTPUT].setVoltage(rack::math::clamp(
        clipSignal(inputs[IN2_INPUT].getVoltage(),
                   inputs[RATIO2_INPUT].isConnected()
                       ? (inputs[RATIO2_INPUT].getVoltage() / 10.f) *
                             params[RATIO_LEVEL2_PARAM].getValue()
                       : params[RATIO_LEVEL2_PARAM].getValue()),
        -10.f, 10.f));
    outputs[OUT3_OUTPUT].setVoltage(rack::math::clamp(
        clipSignal(inputs[IN3_INPUT].getVoltage(),
                   inputs[RATIO3_INPUT].isConnected()
                       ? (inputs[RATIO3_INPUT].getVoltage() / 10.f) *
                             params[RATIO_LEVEL3_PARAM].getValue()
                       : params[RATIO_LEVEL3_PARAM].getValue()),
        -10.f, 10.f));
    outputs[OUT4_OUTPUT].setVoltage(rack::math::clamp(
        clipSignal(inputs[IN4_INPUT].getVoltage(),
                   inputs[RATIO4_INPUT].isConnected()
                       ? (inputs[RATIO4_INPUT].getVoltage() / 10.f) *
                             params[RATIO_LEVEL4_PARAM].getValue()
                       : params[RATIO_LEVEL4_PARAM].getValue()),
        -10.f, 10.f));
    outputs[OUT5_OUTPUT].setVoltage(rack::math::clamp(
        clipSignal(inputs[IN5_INPUT].getVoltage(),
                   inputs[RATIO5_INPUT].isConnected()
                       ? (inputs[RATIO5_INPUT].getVoltage() / 10.f) *
                             params[RATIO_LEVEL5_PARAM].getValue()
                       : params[RATIO_LEVEL5_PARAM].getValue()),
        -10.f, 10.f));
    outputs[OUT6_OUTPUT].setVoltage(rack::math::clamp(
        clipSignal(inputs[IN6_INPUT].getVoltage(),
                   inputs[RATIO6_INPUT].isConnected()
                       ? (inputs[RATIO6_INPUT].getVoltage() / 10.f) *
                             params[RATIO_LEVEL6_PARAM].getValue()
                       : params[RATIO_LEVEL6_PARAM].getValue()),
        -10.f, 10.f));
    outputs[OUT7_OUTPUT].setVoltage(rack::math::clamp(
        clipSignal(inputs[IN7_INPUT].getVoltage(),
                   inputs[RATIO7_INPUT].isConnected()
                       ? (inputs[RATIO7_INPUT].getVoltage() / 10.f) *
                             params[RATIO_LEVEL7_PARAM].getValue()
                       : params[RATIO_LEVEL7_PARAM].getValue()),
        -10.f, 10.f));
    outputs[OUT8_OUTPUT].setVoltage(rack::math::clamp(
        clipSignal(inputs[IN8_INPUT].getVoltage(),
                   inputs[RATIO8_INPUT].isConnected()
                       ? (inputs[RATIO8_INPUT].getVoltage() / 10.f) *
                             params[RATIO_LEVEL8_PARAM].getValue()
                       : params[RATIO_LEVEL8_PARAM].getValue()),
        -10.f, 10.f));
  }
};

struct ClipWidget : StalysModuleWidget {
  static constexpr int hp = 12;

  ClipWidget(Clip *module) {
    setModule(module);
    box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);
    setPanel(box.size, "Clip");

    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 10.16)), module,
                                            Clip::RATIO_LEVEL1_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 25.4)), module,
                                            Clip::RATIO_LEVEL2_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 40.64)), module,
                                            Clip::RATIO_LEVEL3_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 55.88)), module,
                                            Clip::RATIO_LEVEL4_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 71.12)), module,
                                            Clip::RATIO_LEVEL5_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 86.36)), module,
                                            Clip::RATIO_LEVEL6_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 101.6)), module,
                                            Clip::RATIO_LEVEL7_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 116.84)), module,
                                            Clip::RATIO_LEVEL8_PARAM));

    addInput(createInputCentered<port>(mm2px(Vec(7.62, 10.16)), module,
                                       Clip::IN1_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 10.16)), module,
                                       Clip::RATIO1_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 25.4)), module,
                                       Clip::IN2_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 25.4)), module,
                                       Clip::RATIO2_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 40.64)), module,
                                       Clip::IN3_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 40.64)), module,
                                       Clip::RATIO3_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 55.88)), module,
                                       Clip::IN4_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 55.88)), module,
                                       Clip::RATIO4_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 71.12)), module,
                                       Clip::IN5_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 71.12)), module,
                                       Clip::RATIO5_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 86.36)), module,
                                       Clip::IN6_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 86.36)), module,
                                       Clip::RATIO6_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 101.6)), module,
                                       Clip::IN7_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 101.6)), module,
                                       Clip::RATIO7_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 116.84)), module,
                                       Clip::IN8_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 116.84)), module,
                                       Clip::RATIO8_INPUT));

    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 10.16)), module,
                                         Clip::OUT1_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 25.4)), module,
                                         Clip::OUT2_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 40.64)), module,
                                         Clip::OUT3_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 55.88)), module,
                                         Clip::OUT4_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 71.12)), module,
                                         Clip::OUT5_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 86.36)), module,
                                         Clip::OUT6_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 101.6)), module,
                                         Clip::OUT7_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 116.84)), module,
                                         Clip::OUT8_OUTPUT));
  }
};

Model *modelClip = createModel<Clip, ClipWidget>("Clip");
