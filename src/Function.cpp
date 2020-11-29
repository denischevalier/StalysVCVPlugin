#include "plugin.hpp"
#include "Common.hpp"


struct Function : Module {
	enum ParamIds {
		RISE_LEVEL1_PARAM,
		FALL_LEVEL1_PARAM,
		FALL_LEVEL2_PARAM,
		RISE_LEVEL2_PARAM,
		FALL_LEVEL3_PARAM,
		RISE_LEVEL3_PARAM,
		FALL_LEVEL4_PARAM,
		RISE_LEVEL4_PARAM,
		FALL_LEVEL5_PARAM,
		RISE_LEVEL5_PARAM,
		FALL_LEVEL6_PARAM,
		RISE_LEVEL6_PARAM,
		FALL_LEVEL7_PARAM,
		RISE_LEVEL7_PARAM,
		FALL_LEVEL8_PARAM,
		RISE_LEVEL8_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		SIGNAL1_INPUT,
		TRIG1_INPUT,
		RISE1_INPUT,
		FALL1_INPUT,
		SIGNAL2_INPUT,
		TRIG2_INPUT,
		RISE2_INPUT,
		FALL2_INPUT,
		SIGNAL3_INPUT,
		TRIG3_INPUT,
		RISE3_INPUT,
		FALL3_INPUT,
		SIGNAL4_INPUT,
		TRIG4_INPUT,
		RISE4_INPUT,
		FALL4_INPUT,
		SIGNAL5_INPUT,
		TRIG5_INPUT,
		RISE5_INPUT,
		FALL5_INPUT,
		SIGNAL6_INPUT,
		TRIG6_INPUT,
		RISE6_INPUT,
		FALL6_INPUT,
		SIGNAL7_INPUT,
		TRIG7_INPUT,
		RISE7_INPUT,
		FALL7_INPUT,
		SIGNAL8_INPUT,
		TRIG8_INPUT,
		RISE8_INPUT,
		FALL8_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1_OUTPUT,
		RISE_GATE1_OUTPUT,
		FALL_GATE1_OUTPUT,
		EOC1_OUTPUT,
		OUT2_OUTPUT,
		FALL_GATE2_OUTPUT,
		EOC2_OUTPUT,
		RISE_GATE2_OUTPUT,
		OUT3_OUTPUT,
		FALL_GATE3_OUTPUT,
		EOC3_OUTPUT,
		RISE_GATE3_OUTPUT,
		OUT4_OUTPUT,
		FALL_GATE4_OUTPUT,
		EOC4_OUTPUT,
		RISE_GATE4_OUTPUT,
		OUT5_OUTPUT,
		FALL_GATE5_OUTPUT,
		EOC5_OUTPUT,
		RISE_GATE5_OUTPUT,
		OUT6_OUTPUT,
		FALL_GATE6_OUTPUT,
		EOC6_OUTPUT,
		RISE_GATE6_OUTPUT,
		OUT7_OUTPUT,
		FALL_GATE7_OUTPUT,
		EOC7_OUTPUT,
		RISE_GATE7_OUTPUT,
		OUT8_OUTPUT,
		FALL_GATE8_OUTPUT,
		EOC8_OUTPUT,
		RISE_GATE8_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	Function() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(FALL_LEVEL1_PARAM, 0.f, 1.f, 0.f, "Fall");
		configParam(RISE_LEVEL1_PARAM, 0.f, 1.f, 0.f, "Rise");
		configParam(FALL_LEVEL2_PARAM, 0.f, 1.f, 0.f, "Fall");
		configParam(RISE_LEVEL2_PARAM, 0.f, 1.f, 0.f, "Rise");
		configParam(FALL_LEVEL3_PARAM, 0.f, 1.f, 0.f, "Fall");
		configParam(RISE_LEVEL3_PARAM, 0.f, 1.f, 0.f, "Rise");
		configParam(FALL_LEVEL4_PARAM, 0.f, 1.f, 0.f, "Fall");
		configParam(RISE_LEVEL4_PARAM, 0.f, 1.f, 0.f, "Rise");
		configParam(FALL_LEVEL5_PARAM, 0.f, 1.f, 0.f, "Fall");
		configParam(RISE_LEVEL5_PARAM, 0.f, 1.f, 0.f, "Rise");
		configParam(FALL_LEVEL6_PARAM, 0.f, 1.f, 0.f, "Fall");
		configParam(RISE_LEVEL6_PARAM, 0.f, 1.f, 0.f, "Rise");
		configParam(FALL_LEVEL7_PARAM, 0.f, 1.f, 0.f, "Fall");
		configParam(RISE_LEVEL7_PARAM, 0.f, 1.f, 0.f, "Rise");
		configParam(FALL_LEVEL8_PARAM, 0.f, 1.f, 0.f, "Fall");
		configParam(RISE_LEVEL8_PARAM, 0.f, 1.f, 0.f, "Rise");
	}

