#include "plugin.hpp"
#include "Common.hpp"


struct Multiplier : Module {
	enum ParamIds {
		CARRIER_LEVEL1_PARAM,
		CARRIER_LEVEL2_PARAM,
		CARRIER_LEVEL3_PARAM,
		CARRIER_LEVEL4_PARAM,
		CARRIER_LEVEL5_PARAM,
		CARRIER_LEVEL6_PARAM,
		CARRIER_LEVEL7_PARAM,
		CARRIER_LEVEL8_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		SIGNAL1_INPUT,
		CARRIER1_INPUT,
		SIGNAL2_INPUT,
		CARRIER2_INPUT,
		SIGNAL3_INPUT,
		CARRIER3_INPUT,
		SIGNAL4_INPUT,
		CARRIER4_INPUT,
		SIGNAL5_INPUT,
		CARRIER5_INPUT,
		SIGNAL6_INPUT,
		CARRIER6_INPUT,
		SIGNAL7_INPUT,
		CARRIER7_INPUT,
		SIGNAL8_INPUT,
		CARRIER8_INPUT,
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

	Multiplier() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(CARRIER_LEVEL1_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(CARRIER_LEVEL2_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(CARRIER_LEVEL3_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(CARRIER_LEVEL4_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(CARRIER_LEVEL5_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(CARRIER_LEVEL6_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(CARRIER_LEVEL7_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(CARRIER_LEVEL8_PARAM, -1.f, 1.f, 0.f, "Carrier level");
	}

	void process(const ProcessArgs& args) override {
		const float results[8] = {
			inputs[SIGNAL1_INPUT].getNormalVoltage(0.f) * inputs[CARRIER1_INPUT].getNormalVoltage(5.f) * 2.f * exponentialBipolar80Pade_5_4(params[CARRIER_LEVEL1_PARAM].getValue()) / 5.f,
			inputs[SIGNAL2_INPUT].getNormalVoltage(0.f) * inputs[CARRIER2_INPUT].getNormalVoltage(5.f) * 2.f * exponentialBipolar80Pade_5_4(params[CARRIER_LEVEL2_PARAM].getValue()) / 5.f,
			inputs[SIGNAL3_INPUT].getNormalVoltage(0.f) * inputs[CARRIER3_INPUT].getNormalVoltage(5.f) * 2.f * exponentialBipolar80Pade_5_4(params[CARRIER_LEVEL3_PARAM].getValue()) / 5.f,
			inputs[SIGNAL4_INPUT].getNormalVoltage(0.f) * inputs[CARRIER4_INPUT].getNormalVoltage(5.f) * 2.f * exponentialBipolar80Pade_5_4(params[CARRIER_LEVEL4_PARAM].getValue()) / 5.f,
			inputs[SIGNAL5_INPUT].getNormalVoltage(0.f) * inputs[CARRIER5_INPUT].getNormalVoltage(5.f) * 2.f * exponentialBipolar80Pade_5_4(params[CARRIER_LEVEL5_PARAM].getValue()) / 5.f,
			inputs[SIGNAL6_INPUT].getNormalVoltage(0.f) * inputs[CARRIER6_INPUT].getNormalVoltage(5.f) * 2.f * exponentialBipolar80Pade_5_4(params[CARRIER_LEVEL6_PARAM].getValue()) / 5.f,
			inputs[SIGNAL7_INPUT].getNormalVoltage(0.f) * inputs[CARRIER7_INPUT].getNormalVoltage(5.f) * 2.f * exponentialBipolar80Pade_5_4(params[CARRIER_LEVEL7_PARAM].getValue()) / 5.f,
			inputs[SIGNAL8_INPUT].getNormalVoltage(0.f) * inputs[CARRIER8_INPUT].getNormalVoltage(5.f) * 2.f * exponentialBipolar80Pade_5_4(params[CARRIER_LEVEL8_PARAM].getValue()) / 5.f,
		};

		const float out1 = results[0];
		const float out2 = outputs[OUT1_OUTPUT].isConnected()? results[1]: results[1]+out1;
		const float out3 = outputs[OUT2_OUTPUT].isConnected()? results[2]: results[2]+out2;
		const float out4 = outputs[OUT3_OUTPUT].isConnected()? results[3]: results[3]+out3;
		const float out5 = outputs[OUT4_OUTPUT].isConnected()? results[4]: results[4]+out4;
		const float out6 = outputs[OUT5_OUTPUT].isConnected()? results[5]: results[5]+out5;
		const float out7 = outputs[OUT6_OUTPUT].isConnected()? results[6]: results[6]+out6;
		const float out8 = outputs[OUT7_OUTPUT].isConnected()? results[7]: results[7]+out7;

		outputs[OUT1_OUTPUT].setVoltage(clip(out1));
		outputs[OUT2_OUTPUT].setVoltage(clip(out2));
		outputs[OUT3_OUTPUT].setVoltage(clip(out3));
		outputs[OUT4_OUTPUT].setVoltage(clip(out4));
		outputs[OUT5_OUTPUT].setVoltage(clip(out5));
		outputs[OUT6_OUTPUT].setVoltage(clip(out6));
		outputs[OUT7_OUTPUT].setVoltage(clip(out7));
		outputs[OUT8_OUTPUT].setVoltage(clip(out8));
	}
};


struct MultiplierWidget : ModuleWidget {
	MultiplierWidget(Multiplier* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Multiplier.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 12.171)), module, Multiplier::CARRIER_LEVEL1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 26.723)), module, Multiplier::CARRIER_LEVEL2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 41.275)), module, Multiplier::CARRIER_LEVEL3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 55.935)), module, Multiplier::CARRIER_LEVEL4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 70.379)), module, Multiplier::CARRIER_LEVEL5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 84.931)), module, Multiplier::CARRIER_LEVEL6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 99.483)), module, Multiplier::CARRIER_LEVEL7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 114.035)), module, Multiplier::CARRIER_LEVEL8_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 12.171)), module, Multiplier::SIGNAL1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 12.171)), module, Multiplier::CARRIER1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 26.723)), module, Multiplier::SIGNAL2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 26.723)), module, Multiplier::CARRIER2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 41.275)), module, Multiplier::SIGNAL3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 41.275)), module, Multiplier::CARRIER3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 55.935)), module, Multiplier::SIGNAL4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 55.935)), module, Multiplier::CARRIER4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 70.379)), module, Multiplier::SIGNAL5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 70.379)), module, Multiplier::CARRIER5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 84.931)), module, Multiplier::SIGNAL6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 84.931)), module, Multiplier::CARRIER6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 99.483)), module, Multiplier::SIGNAL7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 99.483)), module, Multiplier::CARRIER7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 114.035)), module, Multiplier::SIGNAL8_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 114.035)), module, Multiplier::CARRIER8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 12.171)), module, Multiplier::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 26.723)), module, Multiplier::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 41.275)), module, Multiplier::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 55.935)), module, Multiplier::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 70.379)), module, Multiplier::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 84.931)), module, Multiplier::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 99.483)), module, Multiplier::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 114.035)), module, Multiplier::OUT8_OUTPUT));
	}
};


Model* modelMultiplier = createModel<Multiplier, MultiplierWidget>("Multiplier");
