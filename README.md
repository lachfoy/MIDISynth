# MIDISynth
This repo is just a collection of programs to try and get a MIDI controlled digital synth working with a Raspberry Pi.
The main file (that actually works) is midi_synth.py which contains code heavily referenced from https://github.com/18alantom/synth

Some dependancies need to be installed before running midi_synth.py.
```
python3 -m pip install -U pygame –user
sudo apt install python3-pyaudio
```
Make sure that pygame is at least version 2.0.1 and PyAudio is at least version 0.2.11.
After these requirements are met the program can be run using Python 3 by typing `python3 midi_synth.py`.

Other files are mainly testing and experimenting with different libs to try and reduce the latency.
