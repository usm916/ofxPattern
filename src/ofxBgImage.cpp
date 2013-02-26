//
//  BgImage.cpp
//  audioInputExample
//
//  Created by Takuto Usami on 11/11/02.
//  Copyright (c) 2011 usm BgImage. All rights reserved.
//

#include "ofxBgImage.h"

//----------------------------------------------------------
void ofxBgImage::setup(){
}

//----------------------------------------------------------
void ofxBgImage::drawBg(){
    float dStep = 255/dropTime;
    int scale = 700/dropTime;
    ofFill(); 
    ofSetColor(*baseColor, kbg*dStep);
    drawImage->draw(screenSize->x/2, screenSize->y/2, screenSize->x+scale*(dropTime-kbg), screenSize->x+scale*(dropTime-kbg) );
    kbg--;
}

//----------------------------------------------------------
void ofxBgImage::drawBgSlide(){
    float dStep = (screenSize->x + drawImage->getWidth())/dropTime;
    int scale = 700/dropTime;
    ofFill();
    ofSetColor(*baseColor, 255);
    drawImage->draw(dStep*(dropTime-kbg)-drawImage->getWidth()/2, 0, drawImage->getWidth(), screenSize->y*2 );
    kbg--;
}

//----------------------------------------------------------
void ofxBgImage::drawBg(float _size){
    float dStep = 255/dropTime;
    int scale = 90/dropTime;
    ofFill();
//    ofSetColor(timeColor, kbg*dStep*0.24);
    ofSetColor(*baseColor, kbg*dStep*0.24);
    drawImage->draw(x, y, screenSize->x+scale*(dropTime-kbg)*_size, screenSize->x+scale*(dropTime-kbg)*_size );
    kbg--;
}

//----------------------------------------------------------
void ofxBgImage::drawBgAppear(float _size){
    if(kbg==dropTime&&firstTime){
        kbg=1;
        firstTime=false;
    }
    float dStep = 255/dropTime;
    int scale = 90/dropTime;
    ofFill(); 
//    ofSetColor(timeColor, kbg*dStep*0.24);
    ofSetColor(*baseColor, kbg*dStep*0.24);
    drawImage->draw(x, y, screenSize->x+scale*(dropTime-kbg)*_size, screenSize->x+scale*(dropTime-kbg)*_size );
    if(kbg<dropTime){
        kbg+=3;
    }else if(kbg>dropTime){
        bDisappear = true;
        kbg=dropTime;
    }
//    cout << "Apppp" <<endl;
}

//----------------------------------------------------------
void ofxBgImage::drawBgStaticAppear(){
    if(kbg==dropTime&&firstTime){
        kbg=1;
        firstTime=false;
    }
    float dStep = 255/dropTime;
    int scale = 700/dropTime;
    ofFill(); 
    ofSetColor(255, 255, 255, kbg*dStep);
    drawImage->draw(screenSize->x/2, screenSize->y/2, screenSize->x, screenSize->x*0.75 );
    if(kbg<dropTime){
        kbg++;
    }else if(kbg>dropTime){
        kbg=dropTime;
    }
}

//----------------------------------------------------------
void ofxBgImage::drawBgStaticDisappear(){
    float dStep = 255/dropTime;
    int scale = 700/dropTime;
    ofFill(); 
    ofSetColor(255, 255, 255, kbg*dStep);
    drawImage->draw(screenSize->x/2, screenSize->y/2, screenSize->x, screenSize->x*0.75 );
    kbg--;
}

//----------------------------------------------------------
void ofxBgImage::alphaCount(){
    if(kbg<1){
        kbg = dropTime;
    }
}