#include "plugin.hpp"


struct Abs : Module {
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

	Abs() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs& args) override {
		const float ins[8] = {
			inputs[IN1_INPUT].getNormalVoltage(0.f),
			inputs[IN2_INPUT].getNormalVoltage(0.f),
			inputs[IN3_INPUT].getNormalVoltage(0.f),
			inputs[IN4_INPUT].getNormalVoltage(0.f),
			inputs[IN5_INPUT].getNormalVoltage(0.f),
			inputs[IN6_INPUT].getNormalVoltage(0.f),
			inputs[IN7_INPUT].getNormalVoltage(0.f),
			inputs[IN8_INPUT].getNormalVoltage(0.f)
		};

		outputs[OUT1_OUTPUT].setVoltage(ins[0] >= 0.f? ins[0]: -1.f*ins[0]);
		outputs[OUT2_OUTPUT].setVoltage(ins[1] >= 0.f? ins[1]: -1.f*ins[1]);
		outputs[OUT3_OUTPUT].setVoltage(ins[2] >= 0.f? ins[2]: -1.f*ins[2]);
		outputs[OUT4_OUTPUT].setVoltage(ins[3] >= 0.f? ins[3]: -1.f*ins[3]);
		outputs[OUT5_OUTPUT].setVoltage(ins[4] >= 0.f? ins[4]: -1.f*ins[4]);
		outputs[OUT6_OUTPUT].setVoltage(ins[5] >= 0.f? ins[5]: -1.f*ins[5]);
		outputs[OUT7_OUTPUT].setVoltage(ins[6] >= 0.f? ins[6]: -1.f*ins[6]);
		outputs[OUT8_OUTPUT].setVoltage(ins[7] >= 0.f? ins[7]: -1.f*ins[7]);
	}
};


struct AbsWidget : ModuleWidget {
	AbsWidget(Abs* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Abs.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 11.798)), module, Abs::IN1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 26.351)), module, Abs::IN2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 40.903)), module, Abs::IN3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 55.562)), module, Abs::IN4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 70.007)), module, Abs::IN5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.937, 84.559)), module, Abs::IN6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.937, 99.111)), module, Abs::IN7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.937, 113.663)), module, Abs::IN8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 11.906)), module, Abs::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 26.458)), module, Abs::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 41.01)), module, Abs::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 55.67)), module, Abs::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 70.115)), module, Abs::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 84.667)), module, Abs::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 99.219)), module, Abs::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 113.771)), module, Abs::OUT8_OUTPUT));
	}
};


Model* modelAbs = createModel<Abs, AbsWidget>("Abs");
