//
//  ofxImagesystem.h
//  LS_PatternGeenerate
//
//  Created by usm on 12/17/12.
//
//

#ifndef __LS_PatternGeenerate__ofxImagesystem__
#define __LS_PatternGeenerate__ofxImagesystem__

#include <iostream>
#include "ofMain.h"
#include "ofxBgImage.h"
#include "OSCvalue.h"

class ofxImageSystem : ofBaseApp {
    public:
        ofxImageSystem(){};
        ofxImageSystem(int* _msPosX, int* _msPosY, ofPoint* _screenSize, ofColor* _baseColor, OSCVALUE* _oscValue){
            msPosX = _msPosX;
            msPosY = _msPosY;
            screenSize = _screenSize;
            oscValue = _oscValue;
            baseColor = _baseColor;
            ImgLoadImage();
            timeCount = 200;
        };
        void draw();
        void changeMosePos();
        void ImgLoadImage();
        void ImgHitKey(int);
        void ImgHitKeySlide(int);
        void ImgHitKeySlow(int);
        void ImgHitKeyRipple(int);
        void displayText(string,int,int);
        void checkPush();
        void checkLoopSlide();
    
    private:
        void ImgDrawImage(bool slideImg);
        void ImgDrawImageRipple();
        //general setting
        int * msPosX, * msPosY;
        ofPoint* screenSize;
        OSCVALUE* oscValue;
        ofColor* baseColor;
    
        int disText;
        int Imgkey[10][10];
        int ImgkeyR[10][10];
        int stringToInt(string);
        string intToString(int);
    
        vector< vector< ofImage > > allImage;
        vector<int> photoNumber;
        vector<string> dirFolderPath;
        vector<int> noteNum;
        int dropTime;
        int timeCount;
    
        bool BDI = false;
        bool bKawakami = false;
        bool slideImg = true;
        deque<ofxBgImage*> dsplImages;
        deque<ofxBgImage*> dsplImagesSlow;
        deque<ofxBgImage*> rippleImages;
        
        ofImage addColor;
        float pmsX, pmsY;
};

#endif /* defined(__LS_PatternGeenerate__ofxImagesystem__) */
