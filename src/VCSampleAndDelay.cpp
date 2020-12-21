#include "Common.hpp"

struct VCSampleAndDelay : StalysModule {
  enum ParamIds {
    STEPS_LEVEL1_PARAM,
    STEPS_LEVEL2_PARAM,
    STEPS_LEVEL3_PARAM,
    STEPS_LEVEL4_PARAM,
    STEPS_LEVEL5_PARAM,
    STEPS_LEVEL6_PARAM,
    STEPS_LEVEL7_PARAM,
    STEPS_LEVEL8_PARAM,
    NUM_PARAMS
  };
  enum InputIds {
    STEPS1_INPUT,
    CLOCK1_INPUT,
    SIGNAL1_INPUT,
    CLOCK2_INPUT,
    SIGNAL2_INPUT,
    STEPS2_INPUT,
    CLOCK3_INPUT,
    SIGNAL3_INPUT,
    STEPS3_INPUT,
    CLOCK4_INPUT,
    SIGNAL4_INPUT,
    STEPS4_INPUT,
    CLOCK5_INPUT,
    SIGNAL5_INPUT,
    STEPS5_INPUT,
    CLOCK6_INPUT,
    SIGNAL6_INPUT,
    STEPS6_INPUT,
    CLOCK7_INPUT,
    SIGNAL7_INPUT,
    STEPS7_INPUT,
    CLOCK8_INPUT,
    SIGNAL8_INPUT,
    STEPS8_INPUT,
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

  VCSampleAndDelay() {
    config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
    configParam(STEPS_LEVEL1_PARAM, 1.f, 10.f, 1.f, "Steps");
    configParam(STEPS_LEVEL2_PARAM, 1.f, 10.f, 1.f, "Steps");
    configParam(STEPS_LEVEL3_PARAM, 1.f, 10.f, 1.f, "Steps");
    configParam(STEPS_LEVEL4_PARAM, 1.f, 10.f, 1.f, "Steps");
    configParam(STEPS_LEVEL5_PARAM, 1.f, 10.f, 1.f, "Steps");
    configParam(STEPS_LEVEL6_PARAM, 1.f, 10.f, 1.f, "Steps");
    configParam(STEPS_LEVEL7_PARAM, 1.f, 10.f, 1.f, "Steps");
    configParam(STEPS_LEVEL8_PARAM, 1.f, 10.f, 1.f, "Steps");
  }

