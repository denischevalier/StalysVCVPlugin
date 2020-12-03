#include "plugin.hpp"


struct CtV : Module {
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

	CtV() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	rack::dsp::SchmittTrigger trigger[8];
	float beats[8] = {0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f};
	float out[8] = {0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f};

	void process(const ProcessArgs& args) override {
		const float in[8] = {
			inputs[IN1_INPUT].getVoltage(),
			inputs[IN2_INPUT].getVoltage(),
			inputs[IN3_INPUT].getVoltage(),
			inputs[IN4_INPUT].getVoltage(),
			inputs[IN5_INPUT].getVoltage(),
			inputs[IN6_INPUT].getVoltage(),
			inputs[IN7_INPUT].getVoltage(),
			inputs[IN8_INPUT].getVoltage()
		};

		for (int i = 0; i < 8; i++) {
			beats[i] += 1.f / args.sampleRate;

			if (trigger[i].process(in[i])) {
				out[i] = rack::math::clamp(std::log2f(0.5f/beats[i]), -10.f, 10.f);
				beats[i] = 0.f;
			}
		}

		outputs[OUT1_OUTPUT].setVoltage(out[0]);
		outputs[OUT2_OUTPUT].setVoltage(out[1]);
		outputs[OUT3_OUTPUT].setVoltage(out[2]);
		outputs[OUT4_OUTPUT].setVoltage(out[3]);
		outputs[OUT5_OUTPUT].setVoltage(out[4]);
		outputs[OUT6_OUTPUT].setVoltage(out[5]);
		outputs[OUT7_OUTPUT].setVoltage(out[6]);
		outputs[OUT8_OUTPUT].setVoltage(out[7]);
	}
};


struct CtVWidget : ModuleWidget {
	CtVWidget(CtV* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CtV.svg")));

		/* addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH))); */

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 10.16)), module, CtV::IN1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 25.4)), module, CtV::IN2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 40.64)), module, CtV::IN3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.514, 55.88)), module, CtV::IN4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.514, 71.12)), module, CtV::IN5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.514, 86.36)), module, CtV::IN6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.514, 101.6)), module, CtV::IN7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.514, 116.84)), module, CtV::IN8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 10.16)), module, CtV::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 25.4)), module, CtV::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 40.64)), module, CtV::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 55.88)), module, CtV::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 71.12)), module, CtV::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 86.36)), module, CtV::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 101.6)), module, CtV::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 116.84)), module, CtV::OUT8_OUTPUT));
	}
};


Model* modelCtV = createModel<CtV, CtVWidget>("CtV");
