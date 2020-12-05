#include "plugin.hpp"


struct ASR : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK_INPUT,
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

	ASR() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	float values[8] = {0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f};
	rack::dsp::SchmittTrigger trig;

	void process(const ProcessArgs& args) override {
		if(trig.process(inputs[CLOCK_INPUT].getVoltage())) {
			values[7] = values[6];
			values[6] = values[5];
			values[5] = values[4];
			values[4] = values[3];
			values[3] = values[2];
			values[2] = values[1];
			values[1] = values[0];
			values[0] = inputs[SIGNAL_INPUT].getVoltage();
		}

		outputs[OUT1_OUTPUT].setVoltage(values[0]);
		outputs[OUT2_OUTPUT].setVoltage(values[1]);
		outputs[OUT3_OUTPUT].setVoltage(values[2]);
		outputs[OUT4_OUTPUT].setVoltage(values[3]);
		outputs[OUT5_OUTPUT].setVoltage(values[4]);
		outputs[OUT6_OUTPUT].setVoltage(values[5]);
		outputs[OUT7_OUTPUT].setVoltage(values[6]);
		outputs[OUT8_OUTPUT].setVoltage(values[7]);
	}
};


struct ASRWidget : ModuleWidget {
	ASRWidget(ASR* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/ASR.svg")));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 10.16)), module, ASR::CLOCK_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 25.4)), module, ASR::SIGNAL_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 10.16)), module, ASR::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 25.4)), module, ASR::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 40.64)), module, ASR::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(23.009, 55.746)), module, ASR::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 71.12)), module, ASR::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 86.36)), module, ASR::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 101.6)), module, ASR::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 116.84)), module, ASR::OUT8_OUTPUT));
	}
};


Model* modelASR = createModel<ASR, ASRWidget>("ASR");
