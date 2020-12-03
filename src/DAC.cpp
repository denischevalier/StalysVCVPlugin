#include "plugin.hpp"
#include "Common.hpp"


struct DAC : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		TRIG1_INPUT,
		TRIG2_INPUT,
		TRIG3_INPUT,
		TRIG4_INPUT,
		TRIG5_INPUT,
		TRIG6_INPUT,
		TRIG7_INPUT,
		TRIG8_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	DAC() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs& args) override {
		outputs[OUT_OUTPUT].setVoltage(clipSignal((
			(inputs[TRIG1_INPUT].getVoltage() > 1.f? 1.f: 0.f)+
			(inputs[TRIG2_INPUT].getVoltage() > 1.f? 2.f: 0.f)+
			(inputs[TRIG3_INPUT].getVoltage() > 1.f? 4.f: 0.f)+
			(inputs[TRIG4_INPUT].getVoltage() > 1.f? 8.f: 0.f)+
			(inputs[TRIG5_INPUT].getVoltage() > 1.f? 16.f: 0.f)+
			(inputs[TRIG6_INPUT].getVoltage() > 1.f? 32.f: 0.f)+
			(inputs[TRIG7_INPUT].getVoltage() > 1.f? 64.f: 0.f)
		) / (inputs[TRIG8_INPUT].getVoltage() > 1.f? -12.7f: 12.7f)));
	}
};


struct DACWidget : ModuleWidget {
	DACWidget(DAC* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/DAC.svg")));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 10.16)), module, DAC::TRIG1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 25.4)), module, DAC::TRIG2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 40.64)), module, DAC::TRIG3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 55.88)), module, DAC::TRIG4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 71.12)), module, DAC::TRIG5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 86.36)), module, DAC::TRIG6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 101.6)), module, DAC::TRIG7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 116.84)), module, DAC::TRIG8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 10.16)), module, DAC::OUT_OUTPUT));
	}
};


Model* modelDAC = createModel<DAC, DACWidget>("DAC");
