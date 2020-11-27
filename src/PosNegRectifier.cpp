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

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 12.014)), module, PosNegRectifier::SIGNAL1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 26.566)), module, PosNegRectifier::SIGNAL2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 41.118)), module, PosNegRectifier::SIGNAL3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 55.778)), module, PosNegRectifier::SIGNAL4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 70.222)), module, PosNegRectifier::SIGNAL5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 84.774)), module, PosNegRectifier::SIGNAL6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 99.327)), module, PosNegRectifier::SIGNAL7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.938, 113.879)), module, PosNegRectifier::SIGNAL8_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 11.906)), module, PosNegRectifier::POS1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(39.688, 12.014)), module, PosNegRectifier::NEG1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 26.458)), module, PosNegRectifier::POS2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(39.688, 26.566)), module, PosNegRectifier::NEG2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 41.01)), module, PosNegRectifier::POS3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(39.688, 41.118)), module, PosNegRectifier::NEG3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 55.67)), module, PosNegRectifier::POS4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(39.688, 55.778)), module, PosNegRectifier::NEG4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 70.115)), module, PosNegRectifier::POS5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(39.688, 70.222)), module, PosNegRectifier::NEG5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 84.667)), module, PosNegRectifier::POS6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(39.688, 84.774)), module, PosNegRectifier::NEG6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 99.219)), module, PosNegRectifier::POS7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(39.688, 99.327)), module, PosNegRectifier::NEG7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.49, 113.771)), module, PosNegRectifier::POS8_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(39.688, 113.879)), module, PosNegRectifier::NEG8_OUTPUT));
	}
};


Model* modelPosNegRectifier = createModel<PosNegRectifier, PosNegRectifierWidget>("PosNegRectifier");
