#include "plugin.hpp"


struct PosNegRectifier : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		SIGNAL1_INPUT,
		SIGNAL2_INPUT,
		SIGNAL3_INPUT,
		SIGNAL4_INPUT,
		SIGNAL5_INPUT,
		SIGNAL6_INPUT,
		SIGNAL7_INPUT,
		SIGNAL8_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		POS1_OUTPUT,
		NEG1_OUTPUT,
		POS2_OUTPUT,
		NEG2_OUTPUT,
		POS3_OUTPUT,
		NEG3_OUTPUT,
		POS4_OUTPUT,
		NEG4_OUTPUT,
		POS5_OUTPUT,
		NEG5_OUTPUT,
		POS6_OUTPUT,
		NEG6_OUTPUT,
		POS7_OUTPUT,
		NEG7_OUTPUT,
		POS8_OUTPUT,
		NEG8_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	PosNegRectifier() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs& args) override {
		const float ins[8] = {
			inputs[SIGNAL1_INPUT].getVoltage(),
			inputs[SIGNAL2_INPUT].getVoltage(),
			inputs[SIGNAL3_INPUT].getVoltage(),
			inputs[SIGNAL4_INPUT].getVoltage(),
			inputs[SIGNAL5_INPUT].getVoltage(),
			inputs[SIGNAL6_INPUT].getVoltage(),
			inputs[SIGNAL7_INPUT].getVoltage(),
			inputs[SIGNAL8_INPUT].getVoltage()
		};

		ins[0]>0.f? outputs[POS1_OUTPUT].setVoltage(ins[0]): outputs[NEG1_OUTPUT].setVoltage(ins[0]);
		ins[1]>0.f? outputs[POS2_OUTPUT].setVoltage(ins[1]): outputs[NEG2_OUTPUT].setVoltage(ins[1]);
		ins[2]>0.f? outputs[POS3_OUTPUT].setVoltage(ins[2]): outputs[NEG3_OUTPUT].setVoltage(ins[2]);
		ins[3]>0.f? outputs[POS4_OUTPUT].setVoltage(ins[3]): outputs[NEG4_OUTPUT].setVoltage(ins[3]);
		ins[4]>0.f? outputs[POS5_OUTPUT].setVoltage(ins[4]): outputs[NEG5_OUTPUT].setVoltage(ins[4]);
		ins[5]>0.f? outputs[POS6_OUTPUT].setVoltage(ins[5]): outputs[NEG6_OUTPUT].setVoltage(ins[5]);
		ins[6]>0.f? outputs[POS7_OUTPUT].setVoltage(ins[6]): outputs[NEG7_OUTPUT].setVoltage(ins[6]);
		ins[7]>0.f? outputs[POS8_OUTPUT].setVoltage(ins[7]): outputs[NEG8_OUTPUT].setVoltage(ins[7]);
	}
};


struct PosNegRectifierWidget : ModuleWidget {
	PosNegRectifierWidget(PosNegRectifier* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/PosNegRectifier.svg")));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 10.16)), module, PosNegRectifier::SIGNAL1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 25.4)), module, PosNegRectifier::SIGNAL2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 40.64)), module, PosNegRectifier::SIGNAL3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 55.88)), module, PosNegRectifier::SIGNAL4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 71.12)), module, PosNegRectifier::SIGNAL5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 86.36)), module, PosNegRectifier::SIGNAL6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 101.6)), module, PosNegRectifier::SIGNAL7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.62, 116.84)), module, PosNegRectifier::SIGNAL8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 10.16)), module, PosNegRectifier::POS1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(38.1, 10.16)), module, PosNegRectifier::NEG1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 25.4)), module, PosNegRectifier::POS2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(38.1, 25.4)), module, PosNegRectifier::NEG2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 40.64)), module, PosNegRectifier::POS3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(38.1, 40.64)), module, PosNegRectifier::NEG3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 55.88)), module, PosNegRectifier::POS4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(38.1, 55.88)), module, PosNegRectifier::NEG4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 71.12)), module, PosNegRectifier::POS5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(38.1, 71.12)), module, PosNegRectifier::NEG5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 86.36)), module, PosNegRectifier::POS6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(38.1, 86.36)), module, PosNegRectifier::NEG6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 101.6)), module, PosNegRectifier::POS7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(38.1, 101.6)), module, PosNegRectifier::NEG7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.86, 116.84)), module, PosNegRectifier::POS8_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(38.1, 116.84)), module, PosNegRectifier::NEG8_OUTPUT));
	}
};


Model* modelPosNegRectifier = createModel<PosNegRectifier, PosNegRectifierWidget>("PosNegRectifier");
