//
//  Hatch.h
//  cameraParentingExample
//
//  Created by usm on 12/8/12.
//
//

#ifndef __cameraParentingExample__Hatch__
#define __cameraParentingExample__Hatch__

#include <iostream>
#include "ofMain.h"
#include "OSCvalue.h"

class Hatch {
    public :
    Hatch(){}
    Hatch(OSCVALUE* _oscValue, ofPoint* _screenSize){
        oscValue = _oscValue;
        screenSize = _screenSize;
    }
    ~Hatch(){}
        void setup();
        void drawHatch();
        void update();
        void drawHatch(float degree, ofColor color);
    
        void setValue();
    
    private :
        int depNum, cntTime, swPitch, swCntTime;
        float rotate, pRotate;
        float delta;
        float lineWidth;
        float opacity;
        float pitch;
        int cntSpeed, pCntSpeed;
        ofPoint* screenSize;
        OSCVALUE* oscValue;
};

class ofxHatchPattern : public ofBaseApp {
    public :
        ofxHatchPattern(){}
        ofxHatchPattern(OSCVALUE* _oscValue, ofPoint* _screenSize){
            oscValue = _oscValue;
            screenSize = _screenSize;
        }
        ~ofxHatchPattern(){}
        Hatch hatch;
        void setup();
        void draw();
        void drawUpdate();
    private :
        ofPoint* screenSize;
        OSCVALUE* oscValue;
};

#endif /* defined(__cameraParentingExample__Hatch__) */
