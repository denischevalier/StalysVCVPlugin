#include "plugin.hpp"
#include "Common.hpp"


struct Clip : Module {
	enum ParamIds {
		RATIO_LEVEL1_PARAM,
		RATIO_LEVEL2_PARAM,
		RATIO_LEVEL3_PARAM,
		RATIO_LEVEL4_PARAM,
		RATIO_LEVEL5_PARAM,
		RATIO_LEVEL6_PARAM,
		RATIO_LEVEL7_PARAM,
		RATIO_LEVEL8_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		IN1_INPUT,
		RATIO1_INPUT,
		IN2_INPUT,
		RATIO2_INPUT,
		IN3_INPUT,
		RATIO3_INPUT,
		IN4_INPUT,
		RATIO4_INPUT,
		IN5_INPUT,
		RATIO5_INPUT,
		IN6_INPUT,
		RATIO6_INPUT,
		IN7_INPUT,
		RATIO7_INPUT,
		IN8_INPUT,
		RATIO8_INPUT,
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

	Clip() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(RATIO_LEVEL1_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
		configParam(RATIO_LEVEL2_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
		configParam(RATIO_LEVEL3_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
		configParam(RATIO_LEVEL4_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
		configParam(RATIO_LEVEL5_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
		configParam(RATIO_LEVEL6_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
		configParam(RATIO_LEVEL7_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
		configParam(RATIO_LEVEL8_PARAM, -2.f, 2.f, 0.14925373313f, "Clip level");
	}

	void process(const ProcessArgs& args) override {
		outputs[OUT1_OUTPUT].setVoltage(rack::math::clamp(clipSignal(inputs[IN1_INPUT].getVoltage(), inputs[RATIO1_INPUT].isConnected()?
					(inputs[RATIO1_INPUT].getVoltage()/10.f)*params[RATIO_LEVEL1_PARAM].getValue():
					params[RATIO_LEVEL1_PARAM].getValue()), -10.f, 10.f));
		outputs[OUT2_OUTPUT].setVoltage(rack::math::clamp(clipSignal(inputs[IN2_INPUT].getVoltage(), inputs[RATIO2_INPUT].isConnected()?
					(inputs[RATIO2_INPUT].getVoltage()/10.f)*params[RATIO_LEVEL2_PARAM].getValue():
					params[RATIO_LEVEL2_PARAM].getValue()), -10.f, 10.f));
		outputs[OUT3_OUTPUT].setVoltage(rack::math::clamp(clipSignal(inputs[IN3_INPUT].getVoltage(), inputs[RATIO3_INPUT].isConnected()?
					(inputs[RATIO3_INPUT].getVoltage()/10.f)*params[RATIO_LEVEL3_PARAM].getValue():
					params[RATIO_LEVEL3_PARAM].getValue()), -10.f, 10.f));
		outputs[OUT4_OUTPUT].setVoltage(rack::math::clamp(clipSignal(inputs[IN4_INPUT].getVoltage(), inputs[RATIO4_INPUT].isConnected()?
					(inputs[RATIO4_INPUT].getVoltage()/10.f)*params[RATIO_LEVEL4_PARAM].getValue():
					params[RATIO_LEVEL4_PARAM].getValue()), -10.f, 10.f));
		outputs[OUT5_OUTPUT].setVoltage(rack::math::clamp(clipSignal(inputs[IN5_INPUT].getVoltage(), inputs[RATIO5_INPUT].isConnected()?
					(inputs[RATIO5_INPUT].getVoltage()/10.f)*params[RATIO_LEVEL5_PARAM].getValue():
					params[RATIO_LEVEL5_PARAM].getValue()), -10.f, 10.f));
		outputs[OUT6_OUTPUT].setVoltage(rack::math::clamp(clipSignal(inputs[IN6_INPUT].getVoltage(), inputs[RATIO6_INPUT].isConnected()?
					(inputs[RATIO6_INPUT].getVoltage()/10.f)*params[RATIO_LEVEL6_PARAM].getValue():
					params[RATIO_LEVEL6_PARAM].getValue()), -10.f, 10.f));
		outputs[OUT7_OUTPUT].setVoltage(rack::math::clamp(clipSignal(inputs[IN7_INPUT].getVoltage(), inputs[RATIO7_INPUT].isConnected()?
					(inputs[RATIO7_INPUT].getVoltage()/10.f)*params[RATIO_LEVEL7_PARAM].getValue():
					params[RATIO_LEVEL7_PARAM].getValue()), -10.f, 10.f));
		outputs[OUT8_OUTPUT].setVoltage(rack::math::clamp(clipSignal(inputs[IN8_INPUT].getVoltage(), inputs[RATIO8_INPUT].isConnected()?
					(inputs[RATIO8_INPUT].getVoltage()/10.f)*params[RATIO_LEVEL8_PARAM].getValue():
					params[RATIO_LEVEL8_PARAM].getValue()), -10.f, 10.f));
	}
};


struct ClipWidget : ModuleWidget {
	ClipWidget(Clip* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Clip.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 12.171)), module, Clip::RATIO_LEVEL1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 26.723)), module, Clip::RATIO_LEVEL2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 41.275)), module, Clip::RATIO_LEVEL3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 55.935)), module, Clip::RATIO_LEVEL4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 70.379)), module, Clip::RATIO_LEVEL5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 84.931)), module, Clip::RATIO_LEVEL6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 99.483)), module, Clip::RATIO_LEVEL7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(22.49, 114.035)), module, Clip::RATIO_LEVEL8_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 12.171)), module, Clip::IN1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 12.171)), module, Clip::RATIO1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 26.723)), module, Clip::IN2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 26.723)), module, Clip::RATIO2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 41.275)), module, Clip::IN3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 41.275)), module, Clip::RATIO3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 55.935)), module, Clip::IN4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 55.935)), module, Clip::RATIO4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 70.379)), module, Clip::IN5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 70.379)), module, Clip::RATIO5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 84.931)), module, Clip::IN6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 84.931)), module, Clip::RATIO6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 99.483)), module, Clip::IN7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 99.483)), module, Clip::RATIO7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9.26, 114.035)), module, Clip::IN8_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.719, 114.035)), module, Clip::RATIO8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 12.171)), module, Clip::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 26.723)), module, Clip::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 41.275)), module, Clip::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 55.935)), module, Clip::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 70.379)), module, Clip::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 84.931)), module, Clip::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 99.483)), module, Clip::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.948, 114.035)), module, Clip::OUT8_OUTPUT));
	}
};


Model* modelClip = createModel<Clip, ClipWidget>("Clip");
