#include "plugin.hpp"


struct VCSampleAndDelay : Module {
	enum ParamIds {
		STEPS_LEVEL1_PARAM,
		STEPS_LEVEL2_PARAM,
		STEPS_LEVEL3_PARAM,
		STEPS_LEVEL4_PARAM,
		STEPS_LEVEL5_PARAM,
		STEPS_LEVEL6_PARAM,
		STEPS_LEVEL7_PARAM,
		STEPS_LEVEL8_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		STEPS1_INPUT,
		CLOCK1_INPUT,
		SIGNAL1_INPUT,
		CLOCK2_INPUT,
		SIGNAL2_INPUT,
		STEPS2_INPUT,
		CLOCK3_INPUT,
		SIGNAL3_INPUT,
		STEPS3_INPUT,
		CLOCK4_INPUT,
		SIGNAL4_INPUT,
		STEPS4_INPUT,
		CLOCK5_INPUT,
		SIGNAL5_INPUT,
		STEPS5_INPUT,
		CLOCK6_INPUT,
		SIGNAL6_INPUT,
		STEPS6_INPUT,
		CLOCK7_INPUT,
		SIGNAL7_INPUT,
		STEPS7_INPUT,
		CLOCK8_INPUT,
		SIGNAL8_INPUT,
		STEPS8_INPUT,
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

	VCSampleAndDelay() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(STEPS_LEVEL1_PARAM, 1.f, 10.f, 1.f, "Steps");
		configParam(STEPS_LEVEL2_PARAM, 1.f, 10.f, 1.f, "Steps");
		configParam(STEPS_LEVEL3_PARAM, 1.f, 10.f, 1.f, "Steps");
		configParam(STEPS_LEVEL4_PARAM, 1.f, 10.f, 1.f, "Steps");
		configParam(STEPS_LEVEL5_PARAM, 1.f, 10.f, 1.f, "Steps");
		configParam(STEPS_LEVEL6_PARAM, 1.f, 10.f, 1.f, "Steps");
		configParam(STEPS_LEVEL7_PARAM, 1.f, 10.f, 1.f, "Steps");
		configParam(STEPS_LEVEL8_PARAM, 1.f, 10.f, 1.f, "Steps");
	}

	float counters[8] = {0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f};
	float values[8] = {0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f};
	rack::dsp::SchmittTrigger trig1;
	rack::dsp::SchmittTrigger trig2;
	rack::dsp::SchmittTrigger trig3;
	rack::dsp::SchmittTrigger trig4;
	rack::dsp::SchmittTrigger trig5;
	rack::dsp::SchmittTrigger trig6;
	rack::dsp::SchmittTrigger trig7;
	rack::dsp::SchmittTrigger trig8;

