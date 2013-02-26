//
//  MpaticleGenerator.h
//  testMotionGraphics
//
//  Created by usm on 12/2/12.
//
//

#ifndef __testMotionGraphics__MpaticleGenerator__
#define __testMotionGraphics__MpaticleGenerator__

#include "ofMain.h"
#include "motionParticle.h"
#include "OSCvalue.h"

#include <iostream>

int const numPat = 210;

class ofxMotionGenerator : ofBaseApp{
    public:
        ofxMotionGenerator(){};
        ofxMotionGenerator(float* _scaledVol, float* _magSqrt, ofPoint* _screenSize, OSCVALUE* _oscValue, ofColor* _baseColor){
            screenSize = _screenSize;
            oscValue = _oscValue;
            scaledVol = _scaledVol;
            magSqrt = _magSqrt;
            baseColor = _baseColor;
            setup();
        };
        void setup();
        void updateTarget();
        void updateRandomWalk();
        void draw();
        void setZero();
        void setTarget();
        void reSetPosition();
        void checkPush(int num);
    private:
        MotionParticle moPat[numPat];
        ofPoint* screenSize;
        OSCVALUE* oscValue;
        ofColor* baseColor;
        float *scaledVol, *magSqrt;
        ofImage snow0, snow1;
    
};

#endif /* defined(__testMotionGraphics__MpaticleGenerator__) */
