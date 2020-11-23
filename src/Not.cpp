#include "plugin.hpp"


struct Not : Module {
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

	Not() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs& args) override {
		outputs[OUT1_OUTPUT].setVoltage(inputs[IN1_INPUT].getNormalVoltage(0.f) > 1.f? 0.f: 10.f);
		outputs[OUT2_OUTPUT].setVoltage(inputs[IN2_INPUT].getNormalVoltage(0.f) > 1.f? 0.f: 10.f);
		outputs[OUT3_OUTPUT].setVoltage(inputs[IN3_INPUT].getNormalVoltage(0.f) > 1.f? 0.f: 10.f);
		outputs[OUT4_OUTPUT].setVoltage(inputs[IN4_INPUT].getNormalVoltage(0.f) > 1.f? 0.f: 10.f);
		outputs[OUT5_OUTPUT].setVoltage(inputs[IN5_INPUT].getNormalVoltage(0.f) > 1.f? 0.f: 10.f);
		outputs[OUT6_OUTPUT].setVoltage(inputs[IN6_INPUT].getNormalVoltage(0.f) > 1.f? 0.f: 10.f);
		outputs[OUT7_OUTPUT].setVoltage(inputs[IN7_INPUT].getNormalVoltage(0.f) > 1.f? 0.f: 10.f);
		outputs[OUT8_OUTPUT].setVoltage(inputs[IN8_INPUT].getNormalVoltage(0.f) > 1.f? 0.f: 10.f);
	}
};


struct NotWidget : ModuleWidget {
	NotWidget(Not* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Not.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 11.798)), module, Not::IN1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 26.351)), module, Not::IN2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 40.903)), module, Not::IN3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 55.562)), module, Not::IN4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 70.007)), module, Not::IN5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.937, 84.559)), module, Not::IN6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.937, 99.111)), module, Not::IN7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.937, 113.663)), module, Not::IN8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 11.906)), module, Not::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 26.458)), module, Not::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 41.01)), module, Not::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 55.67)), module, Not::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 70.115)), module, Not::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 84.667)), module, Not::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 99.219)), module, Not::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 113.771)), module, Not::OUT8_OUTPUT));
	}
};


Model* modelNot = createModel<Not, NotWidget>("Not");
