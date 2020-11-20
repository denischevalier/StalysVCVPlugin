# Stalys

## Abstract

This Plugin will contain the modules that I am creating in my study of [cybernetics](https://en.m.wikipedia.org/wiki/Cybernetics) in music.

My goal is to create a [Turing-complete](https://en.m.wikipedia.org/wiki/Turing_completeness) set of instructions for VCV. I would also use it to teach my child about computing and programming :).

My dream is to one day port it to eurorack (but I'd need to learn electronics first 😅).

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
- A DIFF output which substracts the bottom lane from the top lane.
- A MIN circuit which outputs the min value out of the two lanes.

This might seem overwhelming, but just experiment: feed it with LFOs, envelopes, sequences, oscillators or even itself and watch the complex waveforms it generates. You can use just some parts of it and it becomes a mixer/ring-modulator/waveshapper/logic module.

## Planed modules

This list is here for me as a reminder. I might (or might not) implement them in any order.

* 8 bit shift register
* 8 VC CV delay
* 8 S&H
* 8 bit to CV converter (DAC)
* 8 not
* 8 and
* 8 or
* 8 pos/neg rect
* 8 diffrect
* 8 abs
* 8 sum
* 8 diff
* 8 max
* 8 min
* 8 avg
* 8 VC four quadrant multiplier mixer
* 8 VC comparator
* 8 A/B SEL
* clock to V/Oct
* V/Oct to clock
* 8 VC clock divider
* 8 VC CV divider
* CV to 8 bit converter (ACD)
* 8 VC fall (CV + Trig in, VC log to exp, EOC out)
* 8 VC rise (CV + Trig in, VC log to exp, EOC out)
* 8 offset

## Contribute

You can support me in many ways:

* If you want to support me financially, please consider going to [my Patreon](https://www.patreon.com/stalysmusic).
* You can also listen to [my music](https://linktr.ee/stalysmusic).
* If you use my modules in one of your projects (videos, tracks, education, etc.), please send me [an email](mailto:stalysmusic+vcv@gmail.com) for me to check it out. I'll make sure to reference you here.
* You can [create issues](https://github.com/denischevalier/StalysVCVPlugin/issues), improve the [documentation](https://github.com/denischevalier/StalysVCVPlugin/wiki) or create [pull requests](https://github.com/denischevalier/StalysVCVPlugin/pulls) here.
* If you know electronics and are interested in porting one of my modules, please feel free to [contact me](mailto:stalysmusic+vcv@gmail.com).
