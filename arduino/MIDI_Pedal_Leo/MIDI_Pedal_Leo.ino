/**********************************************************************
Program name     : MIDI Pedal Leo
Version          : 0.01
Author           : CYNOLEO
Date(MMDDYY)     : 010324
DESCRIPTION      : 
MIDI Pedal Leo is a MIDI controller with 4 foot switches. 
Short click will make Simple MIDI Pedal send out MIDI CC command 
Long Press will make Simple MIDI Pedal send out MIDI PC command
-----------------------------------------------------------------------
More details about Simple MIDI Pedal can be found on Gig Pedal Website
https://gigpedal.blogspot.com/
***********************************************************************/
#include <MIDIUSB.h>
#include <ResponsiveAnalogRead.h>
#include <OneButton.h>

#define DEBUG 0

#define MIDI_CHANNEL 0 
#define BUTTON0_PIN 2
#define BUTTON1_PIN 3
#define BUTTON2_PIN 4
#define BUTTON3_PIN 5
#define BUTTON0_CONTROLLER_NUMBER 20      // CLICK CONGROLER NUMBER
#define BUTTON1_CONTROLLER_NUMBER 21
#define BUTTON2_CONTROLLER_NUMBER 22
#define BUTTON3_CONTROLLER_NUMBER 23
#define BUTTON0_PROGRAM_NUMBER 1          // LONG PRESS Program Change Number
#define BUTTON1_PROGRAM_NUMBER 2
#define BUTTON2_PROGRAM_NUMBER 6
#define BUTTON3_PROGRAM_NUMBER 8
#define LONG_PRESS_INTERVAL 2000          //LONG PRESS TIME 
#define BUTTON_HIGH_VALUE 0
#define BUTTON_LOW_VALUE 127

OneButton button0(BUTTON0_PIN, true);
OneButton button1(BUTTON1_PIN, true);
OneButton button2(BUTTON2_PIN, true);
OneButton button3(BUTTON3_PIN, true);

int button0Value;
int button1Value;
int button2Value;
int button3Value;

bool button0LongPressedFired;
bool button1LongPressedFired;
bool button2LongPressedFired;
bool button3LongPressedFired;

const int buttonHighValue = BUTTON_HIGH_VALUE;  
const int buttonLowValue = BUTTON_LOW_VALUE;    

byte midiCh = MIDI_CHANNEL; 

void setup() {
  button0.attachClick(button0ClickCtrl);
  button1.attachClick(button1ClickCtrl);
  button2.attachClick(button2ClickCtrl);
  button3.attachClick(button3ClickCtrl);

  //button0.attachLongPressStart(button0LongPressStartCtrl);
  button0.attachLongPressStop(button0LongPressStopCtrl);   
  button0.attachDuringLongPress(button0DuringLongPressCtrl); 
  button0.setLongPressIntervalMs(LONG_PRESS_INTERVAL);

  //button1.attachLongPressStart(button1LongPressStartCtrl);
  button1.attachLongPressStop(button1LongPressStopCtrl);
  button1.attachDuringLongPress(button1DuringLongPressCtrl); 
  button1.setLongPressIntervalMs(LONG_PRESS_INTERVAL);

  //button2.attachLongPressStart(button2LongPressStartCtrl);
  button2.attachLongPressStop(button2LongPressStopCtrl);   
  button2.attachDuringLongPress(button2DuringLongPressCtrl); 
  button2.setLongPressIntervalMs(LONG_PRESS_INTERVAL);  

  //button0.attachLongPressStart(button0LongPressStartCtrl);
  button3.attachLongPressStop(button3LongPressStopCtrl);   
  button3.attachDuringLongPress(button3DuringLongPressCtrl); 
  button3.setLongPressIntervalMs(LONG_PRESS_INTERVAL);  
}

void loop() {
  button0.tick();
  button1.tick();
  button2.tick();
  button3.tick();
}

//----------Button Short Press Control Functions----------
void button0ClickCtrl() {
  #if defined(DEBUG) 
  Serial.println("Button0 Pressed");
  #endif

  if (button0Value ==  buttonLowValue){
    button0Value=  buttonHighValue;
  } else {
    button0Value =  buttonLowValue;
  }

  controlChange(midiCh, BUTTON0_CONTROLLER_NUMBER, button0Value); //  (channel, CC number,  CC value)
  MidiUSB.flush();
}

