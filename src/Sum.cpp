#include "plugin.hpp"
#include "Common.hpp"


struct Sum : Module {
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
		IN9_INPUT,
		IN10_INPUT,
		IN11_INPUT,
		IN12_INPUT,
		IN13_INPUT,
		IN14_INPUT,
		IN15_INPUT,
		IN16_INPUT,
		IN17_INPUT,
		IN18_INPUT,
		IN19_INPUT,
		IN20_INPUT,
		IN21_INPUT,
		IN22_INPUT,
		IN23_INPUT,
		IN24_INPUT,
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

	Sum() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs& args) override {
		const float results[8] = {
			inputs[IN1_INPUT].getNormalVoltage(0.f)+inputs[IN2_INPUT].getNormalVoltage(0.f)+inputs[IN3_INPUT].getNormalVoltage(0.f),
			inputs[IN4_INPUT].getNormalVoltage(0.f)+inputs[IN5_INPUT].getNormalVoltage(0.f)+inputs[IN6_INPUT].getNormalVoltage(0.f),
			inputs[IN7_INPUT].getNormalVoltage(0.f)+inputs[IN8_INPUT].getNormalVoltage(0.f)+inputs[IN9_INPUT].getNormalVoltage(0.f),
			inputs[IN10_INPUT].getNormalVoltage(0.f)+inputs[IN11_INPUT].getNormalVoltage(0.f)+inputs[IN12_INPUT].getNormalVoltage(0.f),
			inputs[IN13_INPUT].getNormalVoltage(0.f)+inputs[IN14_INPUT].getNormalVoltage(0.f)+inputs[IN15_INPUT].getNormalVoltage(0.f),
			inputs[IN16_INPUT].getNormalVoltage(0.f)+inputs[IN17_INPUT].getNormalVoltage(0.f)+inputs[IN18_INPUT].getNormalVoltage(0.f),
			inputs[IN19_INPUT].getNormalVoltage(0.f)+inputs[IN20_INPUT].getNormalVoltage(0.f)+inputs[IN21_INPUT].getNormalVoltage(0.f),
			inputs[IN22_INPUT].getNormalVoltage(0.f)+inputs[IN23_INPUT].getNormalVoltage(0.f)+inputs[IN24_INPUT].getNormalVoltage(0.f)
		};

		const float out1 = results[0];
		const float out2 = outputs[OUT1_OUTPUT].isConnected()? results[1]: results[1]+out1;
		const float out3 = outputs[OUT2_OUTPUT].isConnected()? results[2]: results[2]+out2;
		const float out4 = outputs[OUT3_OUTPUT].isConnected()? results[3]: results[3]+out3;
		const float out5 = outputs[OUT4_OUTPUT].isConnected()? results[4]: results[4]+out4;
		const float out6 = outputs[OUT5_OUTPUT].isConnected()? results[5]: results[5]+out5;
		const float out7 = outputs[OUT6_OUTPUT].isConnected()? results[6]: results[6]+out6;
		const float out8 = outputs[OUT7_OUTPUT].isConnected()? results[7]: results[7]+out7;

		outputs[OUT1_OUTPUT].setVoltage(clipSignal(out1));
		outputs[OUT2_OUTPUT].setVoltage(clipSignal(out2));
		outputs[OUT3_OUTPUT].setVoltage(clipSignal(out3));
		outputs[OUT4_OUTPUT].setVoltage(clipSignal(out4));
		outputs[OUT5_OUTPUT].setVoltage(clipSignal(out5));
		outputs[OUT6_OUTPUT].setVoltage(clipSignal(out6));
		outputs[OUT7_OUTPUT].setVoltage(clipSignal(out7));
		outputs[OUT8_OUTPUT].setVoltage(clipSignal(out8));
	}
};


struct SumWidget : ModuleWidget {
	SumWidget(Sum* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Sum.svg")));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 10.16)), module, Sum::IN1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 10.16)), module, Sum::IN2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 10.16)), module, Sum::IN3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 25.4)), module, Sum::IN4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 25.4)), module, Sum::IN5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 25.4)), module, Sum::IN6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 40.64)), module, Sum::IN7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 40.64)), module, Sum::IN8_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 40.64)), module, Sum::IN9_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 55.88)), module, Sum::IN10_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 55.88)), module, Sum::IN11_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 55.88)), module, Sum::IN12_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 71.12)), module, Sum::IN13_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 71.12)), module, Sum::IN14_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 71.12)), module, Sum::IN15_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 86.36)), module, Sum::IN16_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 86.36)), module, Sum::IN17_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 86.36)), module, Sum::IN18_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 101.6)), module, Sum::IN19_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 101.6)), module, Sum::IN20_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 101.6)), module, Sum::IN21_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.922, 116.415)), module, Sum::IN22_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.86, 116.84)), module, Sum::IN23_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(38.1, 116.84)), module, Sum::IN24_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 10.16)), module, Sum::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 25.4)), module, Sum::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 40.64)), module, Sum::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 55.88)), module, Sum::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 71.12)), module, Sum::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 86.36)), module, Sum::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 101.6)), module, Sum::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.34, 116.84)), module, Sum::OUT8_OUTPUT));
	}
};


Model* modelSum = createModel<Sum, SumWidget>("Sum");
