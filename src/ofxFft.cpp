#include "ofxFft.h"	

void ofxFft::setup(){
    //soundStream.listDevices();
    int bufferSize = BUFFER_SIZE;
	   
    ofSoundStreamSetup(0, 2, this, 96000, BUFFER_SIZE, 4);
    
	rightS.assign(bufferSize, 0.0);
    left = new float[BUFFER_SIZE];
	right = new float[BUFFER_SIZE];
    magnitude = new float[BUFFER_SIZE];
    magSqrt = new float[BUFFER_SIZE];
    pMagnitudeFF = new float[BUFFER_SIZE];
    magnitudeFF = new float[BUFFER_SIZE];
    phase = new float[BUFFER_SIZE];
    power = new float[BUFFER_SIZE];
    for(int i=0;i<BUFFER_SIZE;i++){
        magnitude[i] = magSqrt[i] = pMagnitudeFF[i] = magnitudeFF[i] = phase[i] = power[i] = 0.0;
    }
    
    magFilterFacter = 0.87;
	
	//if you want to set a different device id
	//soundStream.setDeviceID(0);
    //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	volHistory.assign(bufferSize, 0.0);
	
	bufferCounter	= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
    bDisplayMenu = false;
}

void ofxFft::update(){
    //lets scale the vol up to a 0-1 range
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}

}

//--------------------------------------------------------------
void ofxFft::audioReceived(float * input, int bufferSize, int nChannels){
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
	}
	bufferCounter++;
}

//--------------------------------------------------------------
void ofxFft::draw(){
    getSpectrum();
    //test Draw
    if(bDisplayMenu)settingMenu();
//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//    ofSetColor(255,255,255,255);
//    ofSetLineWidth(1);
//    float widthScale = (float)ofGetWidth()/BUFFER_SIZE;
//    for(int i=0;i<BUFFER_SIZE-1;i++) {
//        ofLine(i*widthScale, right[i]*100, (i+1)*widthScale, right[i+1]*100);
//    }
}

//--------------------------------------------------------------
void ofxFft::getSpectrum(){
    static int index=0;
	float avg_power = 0.0f;
    myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, left, BUFFER_SIZE, magnitude, phase, power, &avg_power);
    
    /* SQRT FFT	calculate LOGe*/
    for(int i=0;i<BUFFER_SIZE;i++){
        magnitudeFF[i] = magnitudeFF[i]*magFilterFacter + magnitude[i]*(1-magFilterFacter);
//        magSqrt[i] = magSqrt[i]*magFilterFacter + magnitude[i]*(1-magFilterFacter);
        magSqrt[i] = pow(magnitudeFF[i]*5, 0.86f);
    }
    
}

void ofxFft::drawSpectrum(){
    ofSetColor(255, 255);
    ofFill();
    for(int i=0;i<BUFFER_SIZE;i++){
        ofRect(200 + i*4, 100, 3, magSqrt[i]);
    }
}

//--------------------------------------------------------------
void ofxFft::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}

//
void ofxFft::settingMenu(){
    drawSpectrum();
    drawPram();
}

//--------------------------------------------------------------
void ofxFft::drawPram(){
    
}

//--------------------------------------------------------------
float* ofxFft::getMagnitude(){
    return magnitude;
}

//--------------------------------------------------------------
float* ofxFft::getMagSqrt(){
    return magSqrt;
}

//--------------------------------------------------------------
float* ofxFft::getLeftStream(){
    return left;
}

//--------------------------------------------------------------
float* ofxFft::getRightStream(){
    return right;
}

//--------------------------------------------------------------
int ofxFft::getBufferSize(){
    return (int)BUFFER_SIZE;
}

//--------------------------------------------------------------
float* ofxFft::getScaledVol(){
    return &scaledVol;
}