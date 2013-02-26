#ifndef _THREADED_OBJECT
#define _THREADED_OBJECT

#include "ofMain.h"
#include "ofxOsc.h"
#include "OSCvalue.h"
// OSC listen on port 12345 and 10000
#define PORT 12345
#define PORT2 10000
#define PORTSTRING 10008
#define NUM_MSG_STRINGS 20
//#define AvgCnt 12
//#define StkrNum 3
// this is not a very exciting example yet
// but ofThread provides the basis for ofNetwork and other
// operations that require threading.
//
// please be careful - threading problems are notoriously hard
// to debug and working with threads can be quite difficult

class threadedObject : public ofThread {
    
	public:
    
        //--------------------------------touchOSC
        ofxOscReceiver	receiverString;
        ofxOscReceiver	receiver2;
        ofxOscReceiver	receiver;
        
        float   timers[NUM_MSG_STRINGS];
        int current_msg_string;
        string  mouseButtonState;

        string  msg_strings[NUM_MSG_STRINGS];
        OSCVALUE oscValue;

        string oscTxt;
        float degAvg[6];
        int count;  // threaded fucntions that share data need to use lock (mutex)
	                // and unlock in order to write to that data
	                // otherwise it's possible to get crashes.
	                //
	                // also no opengl specific stuff will work in a thread...
	                // threads can't create textures, or draw stuff on the screen
	                // since opengl is single thread safe

		//--------------------------
		threadedObject(){
			count = 0;
		}

		void start(){
            startThread(true, false);   // blocking, verbose
        }

        void stop(){
            stopThread();
        }

		//--------------------------
		void threadedFunction(){

			while( isThreadRunning() != 0 ){
				if( lock() ){
					count++;
					if(count > 20000) count = 0;
					unlock();
					ofSleepMillis(1 * 1000);
				}
			}
		}

