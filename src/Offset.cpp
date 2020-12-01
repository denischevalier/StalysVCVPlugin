#include "plugin.hpp"


struct Offset : Module {
	enum ParamIds {
		IN1_PARAM,
		IN2_PARAM,
		IN3_PARAM,
		IN4_PARAM,
		IN5_PARAM,
		IN6_PARAM,
		IN7_PARAM,
		IN8_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
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

	Offset() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(IN1_PARAM, -10.f, 10.f, 0.f, "Offset value");
		configParam(IN2_PARAM, -10.f, 10.f, 0.f, "Offset value");
		configParam(IN3_PARAM, -10.f, 10.f, 0.f, "Offset value");
		configParam(IN4_PARAM, -10.f, 10.f, 0.f, "Offset value");
		configParam(IN5_PARAM, -10.f, 10.f, 0.f, "Offset value");
		configParam(IN6_PARAM, -10.f, 10.f, 0.f, "Offset value");
		configParam(IN7_PARAM, -10.f, 10.f, 0.f, "Offset value");
		configParam(IN8_PARAM, -10.f, 10.f, 0.f, "Offset value");
	}

	void process(const ProcessArgs& args) override {
		outputs[OUT1_OUTPUT].setVoltage(params[IN1_PARAM].getValue());
		outputs[OUT2_OUTPUT].setVoltage(params[IN2_PARAM].getValue());
		outputs[OUT3_OUTPUT].setVoltage(params[IN3_PARAM].getValue());
		outputs[OUT4_OUTPUT].setVoltage(params[IN4_PARAM].getValue());
		outputs[OUT5_OUTPUT].setVoltage(params[IN5_PARAM].getValue());
		outputs[OUT6_OUTPUT].setVoltage(params[IN6_PARAM].getValue());
		outputs[OUT7_OUTPUT].setVoltage(params[IN7_PARAM].getValue());
		outputs[OUT8_OUTPUT].setVoltage(params[IN8_PARAM].getValue());
	}
};


struct OffsetWidget : ModuleWidget {
	OffsetWidget(Offset* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Offset.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.938, 11.798)), module, Offset::IN1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.938, 26.351)), module, Offset::IN2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.938, 40.903)), module, Offset::IN3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.938, 55.562)), module, Offset::IN4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.938, 70.007)), module, Offset::IN5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.937, 84.559)), module, Offset::IN6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.937, 99.111)), module, Offset::IN7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(7.937, 113.663)), module, Offset::IN8_PARAM));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 11.906)), module, Offset::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 26.458)), module, Offset::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 41.01)), module, Offset::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 55.67)), module, Offset::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 70.115)), module, Offset::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 84.667)), module, Offset::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 99.219)), module, Offset::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 113.771)), module, Offset::OUT8_OUTPUT));
	}
};


Model* modelOffset = createModel<Offset, OffsetWidget>("Offset");