	float out[8] = {0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f};
	bool gate[8] = {false,false,false,false,false,false,false,false};
	bool eoc[8] = {true,true,true,true,true,true,true,true};
	rack::dsp::SchmittTrigger trigger[8];

	void process(const ProcessArgs& args) override {
		const float minTime = 1e-2f;
		const float maxTime = 1e5f;

		const bool trig[8] = {
			trigger[0].process(inputs[TRIG1_INPUT].getVoltage()),
			trigger[1].process(inputs[TRIG2_INPUT].getVoltage()),
			trigger[2].process(inputs[TRIG3_INPUT].getVoltage()),
			trigger[3].process(inputs[TRIG4_INPUT].getVoltage()),
			trigger[4].process(inputs[TRIG5_INPUT].getVoltage()),
			trigger[5].process(inputs[TRIG6_INPUT].getVoltage()),
			trigger[6].process(inputs[TRIG7_INPUT].getVoltage()),
			trigger[7].process(inputs[TRIG8_INPUT].getVoltage())
		};

		const float signal[8] = {
			inputs[SIGNAL1_INPUT].getVoltage(),
			inputs[SIGNAL2_INPUT].getVoltage(),
			inputs[SIGNAL3_INPUT].getVoltage(),
			inputs[SIGNAL4_INPUT].getVoltage(),
			inputs[SIGNAL5_INPUT].getVoltage(),
			inputs[SIGNAL6_INPUT].getVoltage(),
			inputs[SIGNAL7_INPUT].getVoltage(),
			inputs[SIGNAL8_INPUT].getVoltage()
		};

		const float riseCV[8] = {
			inputs[RISE1_INPUT].getVoltage()/10.f + params[RISE_LEVEL1_PARAM].getValue(),
			inputs[RISE2_INPUT].getVoltage()/10.f + params[RISE_LEVEL2_PARAM].getValue(),
			inputs[RISE3_INPUT].getVoltage()/10.f + params[RISE_LEVEL3_PARAM].getValue(),
			inputs[RISE4_INPUT].getVoltage()/10.f + params[RISE_LEVEL4_PARAM].getValue(),
			inputs[RISE5_INPUT].getVoltage()/10.f + params[RISE_LEVEL5_PARAM].getValue(),
			inputs[RISE6_INPUT].getVoltage()/10.f + params[RISE_LEVEL6_PARAM].getValue(),
			inputs[RISE7_INPUT].getVoltage()/10.f + params[RISE_LEVEL7_PARAM].getValue(),
			inputs[RISE8_INPUT].getVoltage()/10.f + params[RISE_LEVEL8_PARAM].getValue()
		};

		const float fallCV[8] = {
			inputs[FALL1_INPUT].getVoltage()/10.f + params[FALL_LEVEL1_PARAM].getValue(),
			inputs[FALL2_INPUT].getVoltage()/10.f + params[FALL_LEVEL2_PARAM].getValue(),
			inputs[FALL3_INPUT].getVoltage()/10.f + params[FALL_LEVEL3_PARAM].getValue(),
			inputs[FALL4_INPUT].getVoltage()/10.f + params[FALL_LEVEL4_PARAM].getValue(),
			inputs[FALL5_INPUT].getVoltage()/10.f + params[FALL_LEVEL5_PARAM].getValue(),
			inputs[FALL6_INPUT].getVoltage()/10.f + params[FALL_LEVEL6_PARAM].getValue(),
			inputs[FALL7_INPUT].getVoltage()/10.f + params[FALL_LEVEL7_PARAM].getValue(),
			inputs[FALL8_INPUT].getVoltage()/10.f + params[FALL_LEVEL8_PARAM].getValue()
		};

		bool rising[8] = {false,false,false,false,false,false,false,false};
		bool falling[8] = {false,false,false,false,false,false,false,false};

		for(int i = 0; i < 8; i++) {
			if (trig[i]) {
				gate[i] = true;
			}
			const float in = gate[i]? 10.f: signal[i];

			if (in > out[i]) {
				eoc[i] = false;
				const float rise = maxTime * std::pow(minTime/maxTime, riseCV[i]);
				out[i] += rise*args.sampleTime;
				rising[i] = out[i] < in;
				if (!rising[i]) {
					out[i] = in;
					gate[i] = false;
				}
			} else if (in < out[i]) {
				const float fall = maxTime * std::pow(minTime/maxTime, fallCV[i]);
				out[i] -= fall*args.sampleTime;
				falling[i] = out[i] > in;
				if (!falling[i]) {
					out[i] = in;
					eoc[i] = true;
				}
			} else {
				gate[i] = false;
			}
		}

		outputs[OUT1_OUTPUT].setVoltage(clipSignal(out[0]));
		outputs[RISE_GATE1_OUTPUT].setVoltage(rising[0]? 10.f: 0.f);
		outputs[FALL_GATE1_OUTPUT].setVoltage(falling[0]? 10.f: 0.f);
		outputs[EOC1_OUTPUT].setVoltage(eoc[0]? 10.f: 0.f);
		outputs[OUT2_OUTPUT].setVoltage(clipSignal(out[1]));
		outputs[RISE_GATE2_OUTPUT].setVoltage(rising[1]? 10.f: 0.f);
		outputs[FALL_GATE2_OUTPUT].setVoltage(falling[1]? 10.f: 0.f);
		outputs[EOC2_OUTPUT].setVoltage(eoc[1]? 10.f: 0.f);
		outputs[OUT3_OUTPUT].setVoltage(clipSignal(out[2]));
		outputs[RISE_GATE3_OUTPUT].setVoltage(rising[2]? 10.f: 0.f);
		outputs[FALL_GATE3_OUTPUT].setVoltage(falling[2]? 10.f: 0.f);
		outputs[EOC3_OUTPUT].setVoltage(eoc[2]? 10.f: 0.f);
		outputs[OUT4_OUTPUT].setVoltage(clipSignal(out[3]));
		outputs[RISE_GATE4_OUTPUT].setVoltage(rising[3]? 10.f: 0.f);
		outputs[FALL_GATE4_OUTPUT].setVoltage(falling[3]? 10.f: 0.f);
		outputs[EOC4_OUTPUT].setVoltage(eoc[3]? 10.f: 0.f);
		outputs[OUT5_OUTPUT].setVoltage(clipSignal(out[4]));
		outputs[RISE_GATE5_OUTPUT].setVoltage(rising[4]? 10.f: 0.f);
		outputs[FALL_GATE5_OUTPUT].setVoltage(falling[4]? 10.f: 0.f);
		outputs[EOC5_OUTPUT].setVoltage(eoc[4]? 10.f: 0.f);
		outputs[OUT6_OUTPUT].setVoltage(clipSignal(out[5]));
		outputs[RISE_GATE6_OUTPUT].setVoltage(rising[5]? 10.f: 0.f);
		outputs[FALL_GATE6_OUTPUT].setVoltage(falling[5]? 10.f: 0.f);
		outputs[EOC6_OUTPUT].setVoltage(eoc[5]? 10.f: 0.f);
		outputs[OUT7_OUTPUT].setVoltage(clipSignal(out[6]));
		outputs[RISE_GATE7_OUTPUT].setVoltage(rising[6]? 10.f: 0.f);
		outputs[FALL_GATE7_OUTPUT].setVoltage(falling[6]? 10.f: 0.f);
		outputs[EOC7_OUTPUT].setVoltage(eoc[6]? 10.f: 0.f);
		outputs[OUT8_OUTPUT].setVoltage(clipSignal(out[7]));
		outputs[RISE_GATE8_OUTPUT].setVoltage(rising[7]? 10.f: 0.f);
		outputs[FALL_GATE8_OUTPUT].setVoltage(falling[7]? 10.f: 0.f);
		outputs[EOC8_OUTPUT].setVoltage(eoc[8]? 10.f: 0.f);
	}
};