  float counters[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
  float values[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
  rack::dsp::SchmittTrigger trig1;
  rack::dsp::SchmittTrigger trig2;
  rack::dsp::SchmittTrigger trig3;
  rack::dsp::SchmittTrigger trig4;
  rack::dsp::SchmittTrigger trig5;
  rack::dsp::SchmittTrigger trig6;
  rack::dsp::SchmittTrigger trig7;
  rack::dsp::SchmittTrigger trig8;

  void process(const ProcessArgs &args) override {
    const float steps[8] = {
        rack::math::clamp(std::floor(inputs[STEPS1_INPUT].getNormalVoltage(
                              params[STEPS_LEVEL1_PARAM].getValue())),
                          1.f, 10.f),
        rack::math::clamp(std::floor(inputs[STEPS2_INPUT].getNormalVoltage(
                              params[STEPS_LEVEL2_PARAM].getValue())),
                          1.f, 10.f),
        rack::math::clamp(std::floor(inputs[STEPS3_INPUT].getNormalVoltage(
                              params[STEPS_LEVEL3_PARAM].getValue())),
                          1.f, 10.f),
        rack::math::clamp(std::floor(inputs[STEPS4_INPUT].getNormalVoltage(
                              params[STEPS_LEVEL4_PARAM].getValue())),
                          1.f, 10.f),
        rack::math::clamp(std::floor(inputs[STEPS5_INPUT].getNormalVoltage(
                              params[STEPS_LEVEL5_PARAM].getValue())),
                          1.f, 10.f),
        rack::math::clamp(std::floor(inputs[STEPS6_INPUT].getNormalVoltage(
                              params[STEPS_LEVEL6_PARAM].getValue())),
                          1.f, 10.f),
        rack::math::clamp(std::floor(inputs[STEPS7_INPUT].getNormalVoltage(
                              params[STEPS_LEVEL7_PARAM].getValue())),
                          1.f, 10.f),
        rack::math::clamp(std::floor(inputs[STEPS8_INPUT].getNormalVoltage(
                              params[STEPS_LEVEL8_PARAM].getValue())),
                          1.f, 10.f),
    };

    if (trig1.process(inputs[CLOCK1_INPUT].getVoltage())) {
      if (counters[0] < steps[0]) {
        counters[0]++;
      } else {
        counters[0] = 0.f;
        values[0] = inputs[SIGNAL1_INPUT].getVoltage();
      }
    }
    if (trig2.process(inputs[CLOCK2_INPUT].getVoltage())) {
      if (counters[1] < steps[1]) {
        counters[1]++;
      } else {
        counters[1] = 0.f;
        values[1] = inputs[SIGNAL2_INPUT].getVoltage();
      }
    }
    if (trig3.process(inputs[CLOCK3_INPUT].getVoltage())) {
      if (counters[2] < steps[2]) {
        counters[2]++;
      } else {
        counters[2] = 0.f;
        values[2] = inputs[SIGNAL3_INPUT].getVoltage();
      }
    }
    if (trig4.process(inputs[CLOCK4_INPUT].getVoltage())) {
      if (counters[3] < steps[3]) {
        counters[3]++;
      } else {
        counters[3] = 0.f;
        values[3] = inputs[SIGNAL4_INPUT].getVoltage();
      }
    }
    if (trig5.process(inputs[CLOCK5_INPUT].getVoltage())) {
      if (counters[4] < steps[4]) {
        counters[4]++;
      } else {
        counters[4] = 0.f;
        values[4] = inputs[SIGNAL5_INPUT].getVoltage();
      }
    }
    if (trig6.process(inputs[CLOCK6_INPUT].getVoltage())) {
      if (counters[5] < steps[5]) {
        counters[5]++;
      } else {
        counters[5] = 0.f;
        values[5] = inputs[SIGNAL6_INPUT].getVoltage();
      }
    }
    if (trig7.process(inputs[CLOCK7_INPUT].getVoltage())) {
      if (counters[6] < steps[6]) {
        counters[6]++;
      } else {
        counters[6] = 0.f;
        values[6] = inputs[SIGNAL7_INPUT].getVoltage();
      }
    }
    if (trig8.process(inputs[CLOCK8_INPUT].getVoltage())) {
      if (counters[7] < steps[7]) {
        counters[7]++;
      } else {
        counters[7] = 0.f;
        values[7] = inputs[SIGNAL8_INPUT].getVoltage();
      }
    }

    outputs[OUT1_OUTPUT].setVoltage(values[0]);
    outputs[OUT2_OUTPUT].setVoltage(values[1]);
    outputs[OUT3_OUTPUT].setVoltage(values[2]);
    outputs[OUT4_OUTPUT].setVoltage(values[3]);
    outputs[OUT5_OUTPUT].setVoltage(values[4]);
    outputs[OUT6_OUTPUT].setVoltage(values[5]);
    outputs[OUT7_OUTPUT].setVoltage(values[6]);
    outputs[OUT8_OUTPUT].setVoltage(values[7]);
  }
};

struct VCSampleAndDelayWidget : StalysModuleWidget {
  static constexpr int hp = 15;

  VCSampleAndDelayWidget(VCSampleAndDelay *module) {
    setModule(module);
    box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);
    setPanel(box.size, "VCSampleAndDelay");

    addParam(
        createParamCentered<snapKnob>(mm2px(Vec(7.62, 10.398)), module,
                                      VCSampleAndDelay::STEPS_LEVEL1_PARAM));
    addParam(createParamCentered<snapKnob>(
        mm2px(Vec(7.62, 25.4)), module, VCSampleAndDelay::STEPS_LEVEL2_PARAM));
    addParam(createParamCentered<snapKnob>(
        mm2px(Vec(7.62, 40.64)), module, VCSampleAndDelay::STEPS_LEVEL3_PARAM));
    addParam(createParamCentered<snapKnob>(
        mm2px(Vec(7.62, 55.88)), module, VCSampleAndDelay::STEPS_LEVEL4_PARAM));
    addParam(createParamCentered<snapKnob>(
        mm2px(Vec(7.62, 71.12)), module, VCSampleAndDelay::STEPS_LEVEL5_PARAM));
    addParam(createParamCentered<snapKnob>(
        mm2px(Vec(7.62, 86.36)), module, VCSampleAndDelay::STEPS_LEVEL6_PARAM));
    addParam(createParamCentered<snapKnob>(
        mm2px(Vec(7.62, 101.6)), module, VCSampleAndDelay::STEPS_LEVEL7_PARAM));
    addParam(
        createParamCentered<snapKnob>(mm2px(Vec(7.62, 116.84)), module,
                                      VCSampleAndDelay::STEPS_LEVEL8_PARAM));

    addInput(createInputCentered<port>(mm2px(Vec(38.1, 10.16)), module,
                                       VCSampleAndDelay::CLOCK1_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(53.34, 10.16)), module,
                                       VCSampleAndDelay::SIGNAL1_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.622, 10.398)), module,
                                       VCSampleAndDelay::STEPS1_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 25.4)), module,
                                       VCSampleAndDelay::STEPS2_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 25.4)), module,
                                       VCSampleAndDelay::CLOCK2_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(53.34, 25.4)), module,
                                       VCSampleAndDelay::SIGNAL2_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 40.64)), module,
                                       VCSampleAndDelay::STEPS3_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 40.64)), module,
                                       VCSampleAndDelay::CLOCK3_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(53.34, 40.64)), module,
                                       VCSampleAndDelay::SIGNAL3_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 55.88)), module,
                                       VCSampleAndDelay::STEPS4_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 55.88)), module,
                                       VCSampleAndDelay::CLOCK4_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(53.34, 55.88)), module,
                                       VCSampleAndDelay::SIGNAL4_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 71.12)), module,
                                       VCSampleAndDelay::STEPS5_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 71.12)), module,
                                       VCSampleAndDelay::CLOCK5_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(53.34, 71.12)), module,
                                       VCSampleAndDelay::SIGNAL5_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 86.36)), module,
                                       VCSampleAndDelay::STEPS6_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 86.36)), module,
                                       VCSampleAndDelay::CLOCK6_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(53.34, 86.36)), module,
                                       VCSampleAndDelay::SIGNAL6_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 101.6)), module,
                                       VCSampleAndDelay::STEPS7_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 101.6)), module,
                                       VCSampleAndDelay::CLOCK7_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(53.34, 101.6)), module,
                                       VCSampleAndDelay::SIGNAL7_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 116.84)), module,
                                       VCSampleAndDelay::STEPS8_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 116.84)), module,
                                       VCSampleAndDelay::CLOCK8_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(53.34, 116.84)), module,
                                       VCSampleAndDelay::SIGNAL8_INPUT));

    addOutput(createOutputCentered<port>(mm2px(Vec(68.342, 10.16)), module,
                                         VCSampleAndDelay::OUT1_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(68.58, 25.4)), module,
                                         VCSampleAndDelay::OUT2_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(68.58, 40.64)), module,
                                         VCSampleAndDelay::OUT3_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(68.58, 55.88)), module,
                                         VCSampleAndDelay::OUT4_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(68.58, 71.12)), module,
                                         VCSampleAndDelay::OUT5_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(68.58, 86.36)), module,
                                         VCSampleAndDelay::OUT6_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(68.58, 101.6)), module,
                                         VCSampleAndDelay::OUT7_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(68.58, 116.84)), module,
                                         VCSampleAndDelay::OUT8_OUTPUT));
  }
};

Model *modelVCSampleAndDelay =
    createModel<VCSampleAndDelay, VCSampleAndDelayWidget>("VCSampleAndDelay");
