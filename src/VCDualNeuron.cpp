#include "plugin.hpp"

inline float clip(float x) {
	x /= 10.f;
	// Pade approximant of x/(1 + x^12)^(1/12)
	const float limit = 1.16691853009184f;
	x = clamp(x, -limit, limit);
	return ((x + 1.45833f * std::pow(x, 13) + 0.559028f * std::pow(x, 25) + 0.0427035f * std::pow(x, 37))
		/ (1 + 1.54167f * std::pow(x, 12) + 0.642361f * std::pow(x, 24) + 0.0579909f * std::pow(x, 36))) * 10.f;
}

inline float exponentialBipolar80Pade_5_4(float x) {
	return (0.109568f * x + 0.281588f * std::pow(x, 3) + 0.133841f * std::pow(x, 5))
		/ (1 - 0.630374f * std::pow(x, 2) + 0.166271f * std::pow(x, 4));
}


struct VCDualNeuron : Module {
	enum ParamIds {
		// Neuron A inputs
		A_CARRIER_LEVEL_PARAM,
		A_OFFSET_LEVEL_PARAM,
		B_CARRIER_LEVEL_PARAM,
		B_OFFSET_LEVEL_PARAM,
		C_CARRIER_LEVEL_PARAM,
		C_OFFSET_LEVEL_PARAM,

		// Neuron A params
		A_SENSE_LEVEL_PARAM,
		A_RESPONSE_LEVEL_PARAM,

		// Neuron B inputs
		D_CARRIER_LEVEL_PARAM,
		D_OFFSET_LEVEL_PARAM,
		E_CARRIER_LEVEL_PARAM,
		E_OFFSET_LEVEL_PARAM,
		F_CARRIER_LEVEL_PARAM,
		F_OFFSET_LEVEL_PARAM,

		// Neuron B params
		B_SENSE_LEVEL_PARAM,
		B_RESPONSE_LEVEL_PARAM,

		// Combiner inputs
		G_CARRIER_LEVEL_PARAM,
		G_OFFSET_LEVEL_PARAM,
		H_CARRIER_LEVEL_PARAM,
		H_OFFSET_LEVEL_PARAM,

		NUM_PARAMS
	};
	enum InputIds {
		// Neuron A inputs
		A_SIGNAL_INPUT,
		A_CARRIER_INPUT,
		A_OFFSET_INPUT,
		B_SIGNAL_INPUT,
		B_CARRIER_INPUT,
		B_OFFSET_INPUT,
		C_SIGNAL_INPUT,
		C_CARRIER_INPUT,
		C_OFFSET_INPUT,

		// Neuron A params
		A_SENSE_INPUT,
		A_RESPONSE_INPUT,

		// Neuron B inputs
		D_SIGNAL_INPUT,
		D_CARRIER_INPUT,
		D_OFFSET_INPUT,
		E_SIGNAL_INPUT,
		E_CARRIER_INPUT,
		E_OFFSET_INPUT,
		F_SIGNAL_INPUT,
		F_CARRIER_INPUT,
		F_OFFSET_INPUT,

		// Neuron B params
		B_SENSE_INPUT,
		B_RESPONSE_INPUT,

		// Combiner inputs
		G_SIGNAL_INPUT,
		G_CARRIER_INPUT,
		G_OFFSET_INPUT,
		H_SIGNAL_INPUT,
		H_CARRIER_INPUT,
		H_OFFSET_INPUT,

		NUM_INPUTS
	};
	enum OutputIds {
		// Neuron A output
		A_OUTPUT_OUTPUT,

		// Neuron B output
		B_OUTPUT_OUTPUT,

