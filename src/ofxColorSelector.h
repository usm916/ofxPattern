//
//  ofxColorSelector.h
//  LS_PatternGeenerate
//
//  Created by usm on 12/17/12.
//
//

#ifndef __LS_PatternGeenerate__ofxColorSelector__
#define __LS_PatternGeenerate__ofxColorSelector__

#include <iostream>
#include "ofMain.h"
#include "OSCvalue.h"
#include "ofxValueTransition.h"

enum ofxCScolorType {
    CS_HSV_COLOR,
    CS_RGB_COLOR
};

class ofxColorSelector {
public:
    ofxColorSelector(){};
    ofxColorSelector(OSCVALUE* _oscValue, ofColor* _elementColor){
        eleR=eleG=eleB=bgR=bgG=bgB = 0.0;
        oscValue = _oscValue;
        elementColor = _elementColor;
    };
    ofxColorSelector(OSCVALUE* _oscValue, ofColor* _elementColor, ofColor* _bgColor, ofPoint* _hsvValue, ofPoint* _hsvBgValue){
        eleR=eleG=eleB=bgR=bgG=bgB = 0.0;
        oscValue = _oscValue;
        elementColor = _elementColor;
        bgColor = _bgColor;
        hsvValue = _hsvValue;
        hsvBgValue = _hsvBgValue;
    };
    void setColors();
    void setConvertColor();
    void setBgColor();
    void setHsvElementColor();
    void setHsvBgColor();
    void checkPushColor();
    void testColor();
    
private:
    ofxCScolorType type;
    ofxValueTransitionPack pack;
    double eleR,eleG,eleB,bgR,bgG,bgB;
    ofColor* elementColor;
    ofColor* bgColor;
    ofColor* hsvColor;
    ofPoint* hsvValue;
    ofPoint* hsvBgValue;
    OSCVALUE* oscValue;
    void HSV2RGB( double * rr, double * gg, double *bb, double H, double S, double V );
};
#endif /* defined(__LS_PatternGeenerate__ofxColorSelector__) */