        //--------------------------
        void setup(){
            ofSetLogLevel(OF_LOG_VERBOSE);
            
            // listen on the given port
            cout << "listening for osc messages on port " << PORT << "\n";
            receiver.setup( PORT );
            receiver2.setup( PORT2 );
            receiverString.setup( PORTSTRING );
            current_msg_string = 0;
            
            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    if(i<8 && j<8) oscValue.tFader[i][j] = 0.5;
                    if(i<10 && j<10) oscValue.tToggle[i][j] = 0.5;
                    if(i<5 && j<7) oscValue.tPush[i][j] = 0.5;
                }
            }
            for(int i=0;i<9;i++){
                for(int j=0;j<12;j++){
                    for(int k=0;k<10;k++){
                        oscValue.mToggle[i][j][k] = false;
                        oscValue.mPush[i][j][k] = false;
                    }
                }
            }
        }
		//--------------------------
		void draw(){

		}

        void update(){
            //--------------------------------------------------------------touchOSC
            // hide old messages
            for ( int i=0; i<NUM_MSG_STRINGS; i++ )
            {
                if ( timers[i] < ofGetElapsedTimef() )
                    msg_strings[i] = "";
            }
            
            // check for waiting messages
            while( receiver.hasWaitingMessages() )
            {
                // get the next message
                ofxOscMessage m;
                receiver.getNextMessage( &m );
                
                char nameOsc[20];
                char numOsc[20], adrA[20], adrB[20];
                char ssnumOsc[20], c[50];
                float fadrA, fadrB;
                
                char oibf[100];// = m.getAddress().c_str();
                strcpy(oibf, m.getAddress().c_str());
                sscanf( oibf, "/%[^/]/%[^/]/%[^/]/%[^/]", numOsc, nameOsc, adrA, adrB);
                stringstream getMessage;
                getMessage << m.getAddress().c_str();
                getMessage >> c >> fadrA >> c >> fadrB;
                string checkStr = "";
                checkStr = checkStr + nameOsc;
                string checkStrG = "";
                checkStrG = checkStrG + numOsc;
                
                if( checkStr == "multixy" ){
                    int num = adrB[0]-49;//ASCII code number 48+1
                    oscValue.mmx[num] = m.getArgAsFloat( 0 );
                    oscValue.mmy[num] = m.getArgAsFloat( 1 );
                }
                else if(checkStr == "xy1"){
                    int numParts = numOsc[0]-49;//ASCII code number 48+1
                    oscValue.msX[numParts] = m.getArgAsFloat( 0 );
                    oscValue.msY[numParts] = m.getArgAsFloat( 1 );
//            cout << msX[1] << endl;
                }
                else if(checkStr == "mf"){
                    int numParts = numOsc[0]-49;
                    int fnumA = adrA[0]-49;
                    int fnum = adrB[0]-49;
//                    int fnum = fadrB-49;
                    oscValue.tFader[numParts][fnum] = m.getArgAsFloat( 0 );           
                }
                else if(checkStr == "mt"){
                    int numParts = numOsc[0]-49;
                    int fnumA = adrA[0]-49;
                    int fnum = adrB[0]-49;
//                    int fnum = fadrB-49;
                    if(m.getArgAsInt32( 0 ) == 1){
                        oscValue.mToggle[numParts][fnum][fnumA] = true;    
                    } else if(m.getArgAsInt32( 0 ) == 0){
                        oscValue.mToggle[numParts][fnum][fnumA] = false;
                    }
                    cout << numParts << "," << fnum << endl;
                    if(oscValue.mToggle[1][0])cout << "[1][0] = true" << endl;;
                }
                else if(checkStr == "mp"){
                    int numParts = numOsc[0]-49;
                    int fnumA = adrA[0]-49;
                    int fnum = adrB[0]-49;
//                        int fnum = fadrB-49;
                    if(m.getArgAsInt32( 0 ) == 1){
                        oscValue.mPush[numParts][fnum][fnumA] = true;    
                    } else if(m.getArgAsInt32( 0 ) == 0){
                        oscValue.mPush[numParts][fnum][fnumA] = false;
                    }
                }
                else {
                    // unrecognized message: display on the bottom of the screen
                    string msg_string;
                    msg_string = m.getAddress();
                    msg_string += ": ";
                    for ( int i=0; i<m.getNumArgs(); i++ )
                    {
                        // get the argument type
                        msg_string += m.getArgTypeName( i );
                        msg_string += ":";
                        // display the argument - make sure we get the right type
                        if( m.getArgType( i ) == OFXOSC_TYPE_INT32 )
                            msg_string += ofToString( m.getArgAsInt32( i ) );
                        else if( m.getArgType( i ) == OFXOSC_TYPE_FLOAT )
                            msg_string += ofToString( m.getArgAsFloat( i ) );
                        else if( m.getArgType( i ) == OFXOSC_TYPE_STRING )
                            msg_string += m.getArgAsString( i );
                        else
                            msg_string += "unknown";
                    }
                    // add to the list of strings to display
                    msg_strings[current_msg_string] = msg_string;
                    timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
                    current_msg_string = ( current_msg_string + 1 ) % NUM_MSG_STRINGS;
                    // clear the next line
                    msg_strings[current_msg_string] = "";
                }
            }
            
            // hide old messages
            for ( int i=0; i<NUM_MSG_STRINGS; i++ )
            {
                if ( timers[i] < ofGetElapsedTimef() )
                    msg_strings[i] = "";
            }
            
            // check for waiting messages
            while( receiver2.hasWaitingMessages() )
            {
                ofxOscMessage m2;
                receiver2.getNextMessage( &m2 );
                
                // check for mouse moved message
                if(m2.getAddress() == "/audio/low"){
                    oscValue.sound[0] = m2.getArgAsFloat(0);
                }else
                if(m2.getAddress() == "/audio/mid"){
                    oscValue.sound[1] = m2.getArgAsFloat(0);
                }else
                if(m2.getAddress() == "/audio/high"){
                    oscValue.sound[2] = m2.getArgAsFloat(0);
                }
                    
                /*
                // USE POERT2
                // get the next message
                ofxOscMessage m2;
                receiver2.getNextMessage( &m2 );
                
                char nameOsc2[20];
                char numOsc2[20], adrA2[20], adrB2[20];
                
                char oibf2[100];// = m.getAddress().c_str();
                strcpy( oibf2, m2.getAddress().c_str());
                sscanf( oibf2, "/%[^/]/%[^/]/%[^/]/%[^/]", numOsc2, nameOsc2, adrA2, adrB2);
                string checkStr2 = "";
                checkStr2 = checkStr2 + nameOsc2;
                string checkStrG2 = "";
                checkStrG2 = checkStrG2 + numOsc2;    
                if(checkStrG2 == "gyro"){
                    oscValue.degree[3][0] = m2.getArgAsFloat( 3 );
                    oscValue.degree[4][0] = m2.getArgAsFloat( 4 );
                    oscValue.degree[5][0] = m2.getArgAsFloat( 5 );
                    //-----------------------------------------rotate World
                    for(int k=3;k<6;k++){
                        degAvg[k]=0.0f;
                        oscValue.degCvtSin[k][0] = sin(oscValue.degree[k][0]/128.0f*2.0f*PI);
                        for(int i=AvgCnt-1;i>0;i--){
                            oscValue.degCvtSin[k][i] = oscValue.degCvtSin[k][i-1];
                        }
                        for(int i=0;i<AvgCnt;i++){
                            degAvg[k] += oscValue.degCvtSin[k][i];
                        }
                        degAvg[k] = degAvg[k]/AvgCnt;
                    }
                }
                else {
                    // unrecognized message: display on the bottom of the screen
                    string msg_string;
                    msg_string = m2.getAddress();
                    msg_string += ": ";
                    for ( int i=0; i<m2.getNumArgs(); i++ )
                    {
                        // get the argument type
                        msg_string += m2.getArgTypeName( i );
                        msg_string += ":";
                        // display the argument - make sure we get the right type
                        if( m2.getArgType( i ) == OFXOSC_TYPE_INT32 )
                            msg_string += ofToString( m2.getArgAsInt32( i ) );
                        else if( m2.getArgType( i ) == OFXOSC_TYPE_FLOAT )
                            msg_string += ofToString( m2.getArgAsFloat( i ) );
                        else if( m2.getArgType( i ) == OFXOSC_TYPE_STRING )
                            msg_string += m2.getArgAsString( i );
                        else
                            msg_string += "unknown";
                    }
                    // add to the list of strings to display
                    msg_strings[current_msg_string] = msg_string;
                    timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
                    current_msg_string = ( current_msg_string + 1 ) % NUM_MSG_STRINGS;
                    // clear the next line
                    msg_strings[current_msg_string] = "";
                }
                */
            }
            
            // check for waiting messages
            while( receiverString.hasWaitingMessages() )
            {
                // get the next message
                ofxOscMessage m2;
                receiverString.getNextMessage( &m2 );
                
                char nameOsc2[20];
                char numOsc2[20], adrA2[20], adrB2[20];
                
                char oibf2[100];// = m.getAddress().c_str();
                strcpy( oibf2, m2.getAddress().c_str());
                sscanf( oibf2, "/%[^/]/%[^/]/%[^/]/%[^/]", numOsc2, nameOsc2, adrA2, adrB2);
                string checkStr2 = "";
                checkStr2 = checkStr2 + nameOsc2;
                string checkStrG2 = "";
                checkStrG2 = checkStrG2 + numOsc2;    
                if(checkStrG2 == "txt"){
                    oscTxt = m2.getArgAsString( 0 );
                    cout << oscTxt << endl;
                }
                else {
                    // unrecognized message: display on the bottom of the screen
                    string msg_string;
                    msg_string = m2.getAddress();
                    msg_string += ": ";
                    for ( int i=0; i<m2.getNumArgs(); i++ )
                    {
                        // get the argument type
                        msg_string += m2.getArgTypeName( i );
                        msg_string += ":";
                        // display the argument - make sure we get the right type
                        if( m2.getArgType( i ) == OFXOSC_TYPE_INT32 )
                            msg_string += ofToString( m2.getArgAsInt32( i ) );
                        else if( m2.getArgType( i ) == OFXOSC_TYPE_FLOAT )
                            msg_string += ofToString( m2.getArgAsFloat( i ) );
                        else if( m2.getArgType( i ) == OFXOSC_TYPE_STRING )
                            msg_string += m2.getArgAsString( i );
                        else
                            msg_string += "unknown";
                    }
                    // add to the list of strings to display
                    msg_strings[current_msg_string] = msg_string;
                    timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
                    current_msg_string = ( current_msg_string + 1 ) % NUM_MSG_STRINGS;
                    // clear the next line
                    msg_strings[current_msg_string] = "";
                }
            }
        }

};

#endif
