//
//  Hatch.cpp
//  cameraParentingExample
//
//  Created by usm on 12/8/12.
//
//

#include "ofxHatch.h"

//----------------------------------------------
void Hatch::setup(){
    setValue();
}

//----------------------------------------------
void Hatch::setValue(){
    lineWidth = 1.0;
    rotate = pRotate = 0.0;
    opacity = 255;
    pitch = 60;
    depNum = 100;
    
    delta = 9.0;
    
    swCntTime = 0;
    swPitch = 180;
    cntSpeed = pCntSpeed = 1;
}

//----------------------------------------------
void Hatch::update(){
}

//----------------------------------------------
void Hatch::drawHatch(float _degree, ofColor _color){
    ofSetColor(255,255);
    lineWidth = 1 + 20 * oscValue->tFader[2][0];
    ofSetLineWidth(lineWidth);
    
    for(int i=0;i<depNum-20;i++){
        ofPushMatrix();
            ofTranslate(i * pitch + cntTime, 0);
            ofRotateZ(rotate);
            ofLine(0,0,0,ofGetHeight());
        ofPopMatrix();
    }
    
    cntTime += cntSpeed;
    swCntTime ++;
    if(cntTime>pitch) {
        //        pitch = 0;
        cntTime = 0;
    }
    rotate = 90 * (oscValue->tFader[1][3]-0.5);
    pitch = 30 + 120 * oscValue->tFader[2][1];
//    if(swCntTime>swPitch){
//        swCntTime = 0;
//        while( abs(rotate - pRotate) < delta){
//            rotate = ofRandom(-45,45);
//            pitch = ofRandom(30,90);
//        }
//        int cntDelta = 1;
//        while( abs(cntSpeed - pCntSpeed) < cntDelta){
//            cntSpeed = ofRandom(1,4);
//        }
//        pRotate = rotate;
//        pCntSpeed = cntSpeed;
//    }
}

//----------------------------------------------
void Hatch::drawHatch(){
    ofSetColor(255,255);
    ofSetLineWidth(lineWidth);
    for(int i=0;i<depNum/2;i++){
        ofTranslate(i*pitch + cntTime, -200);
        ofRotateZ(rotate * 360);
        ofLine(0,0,0,ofGetHeight());
    }
    
    cntTime ++;
    if(cntTime>pitch) {
//        pitch = 0;
        cntTime = 0;
    }
    
}

//----------------------------------------------
//----------------------------------------------
void ofxHatchPattern::setup(){
    hatch = Hatch(oscValue, screenSize);
    hatch.setValue();
}

void ofxHatchPattern::draw(){
    hatch.drawHatch( ofGetElapsedTimeMillis()/200.0, ofColor(255));
}
