#include "Common.hpp"


struct Multiplier : StalysModule {
  enum ParamIds {
    CARRIER_LEVEL1_PARAM,
    CARRIER_LEVEL2_PARAM,
    CARRIER_LEVEL3_PARAM,
    CARRIER_LEVEL4_PARAM,
    CARRIER_LEVEL5_PARAM,
    CARRIER_LEVEL6_PARAM,
    CARRIER_LEVEL7_PARAM,
    CARRIER_LEVEL8_PARAM,
    NUM_PARAMS
  };
  enum InputIds {
    SIGNAL1_INPUT,
    CARRIER1_INPUT,
    SIGNAL2_INPUT,
    CARRIER2_INPUT,
    SIGNAL3_INPUT,
    CARRIER3_INPUT,
    SIGNAL4_INPUT,
    CARRIER4_INPUT,
    SIGNAL5_INPUT,
    CARRIER5_INPUT,
    SIGNAL6_INPUT,
    CARRIER6_INPUT,
    SIGNAL7_INPUT,
    CARRIER7_INPUT,
    SIGNAL8_INPUT,
    CARRIER8_INPUT,
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

  Multiplier() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
    configParam(CARRIER_LEVEL1_PARAM, -2.f, 2.f, 0.f, "Carrier level");
    configParam(CARRIER_LEVEL2_PARAM, -2.f, 2.f, 0.f, "Carrier level");
    configParam(CARRIER_LEVEL3_PARAM, -2.f, 2.f, 0.f, "Carrier level");
    configParam(CARRIER_LEVEL4_PARAM, -2.f, 2.f, 0.f, "Carrier level");
    configParam(CARRIER_LEVEL5_PARAM, -2.f, 2.f, 0.f, "Carrier level");
    configParam(CARRIER_LEVEL6_PARAM, -2.f, 2.f, 0.f, "Carrier level");
    configParam(CARRIER_LEVEL7_PARAM, -2.f, 2.f, 0.f, "Carrier level");
    configParam(CARRIER_LEVEL8_PARAM, -2.f, 2.f, 0.f, "Carrier level");
  }

  void process(const ProcessArgs &args) override {
    const float results[8] = {
        inputs[SIGNAL1_INPUT].getNormalVoltage(0.f) *
            inputs[CARRIER1_INPUT].getNormalVoltage(5.f) * 4.f *
            exponent(params[CARRIER_LEVEL1_PARAM].getValue()) / 5.f,
        inputs[SIGNAL2_INPUT].getNormalVoltage(0.f) *
            inputs[CARRIER2_INPUT].getNormalVoltage(5.f) * 4.f *
            exponent(params[CARRIER_LEVEL2_PARAM].getValue()) / 5.f,
        inputs[SIGNAL3_INPUT].getNormalVoltage(0.f) *
            inputs[CARRIER3_INPUT].getNormalVoltage(5.f) * 4.f *
            exponent(params[CARRIER_LEVEL3_PARAM].getValue()) / 5.f,
        inputs[SIGNAL4_INPUT].getNormalVoltage(0.f) *
            inputs[CARRIER4_INPUT].getNormalVoltage(5.f) * 4.f *
            exponent(params[CARRIER_LEVEL4_PARAM].getValue()) / 5.f,
        inputs[SIGNAL5_INPUT].getNormalVoltage(0.f) *
            inputs[CARRIER5_INPUT].getNormalVoltage(5.f) * 4.f *
            exponent(params[CARRIER_LEVEL5_PARAM].getValue()) / 5.f,
        inputs[SIGNAL6_INPUT].getNormalVoltage(0.f) *
            inputs[CARRIER6_INPUT].getNormalVoltage(5.f) * 4.f *
            exponent(params[CARRIER_LEVEL6_PARAM].getValue()) / 5.f,
        inputs[SIGNAL7_INPUT].getNormalVoltage(0.f) *
            inputs[CARRIER7_INPUT].getNormalVoltage(5.f) * 4.f *
            exponent(params[CARRIER_LEVEL7_PARAM].getValue()) / 5.f,
        inputs[SIGNAL8_INPUT].getNormalVoltage(0.f) *
            inputs[CARRIER8_INPUT].getNormalVoltage(5.f) * 4.f *
            exponent(params[CARRIER_LEVEL8_PARAM].getValue()) / 5.f,
    };

    const float out1 = results[0];
    const float out2 =
        outputs[OUT1_OUTPUT].isConnected() ? results[1] : results[1] + out1;
    const float out3 =
        outputs[OUT2_OUTPUT].isConnected() ? results[2] : results[2] + out2;
    const float out4 =
        outputs[OUT3_OUTPUT].isConnected() ? results[3] : results[3] + out3;
    const float out5 =
        outputs[OUT4_OUTPUT].isConnected() ? results[4] : results[4] + out4;
    const float out6 =
        outputs[OUT5_OUTPUT].isConnected() ? results[5] : results[5] + out5;
    const float out7 =
        outputs[OUT6_OUTPUT].isConnected() ? results[6] : results[6] + out6;
    const float out8 =
        outputs[OUT7_OUTPUT].isConnected() ? results[7] : results[7] + out7;

    outputs[OUT1_OUTPUT].setVoltage(clipSignal(out1));
    outputs[OUT2_OUTPUT].setVoltage(clipSignal(out2));
    outputs[OUT3_OUTPUT].setVoltage(clipSignal(out3));
    outputs[OUT4_OUTPUT].setVoltage(clipSignal(out4));
    outputs[OUT5_OUTPUT].setVoltage(clipSignal(out5));
    outputs[OUT6_OUTPUT].setVoltage(clipSignal(out6));
    outputs[OUT7_OUTPUT].setVoltage(clipSignal(out7));
    outputs[OUT8_OUTPUT].setVoltage(clipSignal(out8));
  }
};