void button1ClickCtrl() {
  #if defined(DEBUG) 
  Serial.println("Button1 Pressed");
  #endif
  if (button1Value ==  buttonLowValue){
    button1Value=  buttonHighValue;
  } else {
    button1Value =  buttonLowValue;
  }

  controlChange(midiCh, BUTTON1_CONTROLLER_NUMBER, button1Value); //  (channel, CC number,  CC value)
  MidiUSB.flush();
}

void button2ClickCtrl() {
  #if defined(DEBUG) 
  Serial.println("Button2 Pressed");
  #endif
  if (button2Value ==  buttonLowValue){
    button2Value=  buttonHighValue;
  } else {
    button2Value =  buttonLowValue;
  }

  controlChange(midiCh, BUTTON2_CONTROLLER_NUMBER, button2Value); //  (channel, CC number,  CC value)
  MidiUSB.flush();
}

void button3ClickCtrl() {
  #if defined(DEBUG) 
  Serial.println("Button3 Pressed");
  #endif
  if (button3Value ==  buttonLowValue){
    button3Value=  buttonHighValue;
  } else {
    button3Value =  buttonLowValue;
  }

  controlChange(midiCh, BUTTON3_CONTROLLER_NUMBER, button3Value); //  (channel, CC number,  CC value)
  MidiUSB.flush();
}

//----------Button Long Press Control Functions----------
void button0LongPressStopCtrl() {
  #if defined(DEBUG) 
  Serial.println("Button0 Long Press Stop");
  #endif 
  button0LongPressedFired = 0;
}

void button1LongPressStopCtrl() {
  #if defined(DEBUG) 
  Serial.println("Button1 Long Press Stop");
  #endif
  button1LongPressedFired = 0;
  
}

void button2LongPressStopCtrl() {
  #if defined(DEBUG) 
  Serial.println("Button2 Long Press Stop");
  #endif
  button2LongPressedFired = 0;
}

void button3LongPressStopCtrl() {
  #if defined(DEBUG) 
  Serial.println("Button3 Long Press Stop");
  #endif
  button3LongPressedFired = 0;
}

void button0DuringLongPressCtrl(){

  #if defined(DEBUG) 
  Serial.print(button0.getPressedMs());
  Serial.println("\t - DuringLongPress()");
  #endif

  if(!button0LongPressedFired){
    programChange(midiCh, BUTTON0_PROGRAM_NUMBER); // (channel, program number)
    MidiUSB.flush(); 
    
    #if defined(DEBUG) 
    Serial.println("Sent Button 0 MIDI Message");
    #endif
  }
  button0LongPressedFired = 1;  
}

void button1DuringLongPressCtrl(){

  #if defined(DEBUG) 
  Serial.print(button1.getPressedMs());
  Serial.println("\t - DuringLongPress()");
  #endif

  if(!button1LongPressedFired){
    programChange(midiCh, BUTTON1_PROGRAM_NUMBER); // (channel, program number)
    MidiUSB.flush(); 
    
    #if defined(DEBUG) 
    Serial.println("Sent Button 1 MIDI Message");
    #endif
  }
  button1LongPressedFired = 1;  
}

void button2DuringLongPressCtrl(){

  #if defined(DEBUG) 
  Serial.print(button2.getPressedMs());
  Serial.println("\t - DuringLongPress()");
  #endif

  if(!button2LongPressedFired){
    programChange(midiCh, BUTTON2_PROGRAM_NUMBER); // (channel, program number)
    MidiUSB.flush(); 
    
    #if defined(DEBUG) 
    Serial.println("Sent Button 2 MIDI Message");
    #endif
  }
  button2LongPressedFired = 1;
}

void button3DuringLongPressCtrl(){

  #if defined(DEBUG) 
  Serial.print(button3.getPressedMs());
  Serial.println("\t - DuringLongPress()");
  #endif

  if(!button3LongPressedFired){
    programChange(midiCh, BUTTON3_PROGRAM_NUMBER); // (channel, program number)
    MidiUSB.flush(); 
    
    #if defined(DEBUG) 
    Serial.println("Sent Button 3 MIDI Message");
    #endif
  }
  button3LongPressedFired = 1;  
}

//--- Midi Functions ---

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void programChange(byte channel, byte program) {
  midiEventPacket_t pc = {0x0C, 0xC0 | channel, program, 0};
  MidiUSB.sendMIDI(pc);
}