	void process(const ProcessArgs& args) override {
		const float steps[8] = {
			rack::math::clamp(inputs[STEPS1_INPUT].getNormalVoltage(params[STEPS_LEVEL1_PARAM].getValue()), 1.f, 10.f),
			rack::math::clamp(inputs[STEPS2_INPUT].getNormalVoltage(params[STEPS_LEVEL2_PARAM].getValue()), 1.f, 10.f),
			rack::math::clamp(inputs[STEPS3_INPUT].getNormalVoltage(params[STEPS_LEVEL3_PARAM].getValue()), 1.f, 10.f),
			rack::math::clamp(inputs[STEPS4_INPUT].getNormalVoltage(params[STEPS_LEVEL4_PARAM].getValue()), 1.f, 10.f),
			rack::math::clamp(inputs[STEPS5_INPUT].getNormalVoltage(params[STEPS_LEVEL5_PARAM].getValue()), 1.f, 10.f),
			rack::math::clamp(inputs[STEPS6_INPUT].getNormalVoltage(params[STEPS_LEVEL6_PARAM].getValue()), 1.f, 10.f),
			rack::math::clamp(inputs[STEPS7_INPUT].getNormalVoltage(params[STEPS_LEVEL7_PARAM].getValue()), 1.f, 10.f),
			rack::math::clamp(inputs[STEPS8_INPUT].getNormalVoltage(params[STEPS_LEVEL8_PARAM].getValue()), 1.f, 10.f),
		};

		if (trig1.process(inputs[CLOCK1_INPUT].getVoltage())) {
			if (counters[0] < steps[0]) {
				counters[0]++;
			} else {
				counters[0] = 0.f;
				values[0] = inputs[SIGNAL1_INPUT].getVoltage();
			}
		}
		if (trig2.process(inputs[CLOCK2_INPUT].getVoltage())) {
			if (counters[1] < steps[1]) {
				counters[1]++;
			} else {
				counters[1] = 0.f;
				values[1] = inputs[SIGNAL2_INPUT].getVoltage();
			}
		}
		if (trig3.process(inputs[CLOCK3_INPUT].getVoltage())) {
			if (counters[2] < steps[2]) {
				counters[2]++;
			} else {
				counters[2] = 0.f;
				values[2] = inputs[SIGNAL3_INPUT].getVoltage();
			}
		}
		if (trig4.process(inputs[CLOCK4_INPUT].getVoltage())) {
			if (counters[3] < steps[3]) {
				counters[3]++;
			} else {
				counters[3] = 0.f;
				values[3] = inputs[SIGNAL4_INPUT].getVoltage();
			}
		}
		if (trig5.process(inputs[CLOCK5_INPUT].getVoltage())) {
			if (counters[4] < steps[4]) {
				counters[4]++;
			} else {
				counters[4] = 0.f;
				values[4] = inputs[SIGNAL5_INPUT].getVoltage();
			}
		}
		if (trig6.process(inputs[CLOCK6_INPUT].getVoltage())) {
			if (counters[5] < steps[5]) {
				counters[5]++;
			} else {
				counters[5] = 0.f;
				values[5] = inputs[SIGNAL6_INPUT].getVoltage();
			}
		}
		if (trig7.process(inputs[CLOCK7_INPUT].getVoltage())) {
			if (counters[6] < steps[6]) {
				counters[6]++;
			} else {
				counters[6] = 0.f;
				values[6] = inputs[SIGNAL7_INPUT].getVoltage();
			}
		}
		if (trig8.process(inputs[CLOCK8_INPUT].getVoltage())) {
			if (counters[7] < steps[7]) {
				counters[7]++;
			} else {
				counters[7] = 0.f;
				values[7] = inputs[SIGNAL8_INPUT].getVoltage();
			}
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


struct VCSampleAndDelayWidget : ModuleWidget {
	VCSampleAndDelayWidget(VCSampleAndDelay* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/VCSampleAndDelay.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(8.075, 11.769)), module, VCSampleAndDelay::STEPS_LEVEL1_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(7.328, 26.33)), module, VCSampleAndDelay::STEPS_LEVEL2_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(7.328, 40.882)), module, VCSampleAndDelay::STEPS_LEVEL3_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(7.328, 55.542)), module, VCSampleAndDelay::STEPS_LEVEL4_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(7.328, 69.986)), module, VCSampleAndDelay::STEPS_LEVEL5_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(7.328, 84.538)), module, VCSampleAndDelay::STEPS_LEVEL6_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(7.328, 99.091)), module, VCSampleAndDelay::STEPS_LEVEL7_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(7.328, 113.643)), module, VCSampleAndDelay::STEPS_LEVEL8_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(21.304, 11.877)), module, VCSampleAndDelay::STEPS1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.534, 11.877)), module, VCSampleAndDelay::CLOCK1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(47.763, 11.877)), module, VCSampleAndDelay::SIGNAL1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.534, 26.429)), module, VCSampleAndDelay::CLOCK2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(47.763, 26.429)), module, VCSampleAndDelay::SIGNAL2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.558, 26.438)), module, VCSampleAndDelay::STEPS2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.534, 40.981)), module, VCSampleAndDelay::CLOCK3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(47.763, 40.981)), module, VCSampleAndDelay::SIGNAL3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.558, 40.99)), module, VCSampleAndDelay::STEPS3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.534, 55.641)), module, VCSampleAndDelay::CLOCK4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(47.763, 55.641)), module, VCSampleAndDelay::SIGNAL4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.558, 55.65)), module, VCSampleAndDelay::STEPS4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.534, 70.085)), module, VCSampleAndDelay::CLOCK5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(47.763, 70.085)), module, VCSampleAndDelay::SIGNAL5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.558, 70.094)), module, VCSampleAndDelay::STEPS5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.534, 84.637)), module, VCSampleAndDelay::CLOCK6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(47.763, 84.637)), module, VCSampleAndDelay::SIGNAL6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.558, 84.646)), module, VCSampleAndDelay::STEPS6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.534, 99.189)), module, VCSampleAndDelay::CLOCK7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(47.763, 99.189)), module, VCSampleAndDelay::SIGNAL7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.558, 99.198)), module, VCSampleAndDelay::STEPS7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(34.534, 113.741)), module, VCSampleAndDelay::CLOCK8_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(47.763, 113.741)), module, VCSampleAndDelay::SIGNAL8_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.558, 113.75)), module, VCSampleAndDelay::STEPS8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(60.992, 11.877)), module, VCSampleAndDelay::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(60.992, 26.429)), module, VCSampleAndDelay::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(60.992, 40.981)), module, VCSampleAndDelay::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(60.992, 55.641)), module, VCSampleAndDelay::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(60.992, 70.085)), module, VCSampleAndDelay::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(60.992, 84.637)), module, VCSampleAndDelay::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(60.992, 99.189)), module, VCSampleAndDelay::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(60.992, 113.741)), module, VCSampleAndDelay::OUT8_OUTPUT));
	}
};


Model* modelVCSampleAndDelay = createModel<VCSampleAndDelay, VCSampleAndDelayWidget>("VCSampleAndDelay");
