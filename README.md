# Stalys

These are original modules designed by [Stalys](https://linktr.ee/stalysmusic).

## Credits

- Neuron original design: [Andrew Fitch](https://www.nonlinearcircuits.com/)
- Code and Panels: [Stalys](https://linktr.ee/stalysmusic)
- Neuron VCV implementation: [Michael Hetrick](https://mhetrick.com/)
- Befaco AxBxC VCV implementation: [Befaco](http://www.befaco.org)

## Modules

### VC Dual Neuron

This module is heavily inspired by [Nonlinear Circuits](https://www.nonlinearcircuits.com/) [Double Neuron](https://github.com/mhetrick/nonlinearcircuits) module.

The module is divided in three parts. On the left are two VC Neurons circuits, and on the right the original Combiner circuit.

Each Neuron is comprised of three lanes: One input, that is multiplied (four-quadrant multiplier). After multiplication, a VC offset is applied. The three inputs are summed and run into a half-wave rectifier and comparator. The comparator's bipolar output is summed with the rectified signal. SENSE adds a positive DC signal to the mix, while RESPONSE affects the magnitude of the comparator's output.

The Combiner circuit consists of two lanes (with four-quadrant multiplication and vc offset), normalized to each Neuron's output. The output of the two lanes runs into several logic modules:

- A Difference Rectifier (DIFFRECT), which is another creative mixer: the two lanes are summed. Then the negative mix is substracted from the positive mix. If the result is positive, it goes out the DIFFRECT+ output, otherwise it goes out the DIFFRECT- output.
- A MAX circuit which outputs the max value out of the two lanes.
- A SUM output which adds the two lanes.
- A MIN output which substracts the bottom lane from the top lane.

This might seem overwhelming, but just experiment: feed it with LFOs, envelopes, sequences, oscillators or even itself and watch the complex waveforms it generates. You can use just some parts of it and it becomes a mixer/ring-modulator/waveshapper/logic module.

