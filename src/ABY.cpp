#include "plugin.hpp"


struct ABY : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		A1_INPUT,
		B1_INPUT,
		TRIG1_INPUT,
		A2_INPUT,
		B2_INPUT,
		TRIG2_INPUT,
		A3_INPUT,
		B3_INPUT,
		TRIG3_INPUT,
		A4_INPUT,
		B4_INPUT,
		TRIG4_INPUT,
		A5_INPUT,
		B5_INPUT,
		TRIG5_INPUT,
		A6_INPUT,
		B6_INPUT,
		TRIG6_INPUT,
		A7_INPUT,
		B7_INPUT,
		TRIG7_INPUT,
		A8_INPUT,
		B8_INPUT,
		TRIG8_INPUT,
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

	ABY() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	rack::dsp::SchmittTrigger trig[8];
	bool aSelected[8] = {true,true,true,true,true,true,true,true};

	void process(const ProcessArgs& args) override {
		aSelected[0] = trig[0].process(inputs[TRIG1_INPUT].getVoltage())? !aSelected[0]: aSelected[0];
		aSelected[1] = trig[1].process(inputs[TRIG2_INPUT].getVoltage())? !aSelected[1]: aSelected[1];
		aSelected[2] = trig[2].process(inputs[TRIG3_INPUT].getVoltage())? !aSelected[2]: aSelected[2];
		aSelected[3] = trig[3].process(inputs[TRIG4_INPUT].getVoltage())? !aSelected[3]: aSelected[3];
		aSelected[4] = trig[4].process(inputs[TRIG5_INPUT].getVoltage())? !aSelected[4]: aSelected[4];
		aSelected[5] = trig[5].process(inputs[TRIG6_INPUT].getVoltage())? !aSelected[5]: aSelected[5];
		aSelected[6] = trig[6].process(inputs[TRIG7_INPUT].getVoltage())? !aSelected[6]: aSelected[6];
		aSelected[7] = trig[7].process(inputs[TRIG8_INPUT].getVoltage())? !aSelected[7]: aSelected[7];

		outputs[OUT1_OUTPUT].setVoltage(aSelected[0]? inputs[A1_INPUT].getVoltage(): inputs[B1_INPUT].getVoltage());
		outputs[OUT2_OUTPUT].setVoltage(aSelected[1]? inputs[A2_INPUT].getVoltage(): inputs[B2_INPUT].getVoltage());
		outputs[OUT3_OUTPUT].setVoltage(aSelected[2]? inputs[A3_INPUT].getVoltage(): inputs[B3_INPUT].getVoltage());
		outputs[OUT4_OUTPUT].setVoltage(aSelected[3]? inputs[A4_INPUT].getVoltage(): inputs[B4_INPUT].getVoltage());
		outputs[OUT5_OUTPUT].setVoltage(aSelected[4]? inputs[A5_INPUT].getVoltage(): inputs[B5_INPUT].getVoltage());
		outputs[OUT6_OUTPUT].setVoltage(aSelected[5]? inputs[A6_INPUT].getVoltage(): inputs[B6_INPUT].getVoltage());
		outputs[OUT7_OUTPUT].setVoltage(aSelected[6]? inputs[A7_INPUT].getVoltage(): inputs[B7_INPUT].getVoltage());
		outputs[OUT8_OUTPUT].setVoltage(aSelected[7]? inputs[A8_INPUT].getVoltage(): inputs[B8_INPUT].getVoltage());
	}
};


struct ABYWidget : ModuleWidget {
	ABYWidget(ABY* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/ABY.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 12.171)), module, ABY::A1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.49, 12.171)), module, ABY::B1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 12.171)), module, ABY::TRIG1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 26.723)), module, ABY::A2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.49, 26.723)), module, ABY::B2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 26.723)), module, ABY::TRIG2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 41.275)), module, ABY::A3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.49, 41.275)), module, ABY::B3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 41.275)), module, ABY::TRIG3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 55.935)), module, ABY::A4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.49, 55.935)), module, ABY::B4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 55.935)), module, ABY::TRIG4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 70.379)), module, ABY::A5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.49, 70.379)), module, ABY::B5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 70.379)), module, ABY::TRIG5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 84.931)), module, ABY::A6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.49, 84.931)), module, ABY::B6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 84.931)), module, ABY::TRIG6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 99.483)), module, ABY::A7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.49, 99.483)), module, ABY::B7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 99.483)), module, ABY::TRIG7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 114.035)), module, ABY::A8_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.49, 114.035)), module, ABY::B8_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 114.035)), module, ABY::TRIG8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 12.171)), module, ABY::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 26.723)), module, ABY::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 41.275)), module, ABY::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 55.935)), module, ABY::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 70.379)), module, ABY::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 84.931)), module, ABY::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 99.483)), module, ABY::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 114.035)), module, ABY::OUT8_OUTPUT));
	}
};


Model* modelABY = createModel<ABY, ABYWidget>("ABY");
