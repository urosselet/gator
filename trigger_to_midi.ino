// modular gate to midi converter
// @author Ulysse Rosselet

#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const int mdMidiNotes[] = {36, 38, 40, 41, 43, 45, 47, 48, 50, 52, 53, 55, 57, 59, 60, 62};
const int triggerPins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
boolean triggerStates[] = {false, false, false, false, false, false, false, false};
int midiChannel = 1;
int velocity = 127;

boolean lastState = false;

void setup()
{
  // initialize all trigger pins as inputs
  int i;
  for (i = 0; i < 8; i++) {
    pinMode(triggerPins[i], INPUT);
    digitalWrite(triggerPins[i], HIGH);
  }
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop()
{
  int i;
  for (i = 0; i < 8; i++) {
    boolean state = !digitalRead(triggerPins[i]); // input circuit causes low value on high trigger
    if (state == true && triggerStates[i] == false)
    {
      MIDI.sendNoteOn(mdMidiNotes[i], velocity, midiChannel);
    }
    if (state == false && triggerStates[i] == true) {
      MIDI.sendNoteOff(mdMidiNotes[i], velocity, midiChannel);
    }
    triggerStates[i] = state;
  }
}
