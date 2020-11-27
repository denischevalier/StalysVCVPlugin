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

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 11.798)), module, ADC::SIGNAL_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 11.906)), module, ADC::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 26.458)), module, ADC::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 41.01)), module, ADC::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 55.67)), module, ADC::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 70.115)), module, ADC::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 84.667)), module, ADC::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 99.219)), module, ADC::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 113.771)), module, ADC::OUT8_OUTPUT));
	}
};


Model* modelADC = createModel<ADC, ADCWidget>("ADC");
