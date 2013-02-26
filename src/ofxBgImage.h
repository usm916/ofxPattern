//
//  Kaleido.h
//  audioInputExample
//
//  Created by Takuto Usami on 11/11/02.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef BgInage_h
#define BgImage_h

#include "ofMain.h"

#define _BGALPHASSTEP 40

class ofxBgImage {//: public testApp {
    public :
        int kbg, noteNum;
        float wX, wY;
        int imgNum, dropTime;
        int x,  y;
        ofPoint* screenSize;
        ofImage* drawImage;
        string dirPath;
        ofColor timeColor;
        ofColor* baseColor;
        bool firstTime, bDisappear;

        ofxBgImage(){};
        
        ofxBgImage(ofImage* _dr, int _dropTime, int _noteNum, ofPoint* _screenSize, ofColor* _baseColor) {
            screenSize = _screenSize;
            firstTime = true;
            bDisappear = false;
            drawImage = _dr;
            dropTime = _dropTime;
            kbg = _dropTime;
            baseColor = _baseColor;
            timeColor = ofColor(sin((float)ofGetElapsedTimeMillis()/27000.0)*190.0,
                                cos((float)ofGetElapsedTimeMillis()/10000.0)*190.0,
                                sin((float)ofGetElapsedTimeMillis()/41200.0)*190.0);
        };
        
        ofxBgImage(ofImage* _dr, int _dropTime, int _noteNum, int _x, int _y, ofPoint* _screenSize, ofColor* _baseColor) {
            screenSize = _screenSize;
            firstTime = true;
            bDisappear = false;
            drawImage = _dr;
            dropTime = _dropTime;
            kbg = _dropTime;
            x = _x;
            y = _y;
            baseColor = _baseColor;
            timeColor = ofColor(sin((float)ofGetElapsedTimeMillis()/27000.0)*190.0,
                                cos((float)ofGetElapsedTimeMillis()/15000.0)*190.0,
                                sin((float)ofGetElapsedTimeMillis()/41200.0)*190.0);
        };

        ofxBgImage(string _dirPath,int _noteNum, ofPoint* _screenSize, ofColor* _baseColor){
            screenSize = _screenSize;
            firstTime = true;
            dropTime = _BGALPHASSTEP;
            kbg = 0;
            noteNum = _noteNum;
            baseColor = _baseColor;
        };
        
        ~ofxBgImage(){};
        
        void setup();
        void drawBg();
        void drawBgSlide();
        void drawBg(float);
        void drawBgAppear(float);
        
        void drawBgStaticAppear();
        void drawBgStaticDisappear();

        void alphaCount();
};

#endif
