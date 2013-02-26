//
//  midiImport.cpp
//  LS_PatternGeenerate
//
//  Created by usm on 1/6/13.
//
//

#include "midiImport.h"

//--------------------------------------------------------------
void MidiImportToOSCvalue::setup(OSCVALUE* _oscValue) {
    
    oscValue = _oscValue;

	ofSetLogLevel(OF_LOG_VERBOSE);
	
	// print input ports to console
	midiIn.listPorts(); // via instance
	//ofxMidiIn::listPorts(); // via static as well
	
	// open port by number (you may need to change this)
	midiIn.openPort(1);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input");	// open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add miDIimportToOSCvalue as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(true);
}

//--------------------------------------------------------------
void MidiImportToOSCvalue::update() {
}

//--------------------------------------------------------------
void MidiImportToOSCvalue::draw() {
    
    ofPushMatrix();
    ofTranslate(0,300);
	ofSetColor(255);
	
	// draw the last recieved message contents to the screen
	text << "Received: " << ofxMidiMessage::getStatusString(midiMessage.status);
	ofDrawBitmapString(text.str(), 20, 20);
	text.str(""); // clear
	
	text << "channel: " << midiMessage.channel;
	ofDrawBitmapString(text.str(), 20, 34);
	text.str(""); // clear
	
	text << "pitch: " << midiMessage.pitch;
	ofDrawBitmapString(text.str(), 20, 48);
	text.str(""); // clear
	ofRect(20, 58, ofMap(midiMessage.pitch, 0, 127, 0, 180), 20);
	
	text << "velocity: " << midiMessage.velocity;
	ofDrawBitmapString(text.str(), 20, 96);
	text.str(""); // clear
	ofRect(20, 105, ofMap(midiMessage.velocity, 0, 127, 0, 180), 20);
	
	text << "control: " << midiMessage.control;
	ofDrawBitmapString(text.str(), 20, 144);
	text.str(""); // clear
	ofRect(20, 154, ofMap(midiMessage.control, 0, 127, 0, 180), 20);
	
	text << "value: " << midiMessage.value;
	ofDrawBitmapString(text.str(), 20, 192);
	text.str(""); // clear
	if(midiMessage.status == MIDI_PITCH_BEND) {
		ofRect(20, 202, ofMap(midiMessage.value, 0, MIDI_MAX_BEND, 0, 180), 20);
	}
	else {
		ofRect(20, 202, ofMap(midiMessage.value, 0, 127, 0, 180), 20);
	}
	
	text << "delta: " << midiMessage.deltatime;
	ofDrawBitmapString(text.str(), 20, 240);
	text.str(""); // clear
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void MidiImportToOSCvalue::exit() {
	
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------------
void MidiImportToOSCvalue::newMidiMessage(ofxMidiMessage& msg) {
    
	// make a copy of the latest message
	midiMessage = msg;
    switch(midiMessage.velocity){
        case 1:
            oscValue->mPush[3][midiMessage.channel-1][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status));
            break;
        case 2:
            oscValue->mToggle[6][midiMessage.channel-1][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status));
            break;
        case 3:
            oscValue->mPush[2][midiMessage.channel-1][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status));
            break;
        case 4:
            oscValue->mPush[1][midiMessage.channel-1][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status));
            break;
        case 5:
            oscValue->mPush[6][midiMessage.channel-1][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status));
            break;
        case 6:
            oscValue->mPush[8][midiMessage.channel-1][2] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status));
            break;
        case 7:
            oscValue->mPush[8][midiMessage.channel-1][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status));
            break;
        case 8:
            oscValue->mPush[8][midiMessage.channel-1][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status));
            break;
        case 9:
            oscValue->mPush[7][midiMessage.channel-1][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status));
            break;
        case 10:
            oscValue->mToggle[1][midiMessage.channel-1][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status));
            break;
        default:
            break;
    }
//        cout << "set on/off:: " << ofxMidiMessage::getStatusString(midiMessage.status) << endl;
    if(cc(ofxMidiMessage::getStatusString(midiMessage.status))){
        oscValue->tFader[midiMessage.channel-1][midiMessage.control] = (float)midiMessage.value/128;
    }else if(pc(ofxMidiMessage::getStatusString(midiMessage.status))){
        switch (midiMessage.channel) {
            case 1: oscValue->msX[0] = (float)midiMessage.value/128; break;
            case 2: oscValue->msY[0] = (float)midiMessage.value/128; break;
            default: break;
        }
        
    }
}

bool MidiImportToOSCvalue::tone(string _onOff){
    if(_onOff=="Note On"){
        return true;
    }else if(_onOff=="Note Off"){
        return false;
    }else{
        return false;
    }
}

