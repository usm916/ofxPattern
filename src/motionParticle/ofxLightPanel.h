//
//  ofxPanelLighting.h
//  LS_PatternGeenerate
//
//  Created by usm on 12/22/12.
//
//

#ifndef __LS_PatternGeenerate__ofxLightPanel__
#define __LS_PatternGeenerate__ofxLightPanel__

#include <iostream>
#include "ofMain.h"
#include "OSCvalue.h"
#include "ofxValueTransition.h"

class ofxLightPanel : ofBaseApp {
public:
    ofxLightPanel(){}
    ofxLightPanel(ofImage* _panel, ofImage* _noise, float* _scaledVol, float* _magSqrt, ofColor* _baseColor, OSCVALUE* _oscValue){
        oscValue = _oscValue;
        elementColor = _baseColor;
        magSqrt = _magSqrt;
        scaledVol = _scaledVol;
//        panel = _panel;
//        noise = _noise;
    }
    void setup();
    void draw();
    void drawPanel();
    void drawNoise();
    void drawLine();
    void reSetNum();
    
private:
    float* scaledVol;
    float* magSqrt;
    ofColor* elementColor;
    OSCVALUE* oscValue;
//    ofImage *panel, *noise;
    ofImage panel, noise, lightLine;
    int fftNum;
    float scale = 1.0;

    
};

class ofxLightPanelSystem : ofBaseApp {
    
private:
    int numPanel = 120;
    OSCVALUE* oscValue;
    ofColor* baseColor;
    float* magSqrt;
    float* scaledVol;
    ofPoint* screenSize;
    deque<ofxLightPanel* > LightPanel;
    ofImage panel, noise;
    ofImage *pPanel, *pNoise;
    
public:
    void setup();
    void draw();
    void targetUpdate();
    void reSetNumSystem();
    void checkPush();
    
    ofxLightPanelSystem() {}
    ofxLightPanelSystem(int num, float* _scaledVol, float* _magSqrt, ofPoint* _screenSize, ofColor* _baseColor, OSCVALUE* _oscValue) {
//        panel.loadImage("/images/panel.png");
//        noise.loadImage("/images/panelNoise.png");
        oscValue = _oscValue;
        baseColor = _baseColor;
        magSqrt = _magSqrt;
        scaledVol = _scaledVol;
        screenSize = _screenSize;
        for(int i=0;i<numPanel;i++){
            LightPanel.push_back( new ofxLightPanel(pPanel, pNoise, scaledVol, magSqrt, baseColor, oscValue));
        }
        setup();
    }
};

#endif /* defined(__LS_PatternGeenerate__ofxPanelLighting__) */
