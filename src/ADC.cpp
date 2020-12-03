#include "plugin.hpp"
#include "Common.hpp"


struct ADC : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		SIGNAL_INPUT,
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

	ADC() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs& args) override {
		const float signal = clip(inputs[SIGNAL_INPUT].getVoltage()/10.f, 0.14925373313f);

		const uint8_t bits = uint8_t(std::roundf(std::abs(signal)*127));

		outputs[OUT1_OUTPUT].setVoltage(bits & 0b00000001? 10.f: 0.f);
		outputs[OUT2_OUTPUT].setVoltage(bits & 0b00000010? 10.f: 0.f);
		outputs[OUT3_OUTPUT].setVoltage(bits & 0b00000100? 10.f: 0.f);
		outputs[OUT4_OUTPUT].setVoltage(bits & 0b00001000? 10.f: 0.f);
		outputs[OUT5_OUTPUT].setVoltage(bits & 0b00010000? 10.f: 0.f);
		outputs[OUT6_OUTPUT].setVoltage(bits & 0b00100000? 10.f: 0.f);
		outputs[OUT7_OUTPUT].setVoltage(bits & 0b01000000? 10.f: 0.f);
		outputs[OUT8_OUTPUT].setVoltage(signal<0.f? 10.f: 0.f);
	}
};


struct ADCWidget : ModuleWidget {
	ADCWidget(ADC* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/ADC.svg")));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 10.16)), module, ADC::SIGNAL_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 10.16)), module, ADC::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 25.4)), module, ADC::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 40.64)), module, ADC::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 55.88)), module, ADC::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 71.12)), module, ADC::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 86.36)), module, ADC::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 101.6)), module, ADC::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 116.84)), module, ADC::OUT8_OUTPUT));
	}
};


Model* modelADC = createModel<ADC, ADCWidget>("ADC");
