#include "plugin.hpp"
#include "Common.hpp"


struct Diff : Module {
	enum ParamIds {
		NUM_PARAMS
	};
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
	enum LightIds {
		NUM_LIGHTS
	};

	Diff() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs& args) override {
		outputs[OUT1_OUTPUT].setVoltage(clipSignal(inputs[IN1_INPUT].getNormalVoltage(0.f) - inputs[IN2_INPUT].getNormalVoltage(0.f) - inputs[IN3_INPUT].getNormalVoltage(0.f)));
		outputs[OUT2_OUTPUT].setVoltage(clipSignal(inputs[IN4_INPUT].getNormalVoltage(0.f) - inputs[IN5_INPUT].getNormalVoltage(0.f) - inputs[IN6_INPUT].getNormalVoltage(0.f)));
		outputs[OUT3_OUTPUT].setVoltage(clipSignal(inputs[IN7_INPUT].getNormalVoltage(0.f) - inputs[IN8_INPUT].getNormalVoltage(0.f) - inputs[IN9_INPUT].getNormalVoltage(0.f)));
		outputs[OUT4_OUTPUT].setVoltage(clipSignal(inputs[IN10_INPUT].getNormalVoltage(0.f) - inputs[IN11_INPUT].getNormalVoltage(0.f) - inputs[IN12_INPUT].getNormalVoltage(0.f)));
		outputs[OUT5_OUTPUT].setVoltage(clipSignal(inputs[IN13_INPUT].getNormalVoltage(0.f) - inputs[IN14_INPUT].getNormalVoltage(0.f) - inputs[IN15_INPUT].getNormalVoltage(0.f)));
		outputs[OUT6_OUTPUT].setVoltage(clipSignal(inputs[IN16_INPUT].getNormalVoltage(0.f) - inputs[IN17_INPUT].getNormalVoltage(0.f) - inputs[IN18_INPUT].getNormalVoltage(0.f)));
		outputs[OUT7_OUTPUT].setVoltage(clipSignal(inputs[IN19_INPUT].getNormalVoltage(0.f) - inputs[IN20_INPUT].getNormalVoltage(0.f) - inputs[IN21_INPUT].getNormalVoltage(0.f)));
		outputs[OUT8_OUTPUT].setVoltage(clipSignal(inputs[IN22_INPUT].getNormalVoltage(0.f) - inputs[IN23_INPUT].getNormalVoltage(0.f) - inputs[IN24_INPUT].getNormalVoltage(0.f)));
	}
};


struct DiffWidget : ModuleWidget {
	DiffWidget(Diff* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Diff.svg")));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 10.16)), module, Diff::IN1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 10.16)), module, Diff::IN2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 10.16)), module, Diff::IN3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 25.4)), module, Diff::IN4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 25.4)), module, Diff::IN5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 25.4)), module, Diff::IN6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 40.64)), module, Diff::IN7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 40.64)), module, Diff::IN8_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 40.64)), module, Diff::IN9_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 55.88)), module, Diff::IN10_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 55.88)), module, Diff::IN11_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 55.88)), module, Diff::IN12_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 71.12)), module, Diff::IN13_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 71.12)), module, Diff::IN14_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 71.12)), module, Diff::IN15_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 86.36)), module, Diff::IN16_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 86.36)), module, Diff::IN17_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 86.36)), module, Diff::IN18_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 101.6)), module, Diff::IN19_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 101.6)), module, Diff::IN20_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 101.6)), module, Diff::IN21_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.922, 116.415)), module, Diff::IN22_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 116.84)), module, Diff::IN23_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 116.84)), module, Diff::IN24_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 10.16)), module, Diff::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 25.4)), module, Diff::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 40.64)), module, Diff::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 55.88)), module, Diff::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 71.12)), module, Diff::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 86.36)), module, Diff::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 101.6)), module, Diff::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 116.84)), module, Diff::OUT8_OUTPUT));
	}
};


Model* modelDiff = createModel<Diff, DiffWidget>("Diff");