int MidiImportToOSCvalue::tonePush(string _onOff){
    if(_onOff=="Note On"){
        return 1;
    }else if(_onOff=="Note Off"){
        return 0;
    }else{
        return 0;
    }
}

bool MidiImportToOSCvalue::cc(string _CC){
    if(_CC=="Control Change"){
        return true;
    }else{
        return false;
    }
}

bool MidiImportToOSCvalue::pc(string _CC){
    if(_CC=="Program Change"){
        return true;
    }else{
        return false;
    }
}

//--------------------------------------------------------------
//void MidiImportToOSCvalue::keyPressed(int key) {
//    
//	switch(key) {
//		case 'l':
//			midiIn.listPorts();
//			break;
//	}
//}
/*
 // APC 40
 case 10:
 switch (midiMessage.channel) {
 case 1:oscValue->mToggle[1][0][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 2:oscValue->mToggle[1][1][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 3:oscValue->mToggle[1][2][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 4:oscValue->mToggle[1][3][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 5:oscValue->mToggle[1][4][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 6:oscValue->mToggle[1][5][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 7:oscValue->mToggle[1][6][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 8:oscValue->mToggle[1][7][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 default:break;
 }
 break;
 case 2:
 switch (midiMessage.channel) {
 case 1:oscValue->mToggle[6][0][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 2:oscValue->mToggle[6][1][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 3:oscValue->mToggle[6][2][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 4:oscValue->mToggle[6][3][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 5:oscValue->mToggle[6][4][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 6:oscValue->mToggle[6][5][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 7:oscValue->mToggle[6][6][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 8:oscValue->mToggle[6][7][0] = tone(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 default:break;
 }
 break;
 case 9:
 switch (midiMessage.channel) {
 case 1:oscValue->mPush[7][0][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 2:oscValue->mPush[7][1][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 3:oscValue->mPush[7][2][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 4:oscValue->mPush[7][3][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 5:oscValue->mPush[7][4][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 6:oscValue->mPush[7][5][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 //                case 7:oscValue->mPush[6][4][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 //                case 8:oscValue->mPush[6][5][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 default:break;
 }
 break;
 
 case 53:
 switch (midiMessage.channel) {
 case 1:oscValue->mPush[8][0][2] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 2:oscValue->mPush[8][1][2] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 3:oscValue->mPush[8][2][2] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 4:oscValue->mPush[8][3][2] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 5:oscValue->mPush[8][4][2] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 6:oscValue->mPush[8][5][2] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 7:oscValue->mPush[8][6][2] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 8:oscValue->mPush[8][7][2] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 default:break;
 }
 break;
 
 case 54:
 switch (midiMessage.channel) {
 case 1:oscValue->mPush[8][0][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 2:oscValue->mPush[8][1][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 3:oscValue->mPush[8][2][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 4:oscValue->mPush[8][3][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 5:oscValue->mPush[8][4][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 6:oscValue->mPush[8][5][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 7:oscValue->mPush[8][6][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 8:oscValue->mPush[8][7][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 default:break;
 }
 break;
 
 case 55:
 switch (midiMessage.channel) {
 case 1:oscValue->mPush[8][0][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 2:oscValue->mPush[8][1][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 3:oscValue->mPush[8][2][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 4:oscValue->mPush[8][3][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 5:oscValue->mPush[8][4][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 6:oscValue->mPush[8][5][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 7:oscValue->mPush[8][6][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 8:oscValue->mPush[8][7][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 default:break;
 }
 cout << "55" << endl;
 cout << oscValue->mPush[8][0][0] << endl;
 break;
 case 56:
 switch (midiMessage.channel) {
 case 1:oscValue->mPush[8][0][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 2:oscValue->mPush[8][1][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 3:oscValue->mPush[8][2][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 4:oscValue->mPush[8][3][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 5:oscValue->mPush[8][4][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 6:oscValue->mPush[8][5][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 7:oscValue->mPush[8][6][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 8:oscValue->mPush[8][7][1] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 default:break;
 }
 break;
 case 57:
 switch (midiMessage.channel) {
 case 1:oscValue->mPush[1][0][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 2:oscValue->mPush[1][1][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 3:oscValue->mPush[1][2][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 4:oscValue->mPush[1][3][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 5:oscValue->mPush[2][0][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 6:oscValue->mPush[2][1][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 7:oscValue->mPush[2][2][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 case 8:oscValue->mPush[2][3][0] = tonePush(ofxMidiMessage::getStatusString(midiMessage.status)); break;
 default:break;
 }
 break;
 
 default:break;
 }
 cout << "set on/off:: " << ofxMidiMessage::getStatusString(midiMessage.status) << endl;
 
 switch (midiMessage.channel){
 case 1:
 switch (midiMessage.control) {
 //APC CUE LEVEL
 case 7:oscValue->tFader[0][0] = (float)midiMessage.value/128; break;
 //APC DEVICE CONTROL
 case 16:oscValue->tFader[3][0] = (float)midiMessage.value/128; break;
 case 17:oscValue->tFader[3][1] = (float)midiMessage.value/128; break;
 case 18:oscValue->tFader[3][2] = (float)midiMessage.value/128; break;
 case 19:oscValue->tFader[3][3] = (float)midiMessage.value/128; break;
 case 20:oscValue->tFader[3][4] = (float)midiMessage.value/128; break;
 case 21:oscValue->tFader[3][5] = (float)midiMessage.value/128; break;
 case 22:oscValue->tFader[3][6] = (float)midiMessage.value/128; break;
 case 23:oscValue->tFader[3][7] = (float)midiMessage.value/128; break;
 //APC TRACK CONTROL
 case 48:oscValue->tFader[0][0] = (float)midiMessage.value/128; break;
 case 49:oscValue->tFader[0][1] = (float)midiMessage.value/128; break;
 case 50:oscValue->tFader[0][2] = (float)midiMessage.value/128; break;
 case 51:oscValue->tFader[2][0] = (float)midiMessage.value/128; break;
 
 case 52:oscValue->tFader[0][3] = (float)midiMessage.value/128; break;
 case 53:oscValue->tFader[0][4] = (float)midiMessage.value/128; break;
 case 54:oscValue->tFader[0][5] = (float)midiMessage.value/128; break;
 case 55:oscValue->tFader[2][1] = (float)midiMessage.value/128; break;
 default:break;
 }
 break;
 case 2:
 switch (midiMessage.control) {
 //APC CUE LEVEL
 case 7:oscValue->tFader[0][0] = (float)midiMessage.value/128; break;
 //APC DEVICE CONTROL
 case 16:oscValue->tFader[3][0] = (float)midiMessage.value/128; break;
 case 17:oscValue->tFader[3][1] = (float)midiMessage.value/128; break;
 case 18:oscValue->tFader[3][2] = (float)midiMessage.value/128; break;
 case 19:oscValue->tFader[3][3] = (float)midiMessage.value/128; break;
 case 20:oscValue->tFader[3][4] = (float)midiMessage.value/128; break;
 case 21:oscValue->tFader[3][5] = (float)midiMessage.value/128; break;
 case 22:oscValue->tFader[3][6] = (float)midiMessage.value/128; break;
 case 23:oscValue->tFader[3][7] = (float)midiMessage.value/128; break;
 default:break;
 }
 break;
 case 3:
 switch (midiMessage.control) {
 //APC CUE LEVEL
 case 7:oscValue->tFader[0][0] = (float)midiMessage.value/128; break;
 //APC DEVICE CONTROL
 case 16:oscValue->tFader[0][6] = (float)midiMessage.value/128; break;
 case 17:oscValue->tFader[1][0] = (float)midiMessage.value/128; break;
 case 18:oscValue->tFader[1][1] = (float)midiMessage.value/128; break;
 case 19:oscValue->tFader[1][2] = (float)midiMessage.value/128; break;
 case 20:oscValue->tFader[1][3] = (float)midiMessage.value/128; break;
 //                case 21:oscValue->tFader[3][5] = (float)midiMessage.value/128; break;
 //                case 22:oscValue->tFader[3][6] = (float)midiMessage.value/128; break;
 //                case 23:oscValue->tFader[3][7] = (float)midiMessage.value/128; break;
 default:break;
 }
 break;
 case 4:
 switch (midiMessage.control) {
 //APC CUE LEVEL
 case 7:oscValue->tFader[0][0] = (float)midiMessage.value/128; break;
 //APC DEVICE CONTROL
 case 16:oscValue->tFader[2][0] = (float)midiMessage.value/128; break;
 case 17:oscValue->tFader[2][1] = (float)midiMessage.value/128; break;
 case 18:oscValue->tFader[2][2] = (float)midiMessage.value/128; break;
 case 19:oscValue->tFader[2][3] = (float)midiMessage.value/128; break;
 //                case 20:oscValue->tFader[2][4] = (float)midiMessage.value/128; break;
 //                case 21:oscValue->tFader[2][5] = (float)midiMessage.value/128; break;
 ////                case 22:oscValue->tFader[2][6] = (float)midiMessage.value/128; break;
 ////                case 23:oscValue->tFader[2][7] = (float)midiMessage.value/128; break;
 default:break;
 }
 break;
 case 5:
 switch (midiMessage.control) {
 //APC CUE LEVEL
 case 7:oscValue->tFader[0][0] = (float)midiMessage.value/128; break;
 //APC DEVICE CONTROL
 case 16:oscValue->tFader[3][0] = (float)midiMessage.value/128; break;
 case 17:oscValue->tFader[3][1] = (float)midiMessage.value/128; break;
 case 18:oscValue->tFader[3][2] = (float)midiMessage.value/128; break;
 case 19:oscValue->tFader[3][3] = (float)midiMessage.value/128; break;
 case 20:oscValue->tFader[3][4] = (float)midiMessage.value/128; break;
 case 21:oscValue->tFader[3][5] = (float)midiMessage.value/128; break;
 case 22:oscValue->tFader[3][6] = (float)midiMessage.value/128; break;
 case 23:oscValue->tFader[3][7] = (float)midiMessage.value/128; break;
 default:break;
 }
 break;
 case 6:
 switch (midiMessage.control) {
 //APC CUE LEVEL
 case 7:oscValue->tFader[0][0] = (float)midiMessage.value/128; break;
 //APC DEVICE CONTROL
 case 16:oscValue->tFader[3][0] = (float)midiMessage.value/128; break;
 case 17:oscValue->tFader[3][1] = (float)midiMessage.value/128; break;
 case 18:oscValue->tFader[3][2] = (float)midiMessage.value/128; break;
 case 19:oscValue->tFader[3][3] = (float)midiMessage.value/128; break;
 case 20:oscValue->tFader[3][4] = (float)midiMessage.value/128; break;
 case 21:oscValue->tFader[3][5] = (float)midiMessage.value/128; break;
 case 22:oscValue->tFader[3][6] = (float)midiMessage.value/128; break;
 case 23:oscValue->tFader[3][7] = (float)midiMessage.value/128; break;
 default:break;
 }
 break;
 case 7:
 switch (midiMessage.control) {
 //APC CUE LEVEL
 case 7:oscValue->tFader[2][2] = (float)midiMessage.value/128; break;
 //APC DEVICE CONTROL
 case 16:oscValue->tFader[3][0] = (float)midiMessage.value/128; break;
 case 17:oscValue->tFader[3][1] = (float)midiMessage.value/128; break;
 case 18:oscValue->tFader[3][2] = (float)midiMessage.value/128; break;
 case 19:oscValue->tFader[3][3] = (float)midiMessage.value/128; break;
 case 20:oscValue->tFader[3][4] = (float)midiMessage.value/128; break;
 case 21:oscValue->tFader[3][5] = (float)midiMessage.value/128; break;
 case 22:oscValue->tFader[3][6] = (float)midiMessage.value/128; break;
 case 23:oscValue->tFader[3][7] = (float)midiMessage.value/128; break;
 default:break;
 }
 break;
 
 case 8:
 switch (midiMessage.control) {
 //APC CUE LEVEL
 case 7:oscValue->tFader[0][0] = (float)midiMessage.value/128; break;
 //APC DEVICE CONTROL
 case 16:oscValue->tFader[3][0] = (float)midiMessage.value/128; break;
 case 17:oscValue->tFader[3][1] = (float)midiMessage.value/128; break;
 case 18:oscValue->tFader[3][2] = (float)midiMessage.value/128; break;
 case 19:oscValue->tFader[3][3] = (float)midiMessage.value/128; break;
 case 20:oscValue->tFader[3][4] = (float)midiMessage.value/128; break;
 case 21:oscValue->tFader[3][5] = (float)midiMessage.value/128; break;
 case 22:oscValue->tFader[3][6] = (float)midiMessage.value/128; break;
 case 23:oscValue->tFader[3][7] = (float)midiMessage.value/128; break;
 default:break;
 }
 break;
 case 9:
 switch (midiMessage.control) {
 //APC CUE LEVEL
 case 7:oscValue->tFader[0][0] = (float)midiMessage.value/128; break;
 //APC DEVICE CONTROL
 case 16:oscValue->tFader[4][0] = (float)midiMessage.value/128; break;
 case 17:oscValue->tFader[4][1] = (float)midiMessage.value/128; break;
 case 18:oscValue->tFader[4][2] = (float)midiMessage.value/128; break;
 case 19:oscValue->tFader[4][3] = (float)midiMessage.value/128; break;
 //                case 20:oscValue->tFader[3][4] = (float)midiMessage.value/128; break;
 //
 
 */
