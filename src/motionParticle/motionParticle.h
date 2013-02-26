//
//  Header.h
//  testMotionGraphics
//
//  Created by Takuto Usami on 9/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef testMotionGraphics_Header_h
#define testMotionGraphics_Header_h

#include "ofMain.h"
#include "ofxValueTransition.h"

class MotionParticle {

public:
    MotionParticle(){};
    MotionParticle(float* _scaledVol, float* _magSqrt, ofImage* _snow0, ofImage* _snow1, ofPoint* _screenSize, ofColor* _baseColor){
        screenSize = _screenSize;
        scaledVol = _scaledVol;
        magSqrt = _magSqrt;
        baseColor = _baseColor;
//        snow0 = _snow0;
//        snow1 = _snow1;
        setup();
    };
    
    void setup();
    void draw(float Opacity);
    void drawBill(float Opacity);
    void updatePos();
    void setTarget();
    void setTargetWide(float);
    void setTarget(float);
    void setTargetRandomPos();
    void setZero();
    void reSetPos();
    void updateToTarget();
    void updateToRandomWalk();
    void timeCount();
    void drawRipple();
    
    float size, scaleSize, randomTimeScale, elapsedTime, timeRandomSeed;
    
    float amr(float,float);
    float moveHalf(float,float);
    bool looseQaualyValue(float,float,float);
    
    ofPoint getFlow();
private:
    int assignFreq;
    int times, timesCount, timing, tDelay;
    int rippleLife, frameCounter;;
    float radius, posff, tRotate, tRotMlt, tRotateT;
    float timeInFrame, set;
    float* scaledVol;
    float* magSqrt;
    float* opacity;
    ofPoint pos, targetPos, flow;
    ofPoint* screenSize;
    ofColor color;
    ofColor* baseColor;
//    ofImage* snow0;
//    ofImage* snow1;
    ofImage snow0;
    ofImage snow1;
    ofxValueTransitionPack vt;
};

#endif
