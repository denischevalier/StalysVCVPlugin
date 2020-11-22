#include "plugin.hpp"


struct Comparator : Module {
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
		configParam(VALUE_LEVEL1_PARAM, -10.f, 10.f, 0.f, "");
		configParam(VALUE_LEVEL2_PARAM, -10.f, 10.f, 0.f, "");
		configParam(VALUE_LEVEL3_PARAM, -10.f, 10.f, 0.f, "");
		configParam(VALUE_LEVEL4_PARAM, -10.f, 10.f, 0.f, "");
		configParam(VALUE_LEVEL5_PARAM, -10.f, 10.f, 0.f, "");
		configParam(VALUE_LEVEL6_PARAM, -10.f, 10.f, 0.f, "");
		configParam(VALUE_LEVEL7_PARAM, -10.f, 10.f, 0.f, "");
		configParam(VALUE_LEVEL8_PARAM, -10.f, 10.f, 0.f, "");
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


struct ComparatorWidget : ModuleWidget {
	ComparatorWidget(Comparator* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Comparator.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 13.229)), module, Comparator::VALUE_LEVEL1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 27.781)), module, Comparator::VALUE_LEVEL2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 42.333)), module, Comparator::VALUE_LEVEL3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 56.993)), module, Comparator::VALUE_LEVEL4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 71.437)), module, Comparator::VALUE_LEVEL5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 85.99)), module, Comparator::VALUE_LEVEL6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 100.542)), module, Comparator::VALUE_LEVEL7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 115.094)), module, Comparator::VALUE_LEVEL8_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 13.229)), module, Comparator::SIGNAL1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 13.229)), module, Comparator::VALUE1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 27.781)), module, Comparator::SIGNAL2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 27.781)), module, Comparator::VALUE2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 42.333)), module, Comparator::SIGNAL3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 42.333)), module, Comparator::VALUE3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 56.993)), module, Comparator::SIGNAL4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 56.993)), module, Comparator::VALUE4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 71.437)), module, Comparator::SIGNAL5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 71.438)), module, Comparator::VALUE5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 85.99)), module, Comparator::SIGNAL6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 85.99)), module, Comparator::VALUE6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 100.542)), module, Comparator::SIGNAL7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 100.542)), module, Comparator::VALUE7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 115.094)), module, Comparator::SIGNAL8_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 115.094)), module, Comparator::VALUE8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 13.229)), module, Comparator::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 27.781)), module, Comparator::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 42.333)), module, Comparator::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 56.993)), module, Comparator::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 71.437)), module, Comparator::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 85.99)), module, Comparator::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 100.542)), module, Comparator::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 115.094)), module, Comparator::OUT8_OUTPUT));
	}
};


Model* modelComparator = createModel<Comparator, ComparatorWidget>("Comparator");
