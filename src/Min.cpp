#include "Common.hpp"

struct Min : StalysModule {
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
    IN9_INPUT,
    IN10_INPUT,
    IN11_INPUT,
    IN12_INPUT,
    IN13_INPUT,
    IN14_INPUT,
    IN15_INPUT,
    IN16_INPUT,
    IN17_INPUT,
    IN18_INPUT,
    IN19_INPUT,
    IN20_INPUT,
    IN21_INPUT,
    IN22_INPUT,
    IN23_INPUT,
    IN24_INPUT,
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

  Min() { config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS); }

  void process(const ProcessArgs &args) override {
    const float ins[24] = {inputs[IN1_INPUT].getNormalVoltage(10.f),
                           inputs[IN2_INPUT].getNormalVoltage(10.f),
                           inputs[IN3_INPUT].getNormalVoltage(10.f),
                           inputs[IN4_INPUT].getNormalVoltage(10.f),
                           inputs[IN5_INPUT].getNormalVoltage(10.f),
                           inputs[IN6_INPUT].getNormalVoltage(10.f),
                           inputs[IN7_INPUT].getNormalVoltage(10.f),
                           inputs[IN8_INPUT].getNormalVoltage(10.f),
                           inputs[IN9_INPUT].getNormalVoltage(10.f),
                           inputs[IN10_INPUT].getNormalVoltage(10.f),
                           inputs[IN11_INPUT].getNormalVoltage(10.f),
                           inputs[IN12_INPUT].getNormalVoltage(10.f),
                           inputs[IN13_INPUT].getNormalVoltage(10.f),
                           inputs[IN14_INPUT].getNormalVoltage(10.f),
                           inputs[IN15_INPUT].getNormalVoltage(10.f),
                           inputs[IN16_INPUT].getNormalVoltage(10.f),
                           inputs[IN17_INPUT].getNormalVoltage(10.f),
                           inputs[IN18_INPUT].getNormalVoltage(10.f),
                           inputs[IN19_INPUT].getNormalVoltage(10.f),
                           inputs[IN20_INPUT].getNormalVoltage(10.f),
                           inputs[IN21_INPUT].getNormalVoltage(10.f),
                           inputs[IN22_INPUT].getNormalVoltage(10.f),
                           inputs[IN23_INPUT].getNormalVoltage(10.f),
                           inputs[IN24_INPUT].getNormalVoltage(10.f)};

    const float outs[8] = {std::min(std::min(ins[0], ins[1]), ins[2]),
                           std::min(std::min(ins[3], ins[4]), ins[5]),
                           std::min(std::min(ins[6], ins[7]), ins[8]),
                           std::min(std::min(ins[9], ins[10]), ins[11]),
                           std::min(std::min(ins[12], ins[13]), ins[14]),
                           std::min(std::min(ins[15], ins[16]), ins[17]),
                           std::min(std::min(ins[18], ins[19]), ins[20]),
                           std::min(std::min(ins[21], ins[22]), ins[23])};

    const float out2 = outputs[OUT1_OUTPUT].isConnected()
                           ? outs[1]
                           : std::min(outs[0],outs[1]);
    const float out3 =
        outputs[OUT2_OUTPUT].isConnected() ? outs[2] : std::min(out2, outs[2]);
    const float out4 =
        outputs[OUT3_OUTPUT].isConnected() ? outs[3] : std::min(out3, outs[3]);
    const float out5 =
        outputs[OUT4_OUTPUT].isConnected() ? outs[4] : std::min(out4, outs[4]);
    const float out6 =
        outputs[OUT5_OUTPUT].isConnected() ? outs[5] : std::min(out5, outs[5]);
    const float out7 =
        outputs[OUT6_OUTPUT].isConnected() ? outs[6] : std::min(out6, outs[6]);
    const float out8 =
        outputs[OUT7_OUTPUT].isConnected() ? outs[7] : std::min(out7, outs[7]);

    outputs[OUT1_OUTPUT].setVoltage(outs[0]);
    outputs[OUT2_OUTPUT].setVoltage(out2);
    outputs[OUT3_OUTPUT].setVoltage(out3);
    outputs[OUT4_OUTPUT].setVoltage(out4);
    outputs[OUT5_OUTPUT].setVoltage(out5);
    outputs[OUT6_OUTPUT].setVoltage(out6);
    outputs[OUT7_OUTPUT].setVoltage(out7);
    outputs[OUT8_OUTPUT].setVoltage(out8);
  }
};

struct MinWidget : StalysModuleWidget {
  static constexpr int hp = 12;

  MinWidget(Min *module) {
    setModule(module);
    box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);
    setPanel(box.size, "Min");

    addInput(createInputCentered<port>(mm2px(Vec(7.62, 10.16)), module,
                                       Min::IN1_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 10.16)), module,
                                       Min::IN2_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 10.16)), module,
                                       Min::IN3_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 25.4)), module,
                                       Min::IN4_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 25.4)), module,
                                       Min::IN5_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 25.4)), module,
                                       Min::IN6_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 40.64)), module,
                                       Min::IN7_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 40.64)), module,
                                       Min::IN8_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 40.64)), module,
                                       Min::IN9_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 55.88)), module,
                                       Min::IN10_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 55.88)), module,
                                       Min::IN11_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 55.88)), module,
                                       Min::IN12_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 71.12)), module,
                                       Min::IN13_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 71.12)), module,
                                       Min::IN14_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 71.12)), module,
                                       Min::IN15_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 86.36)), module,
                                       Min::IN16_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 86.36)), module,
                                       Min::IN17_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 86.36)), module,
                                       Min::IN18_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.62, 101.6)), module,
                                       Min::IN19_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 101.6)), module,
                                       Min::IN20_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 101.6)), module,
                                       Min::IN21_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(7.922, 116.415)), module,
                                       Min::IN22_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(22.86, 116.84)), module,
                                       Min::IN23_INPUT));
    addInput(createInputCentered<port>(mm2px(Vec(38.1, 116.84)), module,
                                       Min::IN24_INPUT));

    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 10.16)), module,
                                         Min::OUT1_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 25.4)), module,
                                         Min::OUT2_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 40.64)), module,
                                         Min::OUT3_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 55.88)), module,
                                         Min::OUT4_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 71.12)), module,
                                         Min::OUT5_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 86.36)), module,
                                         Min::OUT6_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 101.6)), module,
                                         Min::OUT7_OUTPUT));
    addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 116.84)), module,
                                         Min::OUT8_OUTPUT));
  }
};

Model *modelMin = createModel<Min, MinWidget>("Min");
