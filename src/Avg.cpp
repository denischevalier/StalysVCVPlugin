#include "Common.hpp"


struct Avg : StalysModule {
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

	Avg() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
	}

	void process(const ProcessArgs& args) override {
		const float in[24] = {
			inputs[IN1_INPUT].getVoltage(),
			inputs[IN2_INPUT].getVoltage(),
			inputs[IN3_INPUT].getVoltage(),
			inputs[IN4_INPUT].getVoltage(),
			inputs[IN5_INPUT].getVoltage(),
			inputs[IN6_INPUT].getVoltage(),
			inputs[IN7_INPUT].getVoltage(),
			inputs[IN8_INPUT].getVoltage(),
			inputs[IN9_INPUT].getVoltage(),
			inputs[IN10_INPUT].getVoltage(),
			inputs[IN11_INPUT].getVoltage(),
			inputs[IN12_INPUT].getVoltage(),
			inputs[IN13_INPUT].getVoltage(),
			inputs[IN14_INPUT].getVoltage(),
			inputs[IN15_INPUT].getVoltage(),
			inputs[IN16_INPUT].getVoltage(),
			inputs[IN17_INPUT].getVoltage(),
			inputs[IN18_INPUT].getVoltage(),
			inputs[IN19_INPUT].getVoltage(),
			inputs[IN20_INPUT].getVoltage(),
			inputs[IN21_INPUT].getVoltage(),
			inputs[IN22_INPUT].getVoltage(),
			inputs[IN23_INPUT].getVoltage(),
			inputs[IN24_INPUT].getVoltage()
		};
		const bool inConnected[24] = {
			inputs[IN1_INPUT].isConnected(),
			inputs[IN2_INPUT].isConnected(),
			inputs[IN3_INPUT].isConnected(),
			inputs[IN4_INPUT].isConnected(),
			inputs[IN5_INPUT].isConnected(),
			inputs[IN6_INPUT].isConnected(),
			inputs[IN7_INPUT].isConnected(),
			inputs[IN8_INPUT].isConnected(),
			inputs[IN9_INPUT].isConnected(),
			inputs[IN10_INPUT].isConnected(),
			inputs[IN11_INPUT].isConnected(),
			inputs[IN12_INPUT].isConnected(),
			inputs[IN13_INPUT].isConnected(),
			inputs[IN14_INPUT].isConnected(),
			inputs[IN15_INPUT].isConnected(),
			inputs[IN16_INPUT].isConnected(),
			inputs[IN17_INPUT].isConnected(),
			inputs[IN18_INPUT].isConnected(),
			inputs[IN19_INPUT].isConnected(),
			inputs[IN20_INPUT].isConnected(),
			inputs[IN21_INPUT].isConnected(),
			inputs[IN22_INPUT].isConnected(),
			inputs[IN23_INPUT].isConnected(),
			inputs[IN24_INPUT].isConnected()
		};
		const bool outConnected[8] = {
			outputs[OUT1_OUTPUT].isConnected(),
			outputs[OUT2_OUTPUT].isConnected(),
			outputs[OUT3_OUTPUT].isConnected(),
			outputs[OUT4_OUTPUT].isConnected(),
			outputs[OUT5_OUTPUT].isConnected(),
			outputs[OUT6_OUTPUT].isConnected(),
			outputs[OUT7_OUTPUT].isConnected(),
			outputs[OUT8_OUTPUT].isConnected()
		};
		float out[8] = {0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f};

		float n = 0.f;
		float sum = 0.f;
		for (int i = 0; i<8; i++)  {
			if (inConnected[i]) {
				n++;
				sum += in[i];
			}
			if (inConnected[i+1]) {
				n++;
				sum += in[i+1];
			}
			if (inConnected[i+2]) {
				n++; sum += in[i+2];
			}
			if (outConnected[i]) {
				out[i] = sum/n;
				sum = n = 0.f;
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


struct AvgWidget : StalysModuleWidget {
	static constexpr int hp = 12;

	AvgWidget(Avg* module) {
		setModule(module);
		box.size = Vec(RACK_GRID_WIDTH * hp, RACK_GRID_HEIGHT);
		setPanel(box.size, "Avg");

		addInput(createInputCentered<port>(mm2px(Vec(7.62, 10.16)), module, Avg::IN1_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(22.86, 10.16)), module, Avg::IN2_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 10.16)), module, Avg::IN3_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 25.4)), module, Avg::IN4_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(22.86, 25.4)), module, Avg::IN5_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 25.4)), module, Avg::IN6_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 40.64)), module, Avg::IN7_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(22.86, 40.64)), module, Avg::IN8_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 40.64)), module, Avg::IN9_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 55.88)), module, Avg::IN10_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(22.86, 55.88)), module, Avg::IN11_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 55.88)), module, Avg::IN12_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 71.12)), module, Avg::IN13_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(22.86, 71.12)), module, Avg::IN14_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 71.12)), module, Avg::IN15_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 86.36)), module, Avg::IN16_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(22.86, 86.36)), module, Avg::IN17_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 86.36)), module, Avg::IN18_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.62, 101.6)), module, Avg::IN19_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(22.86, 101.6)), module, Avg::IN20_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 101.6)), module, Avg::IN21_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(7.922, 116.415)), module, Avg::IN22_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(22.86, 116.84)), module, Avg::IN23_INPUT));
		addInput(createInputCentered<port>(mm2px(Vec(38.1, 116.84)), module, Avg::IN24_INPUT));

		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 10.16)), module, Avg::OUT1_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 25.4)), module, Avg::OUT2_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 40.64)), module, Avg::OUT3_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 55.88)), module, Avg::OUT4_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 71.12)), module, Avg::OUT5_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 86.36)), module, Avg::OUT6_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 101.6)), module, Avg::OUT7_OUTPUT));
		addOutput(createOutputCentered<port>(mm2px(Vec(53.34, 116.84)), module, Avg::OUT8_OUTPUT));
	}
};


Model* modelAvg = createModel<Avg, AvgWidget>("Avg");
