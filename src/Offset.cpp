#include "Common.hpp"


struct Offset : StalysModule {
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


struct OffsetWidget : StalysModuleWidget {
	static constexpr int hp = 6;

	OffsetWidget(Offset* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);
		setPanel(box.size, "Offset");

		addParam(createParamCentered<knob>(mm2px(Vec(7.62, 10.16)), module, Offset::IN1_PARAM));
		addParam(createParamCentered<knob>(mm2px(Vec(7.62, 25.4)), module, Offset::IN2_PARAM));
		addParam(createParamCentered<knob>(mm2px(Vec(7.62, 40.64)), module, Offset::IN3_PARAM));
		addParam(createParamCentered<knob>(mm2px(Vec(7.514, 55.88)), module, Offset::IN4_PARAM));
		addParam(createParamCentered<knob>(mm2px(Vec(7.514, 71.12)), module, Offset::IN5_PARAM));
		addParam(createParamCentered<knob>(mm2px(Vec(7.514, 86.36)), module, Offset::IN6_PARAM));
		addParam(createParamCentered<knob>(mm2px(Vec(7.514, 101.6)), module, Offset::IN7_PARAM));
		addParam(createParamCentered<knob>(mm2px(Vec(7.514, 116.84)), module, Offset::IN8_PARAM));

		addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 10.16)), module, Offset::OUT1_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 25.4)), module, Offset::OUT2_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 40.64)), module, Offset::OUT3_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 55.88)), module, Offset::OUT4_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 71.12)), module, Offset::OUT5_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 86.36)), module, Offset::OUT6_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 101.6)), module, Offset::OUT7_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(22.86, 116.84)), module, Offset::OUT8_OUTPUT));
	}
};


Model* modelOffset = createModel<Offset, OffsetWidget>("Offset");
