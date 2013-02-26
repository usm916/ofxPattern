//
//  MpaticleGenerator.cpp
//  testMotionGraphics
//
//  Created by usm on 12/2/12.
//
//

#include "ofxMpaticleGenerator.h"

//---------------------------------------------------
void ofxMotionGenerator::setup(){
//    snow0.loadImage("images/snow0.png");
//    snow1.loadImage("images/snow1.png");
    for(int i=0;i<numPat;i++){
        moPat[i] = MotionParticle(scaledVol, magSqrt, &snow0, &snow1, screenSize, baseColor);
        moPat[i].setup();
    }
}

//---------------------------------------------------
void ofxMotionGenerator::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    checkPush(7);
    for(int i=0;i<numPat;i++){
        moPat[i].draw(255* oscValue->tFader[2][2]);
    }
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//    cout << moPat[0].getFlow() << endl;
//    cout << moPat[20].getFlow() << endl;
}

//---------------------------------------------------
void ofxMotionGenerator::updateTarget(){
    for(int i=0;i<numPat;i++){
        moPat[i].updateToTarget();
        moPat[i].updatePos();
    }
}

void ofxMotionGenerator::updateRandomWalk(){
    for(int i=0;i<numPat;i++){
        moPat[i].updateToRandomWalk();
        moPat[i].updatePos();
    }
}

//---------------------------------------------------
void ofxMotionGenerator::setZero(){
    for(int i=0;i<numPat;i++){
        moPat[i].setZero();
    }
}


//---------------------------------------------------
void ofxMotionGenerator::setTarget(){
    for(int i=0;i<numPat;i++){
        moPat[i].setTarget();
    }
}

//---------------------------------------------------
void ofxMotionGenerator::reSetPosition(){
    for(int i=0;i<numPat;i++){
        moPat[i].reSetPos();
    }
}

//--------------------------------------------------------------
void ofxMotionGenerator::checkPush(int _num){
    // flash images
    // check frame
    for(int i=0;i<9;i++){
        if(oscValue->mPush[_num][0][0]==1){
            setTarget();
        }else if(oscValue->mPush[_num][1][0]==1){
            setZero();
        }
    }
    if(oscValue->mPush[7][0][0]){
        reSetPosition();
    }
}

