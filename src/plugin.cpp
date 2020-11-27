#include "plugin.hpp"


Plugin* pluginInstance;


void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	// p->addModel(modelMyModule);
        p->addModel(modelVCDualNeuron);
        p->addModel(modelComparator);
		p->addModel(modelMultiplier);
		p->addModel(modelSum);
		p->addModel(modelDiff);
		p->addModel(modelNot);
		p->addModel(modelAbs);
		p->addModel(modelASR);
		p->addModel(modelVCSampleAndDelay);
		p->addModel(modelDAC);
		p->addModel(modelADC);
		p->addModel(modelAnd);
		p->addModel(modelMax);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