struct FunctionWidget : ModuleWidget {
	FunctionWidget(Function* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Function.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.888, 11.985)), module, Function::RISE_LEVEL1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.346, 11.985)), module, Function::FALL_LEVEL1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.346, 26.537)), module, Function::FALL_LEVEL2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.75, 26.566)), module, Function::RISE_LEVEL2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.346, 41.089)), module, Function::FALL_LEVEL3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.75, 41.118)), module, Function::RISE_LEVEL3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.346, 55.749)), module, Function::FALL_LEVEL4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.75, 55.778)), module, Function::RISE_LEVEL4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.346, 70.193)), module, Function::FALL_LEVEL5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.75, 70.222)), module, Function::RISE_LEVEL5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.346, 84.745)), module, Function::FALL_LEVEL6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.75, 84.774)), module, Function::RISE_LEVEL6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.346, 99.297)), module, Function::FALL_LEVEL7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.75, 99.327)), module, Function::RISE_LEVEL7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(58.346, 113.849)), module, Function::FALL_LEVEL8_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(31.75, 113.879)), module, Function::RISE_LEVEL8_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.658, 11.877)), module, Function::SIGNAL1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.292, 11.906)), module, Function::TRIG1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(45.117, 11.985)), module, Function::RISE1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.575, 11.985)), module, Function::FALL1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.521, 26.458)), module, Function::SIGNAL2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.154, 26.488)), module, Function::TRIG2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(45.117, 26.537)), module, Function::RISE2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.575, 26.537)), module, Function::FALL2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.521, 41.01)), module, Function::SIGNAL3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.154, 41.04)), module, Function::TRIG3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(45.117, 41.089)), module, Function::RISE3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.575, 41.089)), module, Function::FALL3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.521, 55.67)), module, Function::SIGNAL4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.154, 55.7)), module, Function::TRIG4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(45.117, 55.749)), module, Function::RISE4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.575, 55.749)), module, Function::FALL4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.521, 70.115)), module, Function::SIGNAL5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.154, 70.144)), module, Function::TRIG5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(45.117, 70.193)), module, Function::RISE5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.575, 70.193)), module, Function::FALL5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.521, 84.667)), module, Function::SIGNAL6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.154, 84.696)), module, Function::TRIG6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(45.117, 84.745)), module, Function::RISE6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.575, 84.745)), module, Function::FALL6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.521, 99.219)), module, Function::SIGNAL7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.154, 99.248)), module, Function::TRIG7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(45.117, 99.297)), module, Function::RISE7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.575, 99.297)), module, Function::FALL7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(18.521, 113.771)), module, Function::SIGNAL8_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.154, 113.8)), module, Function::TRIG8_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(45.117, 113.849)), module, Function::RISE8_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(71.575, 113.849)), module, Function::FALL8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(84.836, 11.696)), module, Function::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(98.065, 11.804)), module, Function::RISE_GATE1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(111.295, 11.804)), module, Function::FALL_GATE1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(124.524, 11.804)), module, Function::EOC1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(84.698, 26.278)), module, Function::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(111.295, 26.356)), module, Function::FALL_GATE2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(124.524, 26.356)), module, Function::EOC2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(97.928, 26.385)), module, Function::RISE_GATE2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(84.698, 40.83)), module, Function::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(111.295, 40.908)), module, Function::FALL_GATE3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(124.524, 40.908)), module, Function::EOC3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(97.928, 40.938)), module, Function::RISE_GATE3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(84.698, 55.49)), module, Function::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(111.295, 55.568)), module, Function::FALL_GATE4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(124.524, 55.568)), module, Function::EOC4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(97.928, 55.597)), module, Function::RISE_GATE4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(84.698, 69.934)), module, Function::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(111.295, 70.012)), module, Function::FALL_GATE5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(124.524, 70.012)), module, Function::EOC5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(97.928, 70.042)), module, Function::RISE_GATE5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(84.698, 84.486)), module, Function::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(111.295, 84.564)), module, Function::FALL_GATE6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(124.524, 84.564)), module, Function::EOC6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(97.928, 84.594)), module, Function::RISE_GATE6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(84.698, 99.038)), module, Function::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(111.295, 99.117)), module, Function::FALL_GATE7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(124.524, 99.117)), module, Function::EOC7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(97.928, 99.146)), module, Function::RISE_GATE7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(84.698, 113.59)), module, Function::OUT8_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(111.295, 113.669)), module, Function::FALL_GATE8_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(124.524, 113.669)), module, Function::EOC8_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(97.928, 113.698)), module, Function::RISE_GATE8_OUTPUT));
	}
};


Model* modelFunction = createModel<Function, FunctionWidget>("Function");
