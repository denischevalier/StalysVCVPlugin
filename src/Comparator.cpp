#include "Common.hpp"


struct Comparator : StalysModule {
	enum ParamIds {
		VALUE_LEVEL1_PARAM,
		VALUE_LEVEL2_PARAM,
		VALUE_LEVEL3_PARAM,
		VALUE_LEVEL4_PARAM,
		VALUE_LEVEL5_PARAM,
		VALUE_LEVEL6_PARAM,
		VALUE_LEVEL7_PARAM,
		VALUE_LEVEL8_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		SIGNAL1_INPUT,
		VALUE1_INPUT,
		SIGNAL2_INPUT,
		VALUE2_INPUT,
		SIGNAL3_INPUT,
		VALUE3_INPUT,
		SIGNAL4_INPUT,
		VALUE4_INPUT,
		SIGNAL5_INPUT,
		VALUE5_INPUT,
		SIGNAL6_INPUT,
		VALUE6_INPUT,
		SIGNAL7_INPUT,
		VALUE7_INPUT,
		SIGNAL8_INPUT,
		VALUE8_INPUT,
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
	enum LightIds {
		NUM_LIGHTS
	};

	Comparator() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(VALUE_LEVEL1_PARAM, -10.f, 10.f, 0.f, "Value1");
		configParam(VALUE_LEVEL2_PARAM, -10.f, 10.f, 0.f, "Value2");
		configParam(VALUE_LEVEL3_PARAM, -10.f, 10.f, 0.f, "Value3");
		configParam(VALUE_LEVEL4_PARAM, -10.f, 10.f, 0.f, "Value4");
		configParam(VALUE_LEVEL5_PARAM, -10.f, 10.f, 0.f, "Value5");
		configParam(VALUE_LEVEL6_PARAM, -10.f, 10.f, 0.f, "Value6");
		configParam(VALUE_LEVEL7_PARAM, -10.f, 10.f, 0.f, "Value7");
		configParam(VALUE_LEVEL8_PARAM, -10.f, 10.f, 0.f, "Value8");
	}

	void process(const ProcessArgs& args) override {
		const bool out1 = inputs[SIGNAL1_INPUT].getVoltage() > inputs[VALUE1_INPUT].getNormalVoltage(10.f) * params[VALUE_LEVEL1_PARAM].getValue()/10;
		const bool out2 = inputs[SIGNAL2_INPUT].getVoltage() > inputs[VALUE2_INPUT].getNormalVoltage(10.f) * params[VALUE_LEVEL2_PARAM].getValue()/10;
		const bool out3 = inputs[SIGNAL3_INPUT].getVoltage() > inputs[VALUE3_INPUT].getNormalVoltage(10.f) * params[VALUE_LEVEL3_PARAM].getValue()/10;
		const bool out4 = inputs[SIGNAL4_INPUT].getVoltage() > inputs[VALUE4_INPUT].getNormalVoltage(10.f) * params[VALUE_LEVEL4_PARAM].getValue()/10;
		const bool out5 = inputs[SIGNAL5_INPUT].getVoltage() > inputs[VALUE5_INPUT].getNormalVoltage(10.f) * params[VALUE_LEVEL5_PARAM].getValue()/10;
		const bool out6 = inputs[SIGNAL6_INPUT].getVoltage() > inputs[VALUE6_INPUT].getNormalVoltage(10.f) * params[VALUE_LEVEL6_PARAM].getValue()/10;
		const bool out7 = inputs[SIGNAL7_INPUT].getVoltage() > inputs[VALUE7_INPUT].getNormalVoltage(10.f) * params[VALUE_LEVEL7_PARAM].getValue()/10;
		const bool out8 = inputs[SIGNAL8_INPUT].getVoltage() > inputs[VALUE8_INPUT].getNormalVoltage(10.f) * params[VALUE_LEVEL8_PARAM].getValue()/10;

		outputs[OUT1_OUTPUT].setVoltage(out1? 10.f: 0.f);
		outputs[OUT2_OUTPUT].setVoltage(out2? 10.f: 0.f);
		outputs[OUT3_OUTPUT].setVoltage(out3? 10.f: 0.f);
		outputs[OUT4_OUTPUT].setVoltage(out4? 10.f: 0.f);
		outputs[OUT5_OUTPUT].setVoltage(out5? 10.f: 0.f);
		outputs[OUT6_OUTPUT].setVoltage(out6? 10.f: 0.f);
		outputs[OUT7_OUTPUT].setVoltage(out7? 10.f: 0.f);
		outputs[OUT8_OUTPUT].setVoltage(out8? 10.f: 0.f);
	}
};


struct ComparatorWidget : StalysModuleWidget {
	static constexpr int hp = 12;
	ComparatorWidget(Comparator* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);
		setPanel(box.size, "Comparator");

		addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 10.16)), module, Comparator::VALUE_LEVEL1_PARAM));
		addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 25.4)), module, Comparator::VALUE_LEVEL2_PARAM));
		addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 40.64)), module, Comparator::VALUE_LEVEL3_PARAM));
		addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 55.88)), module, Comparator::VALUE_LEVEL4_PARAM));
		addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 71.12)), module, Comparator::VALUE_LEVEL5_PARAM));
		addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 86.36)), module, Comparator::VALUE_LEVEL6_PARAM));
		addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 101.6)), module, Comparator::VALUE_LEVEL7_PARAM));
		addParam(createParamCentered<smallKnob>(mm2px(Vec(22.86, 116.84)), module, Comparator::VALUE_LEVEL8_PARAM));

		addInput(createInputCentered<port>(mm2px(Vec(7.62, 10.16)), module, Comparator::SIGNAL1_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 10.16)), module, Comparator::VALUE1_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 25.4)), module, Comparator::SIGNAL2_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 25.4)), module, Comparator::VALUE2_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 40.64)), module, Comparator::SIGNAL3_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 40.64)), module, Comparator::VALUE3_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 55.88)), module, Comparator::SIGNAL4_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 55.88)), module, Comparator::VALUE4_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 71.12)), module, Comparator::SIGNAL5_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 71.12)), module, Comparator::VALUE5_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 86.36)), module, Comparator::SIGNAL6_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 86.36)), module, Comparator::VALUE6_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 101.6)), module, Comparator::SIGNAL7_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 101.6)), module, Comparator::VALUE7_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 116.84)), module, Comparator::SIGNAL8_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 116.84)), module, Comparator::VALUE8_INPUT));

		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 10.16)), module, Comparator::OUT1_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 25.4)), module, Comparator::OUT2_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 40.64)), module, Comparator::OUT3_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 55.88)), module, Comparator::OUT4_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 71.12)), module, Comparator::OUT5_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 86.36)), module, Comparator::OUT6_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 101.6)), module, Comparator::OUT7_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 116.84)), module, Comparator::OUT8_OUTPUT));
	}
};


Model* modelComparator = createModel<Comparator, ComparatorWidget>("Comparator");
