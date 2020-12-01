# Stalys

![All Modules](/img/allmodules.png)

## Abstract

This Plugin will contain the modules that I am creating in my study of [cybernetics](https://en.m.wikipedia.org/wiki/Cybernetics) in music.

My goal is to create a [Turing-complete](https://en.m.wikipedia.org/wiki/Turing_completeness) set of instructions for VCV. I would also use it to teach my child about computing and programming :).

My dream is to one day port it to eurorack (but I'd need to learn electronics first 😅).

## Credits

- Neuron original design: [Andrew Fitch](https://www.nonlinearcircuits.com/)
- Code and Panels: [Stalys](https://linktr.ee/stalysmusic)
- Neuron VCV implementation: [Michael Hetrick](https://mhetrick.com/)
- Befaco AxB+C VCV implementation: [Befaco](https://github.com/VCVRack/Befaco)

## Installation

- **Dependencies:** Follow the steps in the [official VCV Rack manual](https://vcvrack.com/manual/Building#setting-up-your-development-environment). You do not need to build the Rack itself.
- **Clone  variablethis repository in the destination of your choice:** `git clone https://github.com/denischevalier/StalysVCVPlugin`.
- **Go into the plugin directory:** `cd StalysVCVPlugin`.
- **Setup the environmnent:** `export RACK_DIR=path/to/your/sdk/installation`.
- **Build and install the modules:** `make install`.

## Modules

<details><summary>VC Dual Neuron</summary>

![VC Dual Neuron](/img/vcdualneuron.png)

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

</details>

<details><summary>Analog Shift Register</summary>

![ASR](/img/asr.png)

This module is an 8 step shift register: At each incoming CLOCK trigger, all output voltages are shifted down one position and the value of IN is sampled into the first output.

Typical use would be to generate canon melodies.

</details>

<details><summary>8 Comparator</summary>

![8 Comparator](/img/comparator.png)

This module is what its name indicates: 8 VC comparators: It outputs a gate whenever the input signal is superior to the value signal (defaults to 0).

Plug two different LFOs to see complex rhythms emerge.

</details>

<details><summary>8 Multiplier</summary>

![8 Multiplier](/img/multiplier.png)

This module is 8 four quadrant multipliers or ring-modulators (with attenuversion of the Carrier). A 5V voltage is normaled to the Carrier input.

If no cable is plugged into an output, it is summed to the next outputs.

</details>

<details><summary>8 Sum</summary>

![8 Sum](/img/sum.png)

This module is 8 three inputs unity mixer.

If no cable is plugged into an output, it is summed to the next outputs.

</details>

<details><summary>8 Diff</summary>

![8 Diff](/img/diff.png)

This module is 8 three inputs subtracter.

</details>

<details><summary>8 Not</summary>

![8 Not](/img/not.png)

This module is 8 boolean Not operators: they invert the gates they receive as inputs.

</details>

<details><summary>8 Abs</summary>

![8 Abs](/img/abs.png)

This modules inverses the negative portion of any input voltage.

</details>

<details><summary>8 VC Sample&Delay</summary>

![8 VC Sample&Delay](/img/vcsampleanddelay.png)

This module is 8 sample and hold with a twist: it will only take gate into account every STEP pulses.

This can serve for counterpoint melody generation, VC clock division, or any usual Sample&Hold usages.

</details>

<details><summary>Digital to Analog Converter</summary>

![DAC](/img/dac.png)

This modules is an 8 bit bipolar digital to analog converter. It converts input triggers and gates into bipolar CV.

One example of use for it is in a Rungler context: Connect it's output to the frequency of a VCO, the inverted output to the frequency of another VCO. Send the output of VCO 1 to the Analog Shift Register, then the outs of the ASR to the DAC, and use the square out of the second VCO as clock for the ASR: You've got a pseudo-random melody generator.

</details>

<details><summary>Analog to Digital Converter</summary>

![ADC](/img/adc.png)

This modules is an 8 bit bipolar analog to digital converter. It converts input signal into 8 gates. Gates 1-7 represent the number 1 to 127, where as the 8th is the sign of the signal.

Pair it with DAC and invert or mute some gates to get a pretty gnarly bitcrusher/distortion/waveshaper. Or pass any signal to it to generate interesting rhythms.

</details>

<details><summary>8 Max</summary>

![8 Max](/img/max.png)

This module is 8 times three input MAX operator logic module (ie. Analog OR). Inputs are normalized to -10 volts to permit to not use all. If an output is not plugged, its value is maxed with the next row, thus allowing up to a 24 inputs max computation.

</details>

<details><summary>8 Min</summary>

![8 Min](/img/min.png)

This module is 8 times three input MIN operator logic module (ie. Analog AND). Inputs are normalized to 10 volts to permit to not use all. If an output is not plugged, its value is minimized with the next row, thus allowing up to a 24 inputs min computation.

</details>

<details><summary>8 Rectifier (±)</summary>

![8 Positive/Negative Rectifier](/img/posnegrectifier.png)

This module is 8 rectifiers that output the positive portion of a signal to the **+** output, and the negative to the **-** output.

This can serve to apply different treatment to each half of a waveform or as a distortion effect.

</details>

<details><summary>8 Averager</summary>

![8 Avg](/img/avg.png)

This module is an octal three-inputs averager: It computes the average of its connected inputs. If an output is not connected, it will compute add the corresponding inputs to the average of the following output, thus permitting averaging of up to 24 inputs.

</details>

<details><summary>8 Function generators</summary>

![8 Function](/img/function.png)

This module is 8 function generators. Each row takes (from left to right) one trigger input, one signal input, one rise CV and param, one fall CV and param. It then outputs the slew processed signal, a gate during rising phase, a gate during falling phase and an End-Of-Cycle gate. Note that EOC is up when no cycle (as on a Serge DUSG), to permit feedback.

This module is a jack of all trades. Amongst its various use-cases, here are the main ones:

* AD envelope generator
* LFO
* VCO
* Gate Sequencer
* Rudimentary low-pass gate
* Filter
* Clock generator
* Slew limiter

Inspired by [Befaco Slew Limiter](https://github.com/VCVRack/Befaco/blob/v1/src/SlewLimiter.cpp).

</details>

<details><summary>8 A/B Y</summary>

![8 A/B Y](/img/aby.png)

This module is an octal 2-in 1-out switch, eg A/B Y switch.

It can be used to switch between chorus and verse sequences for instance.

</details>

<details><summary>8 Offset</summary>

![8 Offset](/img/offset.png)

This module is an octal offset module, generating voltages from -10 to 10V.

</details>

## Contribute

You can support me in many ways:

* If you want to support me financially, please consider going to [my Patreon](https://www.patreon.com/stalysmusic).
* You can also listen to [my music](https://linktr.ee/stalysmusic).
* If you use my modules in one of your projects (videos, tracks, education, etc.), please send me [an email](mailto:stalysmusic+vcv@gmail.com) for me to check it out. I'll make sure to reference you here.
* You can [create issues](https://github.com/denischevalier/StalysVCVPlugin/issues), improve the [documentation](https://github.com/denischevalier/StalysVCVPlugin/wiki) or create [pull requests](https://github.com/denischevalier/StalysVCVPlugin/pulls) here.
* If you know electronics and are interested in porting one of my modules, please feel free to [contact me](mailto:stalysmusic+vcv@gmail.com).