		// Combiner outputs
		DIFFRECT_POS_OUTPUT,
		MAX_OUTPUT,
		SUM_OUTPUT,
		INV_OUTPUT,
		MIN_OUTPUT,
		DIFFRECT_NEG_OUTPUT,

		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	VCDualNeuron() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		// Neuron A inputs
		configParam(A_CARRIER_LEVEL_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(A_OFFSET_LEVEL_PARAM, -1.f, 1.f, 0.f, "Offset level");
		configParam(B_CARRIER_LEVEL_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(B_OFFSET_LEVEL_PARAM, -1.f, 1.f, 0.f, "Offset level");
		configParam(C_CARRIER_LEVEL_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(C_OFFSET_LEVEL_PARAM, -1.f, 1.f, 0.f, "Offset level");

		// Neuron A params
		configParam(A_SENSE_LEVEL_PARAM, 0.f, 5.f, 0.f, "Sense level");
		configParam(A_RESPONSE_LEVEL_PARAM, 1.f, 10.f, 1.f, "Response level");

		// Neuron B inputs
		configParam(D_CARRIER_LEVEL_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(D_OFFSET_LEVEL_PARAM, -1.f, 1.f, 0.f, "Offset level");
		configParam(E_CARRIER_LEVEL_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(E_OFFSET_LEVEL_PARAM, -1.f, 1.f, 0.f, "Offset level");
		configParam(F_CARRIER_LEVEL_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(F_OFFSET_LEVEL_PARAM, -1.f, 1.f, 0.f, "Offset level");

		// Neuron B params
		configParam(B_SENSE_LEVEL_PARAM, 0.f, 5.f, 0.f, "Sense level");
		configParam(B_RESPONSE_LEVEL_PARAM, 1.f, 10.f, 1.f, "Response level");

		// Combiner inputs
		configParam(G_CARRIER_LEVEL_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(G_OFFSET_LEVEL_PARAM, -1.f, 1.f, 0.f, "Offset level");
		configParam(H_CARRIER_LEVEL_PARAM, -1.f, 1.f, 0.f, "Carrier level");
		configParam(H_OFFSET_LEVEL_PARAM, -1.f, 1.f, 0.f, "Offset level");
	}

	void process(const ProcessArgs& args) override {
		// Neuron A
		// Input 1
		float aSignal = inputs[A_SIGNAL_INPUT].getVoltage();
		float aCarrier = inputs[A_CARRIER_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[A_CARRIER_LEVEL_PARAM].getValue());
		float aOffset = inputs[A_OFFSET_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[A_OFFSET_LEVEL_PARAM].getValue());
		float aInput = aSignal * aCarrier/5.f + aOffset;

		// Input 2
		float bSignal = inputs[B_SIGNAL_INPUT].getVoltage();
		float bCarrier = inputs[B_CARRIER_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[B_CARRIER_LEVEL_PARAM].getValue());
		float bOffset = inputs[B_OFFSET_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[B_OFFSET_LEVEL_PARAM].getValue());
		float bInput = bSignal * bCarrier/5.f + bOffset;

		// Input 3
		float cSignal = inputs[C_SIGNAL_INPUT].getVoltage();
		float cCarrier = inputs[C_CARRIER_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[C_CARRIER_LEVEL_PARAM].getValue());
		float cOffset = inputs[C_OFFSET_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[C_OFFSET_LEVEL_PARAM].getValue());
		float cInput = cSignal * cCarrier/5.f + cOffset;

		// Params
		float aSense = params[A_SENSE_LEVEL_PARAM].getValue();
		if (inputs[A_SENSE_INPUT].isConnected()) {
			aSense = rack::math::clamp(inputs[A_SENSE_INPUT].getVoltage() * aSense, 0.f, 5.f);
		}
		float aResponse = params[A_RESPONSE_LEVEL_PARAM].getValue();
		if (inputs[A_RESPONSE_INPUT].isConnected()) {
			aResponse = rack::math::clamp(inputs[A_RESPONSE_INPUT].getVoltage() * aResponse, 1.f, 10.f);
		}

		// Output
		float aRectifiedInput = rack::math::clamp((aInput+bInput+cInput)/3+aSense, 0.f, 10.f);
		float aComparatorOutput = aRectifiedInput > 0.f? aResponse: aResponse * -1.f;
		float aOutput = aRectifiedInput - aComparatorOutput;

		// Neuron B
		// Input 1
		float dSignal = inputs[D_SIGNAL_INPUT].getVoltage();
		float dCarrier = inputs[D_CARRIER_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[D_CARRIER_LEVEL_PARAM].getValue());
		float dOffset = inputs[D_OFFSET_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[D_OFFSET_LEVEL_PARAM].getValue());
		float dInput = dSignal * dCarrier/5.f + dOffset;

		// Input 2
		float eSignal = inputs[E_SIGNAL_INPUT].getVoltage();
		float eCarrier = inputs[E_CARRIER_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[E_CARRIER_LEVEL_PARAM].getValue());
		float eOffset = inputs[E_OFFSET_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[E_OFFSET_LEVEL_PARAM].getValue());
		float eInput = eSignal * eCarrier/5.f + eOffset;

		// Input 3
		float fSignal = inputs[F_SIGNAL_INPUT].getVoltage();
		float fCarrier = inputs[F_CARRIER_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[F_CARRIER_LEVEL_PARAM].getValue());
		float fOffset = inputs[F_OFFSET_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[F_OFFSET_LEVEL_PARAM].getValue());
		float fInput = fSignal * fCarrier/5.f + fOffset;

		// Params
		float bSense = params[B_SENSE_LEVEL_PARAM].getValue();
		if (inputs[B_SENSE_INPUT].isConnected()) {
			bSense = rack::math::clamp(inputs[B_SENSE_INPUT].getVoltage() * bSense, 0.f, 5.f);
		}
		float bResponse = params[B_RESPONSE_LEVEL_PARAM].getValue();
		if (inputs[B_RESPONSE_INPUT].isConnected()) {
			bResponse = rack::math::clamp(inputs[B_RESPONSE_INPUT].getVoltage() * bResponse, 1.f, 10.f);
		}

		// Output
		float bRectifiedInput = rack::math::clamp((dInput+eInput+fInput)/3+bSense, 0.f, 10.f);
		float bComparatorOutput = bRectifiedInput > 0.f? bResponse: bResponse * -1.f;
		float bOutput = bRectifiedInput - bComparatorOutput;

		// Combiner
		// Input 1
		float gSignal = inputs[G_SIGNAL_INPUT].getNormalVoltage(aOutput);
		float gCarrier = inputs[G_CARRIER_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[G_CARRIER_LEVEL_PARAM].getValue());
		float gOffset = inputs[G_OFFSET_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[G_OFFSET_LEVEL_PARAM].getValue());
		float gInput = gSignal * gCarrier/5.f + gOffset;

		// Input 2
		float hSignal = inputs[H_SIGNAL_INPUT].getNormalVoltage(bOutput);
		float hCarrier = inputs[H_CARRIER_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[H_CARRIER_LEVEL_PARAM].getValue());
		float hOffset = inputs[H_OFFSET_INPUT].getNormalVoltage(5.f) * 2.f*exponentialBipolar80Pade_5_4(params[H_OFFSET_LEVEL_PARAM].getValue());
		float hInput = hSignal * hCarrier/5.f + hOffset;

		// Outputs
		float diff = rack::math::clamp(gInput - hInput, -10.f, 10.f);
		float diffrectPos = diff > 0.f? diff: 0.f;
		float diffrectNeg = diff < 0.f? diff: 0.f;
		float max = gInput >= hInput? gInput: hInput;
		float min = gInput >= hInput? hInput: gInput;
		float sum = gInput + hInput;
		float inv = gInput - hInput;

		// Set outpus
		// Neuron A
		outputs[A_OUTPUT_OUTPUT].setVoltage(clip(aOutput));

		// Neuron B
		outputs[B_OUTPUT_OUTPUT].setVoltage(clip(bOutput));
		
		// Combiner
		outputs[DIFFRECT_POS_OUTPUT].setVoltage(clip(diffrectPos));
		outputs[DIFFRECT_NEG_OUTPUT].setVoltage(clip(diffrectNeg));
		outputs[MAX_OUTPUT].setVoltage(clip(max));
		outputs[MIN_OUTPUT].setVoltage(clip(min));
		outputs[SUM_OUTPUT].setVoltage(clip(sum));
		outputs[INV_OUTPUT].setVoltage(clip(inv));
	}
};

struct VCDualNeuronWidget : ModuleWidget {
	VCDualNeuronWidget(VCDualNeuron* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/VCDualNeuron.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(29.104, 18.521)), module, VCDualNeuron::A_CARRIER_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(60.854, 18.521)), module, VCDualNeuron::A_OFFSET_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(92.604, 21.167)), module, VCDualNeuron::A_SENSE_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(29.104, 34.396)), module, VCDualNeuron::B_CARRIER_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(60.854, 34.396)), module, VCDualNeuron::B_OFFSET_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(134.805, 34.528)), module, VCDualNeuron::G_CARRIER_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(166.555, 34.528)), module, VCDualNeuron::G_OFFSET_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(92.604, 47.625)), module, VCDualNeuron::A_RESPONSE_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(29.104, 50.271)), module, VCDualNeuron::C_CARRIER_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(60.854, 50.271)), module, VCDualNeuron::C_OFFSET_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(29.104, 76.729)), module, VCDualNeuron::D_CARRIER_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(60.854, 76.729)), module, VCDualNeuron::D_OFFSET_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(92.548, 79.503)), module, VCDualNeuron::B_SENSE_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(29.104, 92.604)), module, VCDualNeuron::E_CARRIER_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(60.854, 92.604)), module, VCDualNeuron::E_OFFSET_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(134.805, 92.736)), module, VCDualNeuron::H_CARRIER_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(166.555, 92.737)), module, VCDualNeuron::H_OFFSET_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(92.548, 105.962)), module, VCDualNeuron::B_RESPONSE_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(29.104, 108.479)), module, VCDualNeuron::F_CARRIER_LEVEL_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(60.854, 108.479)), module, VCDualNeuron::F_OFFSET_LEVEL_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(92.604, 11.906)), module, VCDualNeuron::A_SENSE_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(13.229, 18.521)), module, VCDualNeuron::A_SIGNAL_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(44.979, 18.521)), module, VCDualNeuron::A_CARRIER_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(76.729, 18.521)), module, VCDualNeuron::A_OFFSET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(13.229, 34.396)), module, VCDualNeuron::B_SIGNAL_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(44.979, 34.396)), module, VCDualNeuron::B_CARRIER_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(76.729, 34.396)), module, VCDualNeuron::B_OFFSET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(182.429, 34.528)), module, VCDualNeuron::G_OFFSET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(150.548, 34.66)), module, VCDualNeuron::G_CARRIER_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(119.195, 34.793)), module, VCDualNeuron::G_SIGNAL_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(13.229, 50.271)), module, VCDualNeuron::C_SIGNAL_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(44.979, 50.271)), module, VCDualNeuron::C_CARRIER_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(76.729, 50.271)), module, VCDualNeuron::C_OFFSET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(92.604, 56.885)), module, VCDualNeuron::A_RESPONSE_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(92.548, 70.243)), module, VCDualNeuron::B_SENSE_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(13.229, 76.729)), module, VCDualNeuron::D_SIGNAL_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(44.979, 76.729)), module, VCDualNeuron::D_CARRIER_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(76.729, 76.729)), module, VCDualNeuron::D_OFFSET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(119.195, 92.472)), module, VCDualNeuron::H_SIGNAL_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(13.229, 92.604)), module, VCDualNeuron::E_SIGNAL_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(44.979, 92.604)), module, VCDualNeuron::E_CARRIER_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(76.729, 92.604)), module, VCDualNeuron::E_OFFSET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(150.68, 92.737)), module, VCDualNeuron::H_CARRIER_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(182.429, 92.737)), module, VCDualNeuron::H_OFFSET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(13.229, 108.479)), module, VCDualNeuron::F_SIGNAL_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(44.979, 108.479)), module, VCDualNeuron::F_CARRIER_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(76.729, 108.479)), module, VCDualNeuron::F_OFFSET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(92.548, 115.222)), module, VCDualNeuron::B_RESPONSE_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.082, 23.812)), module, VCDualNeuron::DIFFRECT_POS_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(92.604, 34.396)), module, VCDualNeuron::A_OUTPUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.082, 39.687)), module, VCDualNeuron::MAX_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.082, 55.562)), module, VCDualNeuron::SUM_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.082, 71.437)), module, VCDualNeuron::INV_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.082, 87.312)), module, VCDualNeuron::MIN_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(92.604, 92.604)), module, VCDualNeuron::B_OUTPUT_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(201.083, 103.188)), module, VCDualNeuron::DIFFRECT_NEG_OUTPUT));
	}
};


Model* modelVCDualNeuron = createModel<VCDualNeuron, VCDualNeuronWidget>("VCDualNeuron");
