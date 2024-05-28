# Il Frattalatore: the Fractal Synthesizer
## Computer Music - Languages and Systems AY 2021/2022, Homework 2.
### By CAPR Group: Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli

<br />
<div align="center">
<img src="https://user-images.githubusercontent.com/51057211/169388464-58b6c300-094e-49a4-bde6-31e8fce45283.png" width="200" height="200">
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#il-frattalatore">Il Frattalatore</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#folder-structure">Folder Structure</a>
    <li>
      <a href="#usage">Usage</a>
      <ul>
      <a href="#fractal-window">Fractal Window</a>
      </ul>
      <ul>
      <a href="#frattalatore-gui">Frattalatore GUI</a>
      </ul>
    </li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

## Il Frattalatore
The Frattalatore is an additive synthesizer that exploits the fractal mathematical systems to produce singular sounds. It has been implemented using Juce 6 and external C++ libraries: ***SFML*** and ***oscpack***.
The Frattalatore outputs a sum of 5 oscillators’ contributions, related each other by a fractal set of parameters. All the oscillators take as input the same MIDI note input given by a piano keyboard or by the VST virtual keyboard, but they are set with different sets of parameters that come from the fractal computation obtained via OSC (Open Sound Control) messages. The Frattalatore can be used either as a standalone application or as a VST in a DAW, such as Ableton, Pro Tools etc.

### Built With

These are the major frameworks/libraries used to bootstrap the  Frattalatore project.

* [oscpack](http://www.rossbencina.com/code/oscpack)
* [SFML](https://github.com/SFML/SFML)
* [JUCE 6](https://juce.com/)

## Folder structure
Two main folders, **Frattalatore** and **FractalWindow** contain respectively the JUCE synthesizer project and the fractal generator project.
In the Frattalatore folder the structure is the same as a standard JUCE plugin application, with the ***.jucer*** file that can be opened with the cross-platform **Projucer** and then built with every other IDE such as Visual Studio and XCode.
The synth can be opened following the path ***Frattalatore\Builds\Visual Studio 2022\x64\Debug***, choosing the folder of the version to use (VST or Standalone) and opening it using a DAW or running it via the .exe file as a standalone application.
The **FractalWindow** folder contains the fractal generator. The project has been built using **Visual Studio 17 2022**. Following the path ***FractalWindow\x64\Debug*** or ***FractalWindow\x64\Release*** there is the ***FractalWindow.exe*** that can be opened. This will run the application.

## How to run the Frattalatore

The synth can be used in two modalities: as a classic VST synthesizer or connecting it with the fractal generator. This last can be easily done just running both the Frattalatore and the FractalWindow.exe following the previously indicated paths in the repository. 

<p align="right">(<a href="#top">back to top</a>)</p>

## Usage
### Fractal Window
![Main Menu](https://user-images.githubusercontent.com/51057211/169401448-8dc7afb9-c972-4edd-9cad-b2ffd8fe2ee2.png)
|:--:|
| <b>Main window</b>|
![Mandelbrot](https://user-images.githubusercontent.com/51057211/169401671-b76a4744-5b97-4218-ba14-5741e8fe2e23.png)
|:--:|
| <b>Mandelbrot Fractal</b>|


* **Main Window:** moving with the up/down keyboard arrows the user can choose which fractal shape to be generated: Mandelbrot set, Julia set 1, Julia set 2 and Burning Ship, then pressing Enter the Fractal will appear in another window.
* **Fractal Window:** Rolling the mouse wheel or zooming in/out on the trackpad the user can increase or decrease the number of iterations for the fractal computation, thus the image in the window will have more or less resolution depending on this number of iterations.


### Frattalatore GUI
![MandelSynth](https://user-images.githubusercontent.com/51057211/169401305-0098db14-5628-4c05-a4f0-25d2347a9e72.png)
|:--:|
| <b>Synth GUI</b>|

* **Oscillators:** The Frattalatore has five independent oscillators and each one has a combo box where to choose the type of the oscillator wave between sine, triangular and square waves. Then, ***gain, pitch, Frequency Modulation(FM) Frequency and FM Depth*** knobs are present. These last two knobs are the ones that can be controlled by the OSC messages coming from the fractal window. A more detailed description of how the OSC messages affect the FM parameters is written in the report contained in this repository.
* **Filter:** A filter section that contains a combo box where to choose the kind of filter: ***Low Pass (LPF), Band Pass(BPF) and High Pass(HPF)***. The knobs control the cut-off frequency of the filter and the resonance.
* **LFO:** a Low Frequency Oscillator(LFO) controlled by a sine wave with a certain frequency (LFO Freq knob) and an amplitude or Depth.
* **ADSR:** Envelope modulation section, The knobs manage the Attack, Decay, Sustain and Release envelope parameters.

## Contact

Claudio Eutizi - claudio.eutizi@mail.polimi.it
Andres Bertazzi - andres.bertazzi@mail.polimi.it
Pierluigi Tartabini - pierluigi.tartabni@mail.polimi.it
Riccardo Martinelli - riccardo1.martinelli@mail.polimi.it

Project Link: [Frattalatore-CAPR](https://github.com/polimi-cmls-22/group9-hw-JUCE-CAPR)

<p align="right">(<a href="#top">back to top</a>)</p>

