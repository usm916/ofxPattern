//
//  midiImport.h
//  LS_PatternGeenerate
//
//  Created by usm on 1/6/13.
//
//

#ifndef __LS_PatternGeenerate__midiImport__
#define __LS_PatternGeenerate__midiImport__

#include <iostream>
#include "ofxMidi.h"
#include "OSCvalue.h"

class MidiImportToOSCvalue : public ofThread, public ofxMidiListener {

public:
    MidiImportToOSCvalue(){}
    ~MidiImportToOSCvalue(){}
    
    void setup(OSCVALUE*);
	void update();
	void draw();
	void exit();
	
//	void keyPressed(int key);
//	void keyReleased(int key);
    
    void newMidiMessage(ofxMidiMessage& eventArgs);
    bool tone(string);
    bool cc(string);
    bool pc(string);

    int tonePush(string);
    
    stringstream text;
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
private:
    
    OSCVALUE* oscValue;
};

#endif /* defined(__LS_PatternGeenerate__midiImport__) */