struct MultiplierWidget : StalysModuleWidget {
  static constexpr int hp = 12;

  MultiplierWidget(Multiplier *module) {
    setModule(module);
    box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);
    setPanel(box.size, "Multiplier");

    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 10.16)), module,
                                            Multiplier::CARRIER_LEVEL1_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 25.4)), module,
                                            Multiplier::CARRIER_LEVEL2_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 40.64)), module,
                                            Multiplier::CARRIER_LEVEL3_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 55.88)), module,
                                            Multiplier::CARRIER_LEVEL4_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 71.12)), module,
                                            Multiplier::CARRIER_LEVEL5_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 86.36)), module,
                                            Multiplier::CARRIER_LEVEL6_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 101.6)), module,
                                            Multiplier::CARRIER_LEVEL7_PARAM));
    addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 116.84)), module,
                                            Multiplier::CARRIER_LEVEL8_PARAM));

    addInput(createInputCentered<port>(mm2px(Vec(7.62, 10.16)), module,
                                       Multiplier::SIGNAL1_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 10.16)), module,
                                       Multiplier::CARRIER1_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 25.4)), module,
                                       Multiplier::SIGNAL2_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 25.4)), module,
                                       Multiplier::CARRIER2_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 40.64)), module,
                                       Multiplier::SIGNAL3_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 40.64)), module,
                                       Multiplier::CARRIER3_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 55.88)), module,
                                       Multiplier::SIGNAL4_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 55.88)), module,
                                       Multiplier::CARRIER4_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 71.12)), module,
                                       Multiplier::SIGNAL5_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 71.12)), module,
                                       Multiplier::CARRIER5_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 86.36)), module,
                                       Multiplier::SIGNAL6_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 86.36)), module,
                                       Multiplier::CARRIER6_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 101.6)), module,
                                       Multiplier::SIGNAL7_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 101.6)), module,
                                       Multiplier::CARRIER7_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 116.84)), module,
                                       Multiplier::SIGNAL8_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 116.84)), module,
                                       Multiplier::CARRIER8_INPUT));

    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 10.16)), module,
                                         Multiplier::OUT1_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 25.4)), module,
                                         Multiplier::OUT2_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 40.64)), module,
                                         Multiplier::OUT3_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 55.88)), module,
                                         Multiplier::OUT4_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 71.12)), module,
                                         Multiplier::OUT5_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 86.36)), module,
                                         Multiplier::OUT6_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 101.6)), module,
                                         Multiplier::OUT7_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 116.84)), module,
                                         Multiplier::OUT8_OUTPUT));
  }
};


Model *modelMultiplier =
    createModel<Multiplier, MultiplierWidget>("Multiplier");
